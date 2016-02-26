#include "stdafx.h"
#include "core/EditorAudio.h"

#include <algorithm>

#include "imgui.h"
#include "core/ResourceManager.h"
#include "core/AudioFile.h"
#include "core/Log.h"

#define PA_ASSERT(f) if (PaError error = f != paNoError) { LOG_ERROR("Portaudio error: %s", Pa_GetErrorText(error)); ASSERT(false); }


EditorAudio::EditorAudio()
	: m_openingFile(false)
	, m_currentAudioSample(nullptr)
	, m_recording(nullptr)
{
	strcpy(m_pathBuffer, "./data/audio/");
}

EditorAudio::~EditorAudio()
{
	if (m_currentAudioSample)
	{
		m_currentAudioSample->releaseUnuse();
		m_currentAudioSample = nullptr;
	}
}

void EditorAudio::update(float _dt)
{
	if (ImGui::Button("Open Sample"))
	{
		m_openingFile = true;
	}

	if (m_openingFile)
	{
		ImGui::Begin("Open sample", &m_openingFile);
		ImGui::FileExplorer(m_pathBuffer, 256);
		if (ImGui::Button("Open"))
		{
			m_openingFile = false;
			openFile(m_pathBuffer);
		}
		ImGui::End();
	}

	if (m_currentAudioSample)
	{
		ImGui::SameLine();
		if (m_player.isPlaying())
		{
			if (ImGui::Button("STOP"))
			{
				m_player.stop();
			}
		}
		else
		{
			if (ImGui::Button("PLAY"))
			{
				m_player.play();
			}
		}
	}

	ImGui::SameLine();
	
	if (m_recording && Pa_IsStreamActive(m_recording))
	{
		if (ImGui::Button("STOPREC"))
		{
			stopRecord();
		}
	}
	else
	{
		stopRecord();

		if (ImGui::Button("REC"))
		{
			record();
		}
	}

	if (m_currentAudioSample)
	{
		displaySampleGraph(m_currentAudioSample);
	}
}

static int recordCallback(const void* _inputBuffer, void* _outputBuffer, unsigned long _framesPerBuffer, const PaStreamCallbackTimeInfo* _timeInfo, PaStreamCallbackFlags _statusFlags, void* _userData)
{
	EditorAudio::RecordData* data = reinterpret_cast<EditorAudio::RecordData*>(_userData);
	const int16* readData = reinterpret_cast<const int16*>(_inputBuffer);
	int16* writeData = data->data + (data->currentFrame * 2);
	unsigned long framesLeft = data->maxFrame - data->currentFrame;
	uint32 copyedFrames = std::min(framesLeft, _framesPerBuffer);

	memcpy(writeData, readData, copyedFrames * 2 * sizeof(uint16));

	data->currentFrame += copyedFrames;
	return data->currentFrame == data->maxFrame ? paComplete : paContinue;
}

void EditorAudio::record()
{
	PaStreamParameters inputParameters = {};
	inputParameters.device = Pa_GetDefaultInputDevice();
	if (inputParameters.device == paNoDevice)
	{
		LOG_ERROR("Can't record: No input device.");
		return;
	}
	inputParameters.channelCount = 2;
	inputParameters.sampleFormat = paInt16;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;

	m_recordingData.currentFrame = 0;
	m_recordingData.maxFrame = 44100 * 5;
	m_recordingData.data = new int16[m_recordingData.maxFrame * 2];

	PA_ASSERT(Pa_OpenStream(&m_recording, &inputParameters, nullptr, 44100, paFramesPerBufferUnspecified, paClipOff, &recordCallback, &m_recordingData));
	PA_ASSERT(Pa_StartStream(m_recording));
}

void EditorAudio::stopRecord()
{
	if (!m_recording)
		return;

	PA_ASSERT(Pa_CloseStream(m_recording));
	m_recording = nullptr;

	AudioSample* sample = ResourceManager::CreateResource<AudioSample, uint32, uint32, AudioFormat>(44100, m_recordingData.currentFrame, AUDIOFORMAT_STEREO16);
	sample->loadUse();
	memcpy(sample->getBuffer(), m_recordingData.data, m_recordingData.currentFrame * AudioSample::getFormatSampleSize(sample->getFormat()));
	setSample(sample);
	sample->releaseUnuse();

	m_recordingData.currentFrame = 0;
	m_recordingData.maxFrame = 0;
	delete[] m_recordingData.data;
	m_recordingData.data = nullptr;
}

void EditorAudio::setSample(AudioSample* _sample)
{
	if (m_currentAudioSample)
	{
		m_currentAudioSample->releaseUnuse();
		m_currentAudioSample = nullptr;
	}

	m_currentAudioSample = _sample;
	m_currentAudioSample->loadUse();
	m_player.setSample(m_currentAudioSample);
}

void EditorAudio::openFile(const char* _path)
{
	AudioFile* file = ResourceManager::CreateResource<AudioFile, const char*>(_path);
	if (file->getError() != Resource::ERROR_NONE)
	{
		LOG_ERROR("Failed to open sample \"%s\": %s", _path, file->getErrorDescription());
		return;
	}
	setSample(file);
}

