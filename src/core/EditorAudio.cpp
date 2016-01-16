#include "core/EditorAudio.h"

#include "imgui.h"

EditorAudio::EditorAudio()
{
	strcpy(buf, ".\\");
}

EditorAudio::~EditorAudio()
{
}

void EditorAudio::update(float _dt)
{
	ImGui::FileExplorer(buf, 256);
}

void EditorAudio::setRootPath(const char* _value)
{
	m_rootPath = _value;
	strcpy(buf, _value);
}