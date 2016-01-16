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
	ImGui::BeginChildFrame((ImGuiID)this, ImVec2());

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
	else if (dataSize == 3) maxValue = 0x0FFFFF;
	else if (dataSize == 4) maxValue = INT32_MAX;
	float invMaxValue = 1.f / static_cast<float>(maxValue);

	ImVec2 graphStartPos = windowStartPos;
	ImVec2 graphSize = ImVec2(windowSize.x, windowSize.y);
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	uint32 sampleStep = sampleCount / static_cast<uint32>(graphSize.x);

	if (channelCount == 2)
	{
		graphSize.y *= 0.5f;
		
		int32 prevLeftSample = 0;
		int32 prevRightSample = 0;

		memcpy(&prevLeftSample, buffer, dataSize);
		memcpy(&prevRightSample, buffer + dataSize, dataSize);

		if (dataSize == 1)
		{
			prevLeftSample = *reinterpret_cast<int8*>(&prevLeftSample);
			prevRightSample = *reinterpret_cast<int8*>(&prevRightSample);
		}
		else if (dataSize == 2)
		{
			prevLeftSample = *reinterpret_cast<int16*>(&prevLeftSample);
			prevRightSample = *reinterpret_cast<int16*>(&prevRightSample);
		}
		else if (dataSize == 3)
		{
			// ??
		}


		float prevLeftValue = static_cast<float>(prevLeftSample) * invMaxValue;
		float prevRightValue = static_cast<float>(prevRightSample) * invMaxValue;

		for (uint32 i = 1; i < static_cast<uint32>(graphSize.x); ++i)
		{
			int32 leftSample = 0;
			int32 rightSample = 0;
			memcpy(&leftSample, buffer + i * sampleStep * sampleSize, dataSize);
			memcpy(&rightSample, buffer + i * sampleStep * sampleSize + dataSize, dataSize);

			if (dataSize == 1)
			{
				leftSample = *reinterpret_cast<int8*>(&leftSample);
				rightSample = *reinterpret_cast<int8*>(&rightSample);
			}
			else if (dataSize == 2)
			{
				leftSample = *reinterpret_cast<int16*>(&leftSample);
				rightSample = *reinterpret_cast<int16*>(&rightSample);
			}
			else if (dataSize == 3)
			{
				// ??
			}

			float leftValue = static_cast<float>(leftSample) * invMaxValue;
			float rightValue = static_cast<float>(rightSample) * invMaxValue;

			drawList->AddLine(
				ImVec2(graphStartPos.x + static_cast<float>(i - 1), graphStartPos.y + graphSize.y * .5f - graphSize.y * prevLeftValue),
				ImVec2(graphStartPos.x + static_cast<float>(i), graphStartPos.y + graphSize.y * .5f - graphSize.y * leftValue),
				0xFFFFFFFF
			);

			drawList->AddLine(
				ImVec2(graphStartPos.x + static_cast<float>(i - 1), graphStartPos.y + graphSize.y * 1.5f - graphSize.y * prevRightValue),
				ImVec2(graphStartPos.x + static_cast<float>(i), graphStartPos.y + graphSize.y * 1.5f - graphSize.y * rightValue),
				0xFFFFFFFF
				);

			prevLeftValue = leftValue;
			prevRightValue = rightValue;
		}
		
	}
	else if (channelCount == 1)
	{
		int32 prevSample = 0;
		memcpy(&prevSample, buffer, dataSize);

		if (dataSize == 1)
		{
			prevSample = *reinterpret_cast<int8*>(&prevSample);
		}
		else if (dataSize == 2)
		{
			prevSample = *reinterpret_cast<int16*>(&prevSample);
		}
		else if (dataSize == 3)
		{
			// ??
		}

		float prevValue = static_cast<float>(prevSample) * invMaxValue;

		for (uint32 i = 1; i < static_cast<uint32>(graphSize.x); ++i)
		{
			int32 sample = 0;
			memcpy(&sample, buffer + i * sampleStep * sampleSize, dataSize);

			if (dataSize == 1)
			{
				sample = *reinterpret_cast<int8*>(&sample);
			}
			else if (dataSize == 2)
			{
				sample = *reinterpret_cast<int16*>(&sample);
			}
			else if (dataSize == 3)
			{
				// ??
			}

			float value = static_cast<float>(sample) * invMaxValue;

			drawList->AddLine(
				ImVec2(graphStartPos.x + static_cast<float>(i - 1), graphStartPos.y + graphSize.y * .5f - graphSize.y * prevValue),
				ImVec2(graphStartPos.x + static_cast<float>(i), graphStartPos.y + graphSize.y * .5f - graphSize.y * value),
				0xFFFFFFFF
				);

			prevValue = value;
		}
	}

	ImGui::EndChildFrame();
}
