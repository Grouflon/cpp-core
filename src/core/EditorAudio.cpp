#include "core/EditorAudio.h"

#include <cmath>

#include "imgui.h"
#include "core/ResourceManager.h"
#include "core/AudioFile.h"
#include "core/Log.h"

EditorAudio::EditorAudio()
	: m_openingFile(false)
	, m_currentAudioFile(nullptr)
{
	strcpy(m_pathBuffer, "./data/audio/");
	openSample("./data/audio/Alarm01.wav");
}

EditorAudio::~EditorAudio()
{
	if (m_currentAudioFile)
	{
		m_currentAudioFile->releaseUnuse();
		m_currentAudioFile = nullptr;
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
			openSample(m_pathBuffer);
		}
		ImGui::End();
	}

	if (m_currentAudioFile)
	{
		displaySampleGraph(m_currentAudioFile);
	}
}

void EditorAudio::openSample(const char* _path)
{
	if (m_currentAudioFile)
	{
		m_currentAudioFile->releaseUnuse();
		m_currentAudioFile = nullptr;
	}

	m_currentAudioFile = ResourceManager::CreateResource<AudioFile, const char*>(_path);
	m_currentAudioFile->loadUse();
	if (m_currentAudioFile->getError() != Resource::ERROR_NONE)
	{
		LOG_ERROR("Failed to open sample \"%s\": %s", _path, m_currentAudioFile->getErrorDescription());
		m_currentAudioFile->releaseUnuse();
		m_currentAudioFile = nullptr;
	}
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