void EditorAudio::displaySampleGraph(AudioSample* _sample)
{
	ImGui::BeginChildFrame(reinterpret_cast<ImGuiID>(this), ImVec2());

	ImVec2 windowStartPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();

	uint8 channelCount = AudioSample::getFormatChannelCount(_sample->getFormat());
	uint8* buffer = static_cast<uint8*>(_sample->getBuffer());
	uint32 sampleCount = _sample->getSampleCount();
	uint8 sampleSize = AudioSample::getFormatSampleSize(_sample->getFormat());
	uint8 dataSize =  sampleSize / channelCount;
	int32 maxValue = ~0;
	if (dataSize == 1) maxValue = INT8_MAX;
	else if (dataSize == 2) maxValue = INT16_MAX;
	else if (dataSize == 3) maxValue = static_cast<int32>(pow(2, 8 * dataSize)) / 2 - 1;
	else if (dataSize == 4) maxValue = INT32_MAX;
	float invMaxValue = 1.f / static_cast<float>(maxValue);

	ImVec2 graphStartPos = windowStartPos;
	ImVec2 graphSize = ImVec2(windowSize.x, windowSize.y);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	uint32 sampleStep = sampleCount / static_cast<uint32>(graphSize.x);

	if (channelCount == 2)
	{
		graphSize.y *= 0.5f;
		
		float displayMinLeftValue = 0.f;
		float displayMinRightValue = 0.f;
		float displayMaxLeftValue = 0.f;
		float displayMaxRightValue = 0.f;

		uint32 sampleIndex = 0u;
		for (uint32 i = 0; i < sampleCount; ++i)
		{
			uint32 leftSample = 0;
			uint32 rightSample = 0;
			memcpy(&leftSample, buffer + i * sampleSize, dataSize);
			memcpy(&rightSample, buffer + i * sampleSize + dataSize, dataSize);

			float leftValue = static_cast<float>(leftSample) * invMaxValue;
			float rightValue = static_cast<float>(rightSample) * invMaxValue;
			if (leftValue > 1.f) leftValue -= 2.f;
			if (rightValue > 1.f) rightValue -= 2.f;

			// We only display one sample per pixel.
			// Therefore, we chose to represent the most extreme values of all the intermediate samples
			displayMinLeftValue = std::min(displayMinLeftValue, leftValue);
			displayMinRightValue = std::min(displayMinRightValue, leftValue);
			displayMaxLeftValue = std::max(displayMaxLeftValue, leftValue);
			displayMaxRightValue = std::max(displayMaxRightValue, leftValue);

			if (i % sampleStep == 0 || i == sampleCount - 1)
			{
				drawList->AddLine(
					ImVec2(graphStartPos.x + static_cast<float>(sampleIndex), graphStartPos.y + graphSize.y * .5f - graphSize.y * displayMinLeftValue),
					ImVec2(graphStartPos.x + static_cast<float>(sampleIndex), graphStartPos.y + graphSize.y * .5f - graphSize.y * displayMaxLeftValue),
					0xFFFFFFFF
					);

				drawList->AddLine(
					ImVec2(graphStartPos.x + static_cast<float>(sampleIndex), graphStartPos.y + graphSize.y * 1.5f - graphSize.y * displayMinRightValue),
					ImVec2(graphStartPos.x + static_cast<float>(sampleIndex), graphStartPos.y + graphSize.y * 1.5f - graphSize.y * displayMaxRightValue),
					0xFFFFFFFF
					);

				displayMinLeftValue = 0.f;
				displayMinRightValue = 0.f;
				displayMaxLeftValue = 0.f;
				displayMaxRightValue = 0.f;
				++sampleIndex;
			}
		}
	}
	else if (channelCount == 1)
	{
		float displayMinValue = 0.f;
		float displayMaxValue = 0.f;

		uint32 sampleIndex = 1u;
		for (uint32 i = 1; i < sampleCount; ++i)
		{
			uint32 sample = 0;
			memcpy(&sample, buffer + i * sampleSize, dataSize);

			float value = static_cast<float>(sample) * invMaxValue;
			if (value > 1.f) value -= 2.f;

			// We only display one sample per pixel.
			// Therefore, we chose to represent the most extreme values of all the intermediate samples
			displayMinValue = std::min(displayMinValue, value);
			displayMaxValue = std::max(displayMaxValue, value);

			if (i % sampleStep == 0 || i == sampleCount - 1)
			{
				drawList->AddLine(
					ImVec2(graphStartPos.x + static_cast<float>(sampleIndex), graphStartPos.y + graphSize.y * .5f - graphSize.y * displayMinValue),
					ImVec2(graphStartPos.x + static_cast<float>(sampleIndex), graphStartPos.y + graphSize.y * .5f - graphSize.y * displayMaxValue),
					0xFFFFFFFF
					);

				displayMinValue = 0.f;
				displayMaxValue = 0.f;
				++sampleIndex;
			}
		}
	}

	ImGui::EndChildFrame();
}
