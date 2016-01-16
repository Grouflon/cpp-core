#include "imgui_user.h"

#include <vector>
#include <algorithm>
#include <dirent.h>		// Lists files in directory

#include "imgui.h"
#include "core/Log.h"
#include "core/Types.h"
#include "core/Path.h"
#include "core/FileHandle.h"

namespace ImGui
{
	struct DirEntry
	{
		std::string name;
		bool dir;
		int32 size;
	};

	void FileExplorer(char* _pathBuffer, size_t _bufferSize)
	{
		InputText("path", _pathBuffer, _bufferSize);
		Path::Sanitize(_pathBuffer);

		char* dirPath = static_cast<char*>(alloca(_bufferSize));
		strcpy(dirPath, _pathBuffer);

		std::vector<DirEntry> entries;

		bool pathIsDir = true;
		DIR* dir = opendir(dirPath);
		if (!dir)
		{
			dirPath[Path::GetDirectoriesLength(dirPath)] = '\0';
			dir = opendir(dirPath);
		}
		if (dir)
		{
			if (dirPath[strlen(dirPath) - 1] != '/')
			{
				strncat(dirPath, "/", _bufferSize);
			}

			errno = 0;
			dirent* ent = readdir(dir);

			while(ent)
			{
				if (strcmp(".", ent->d_name) != 0)
				{
					int32 size = 0u;
					if (ent->d_type != DT_DIR)
					{
						std::string filePath = std::string(dirPath) + ent->d_name;
						FileHandle f(filePath.c_str());
						f.open(FileHandle::OPENMODE_READ);
						size = f.getSize();
					}

					DirEntry dirEntry;
					dirEntry.name = ent->d_name;
					dirEntry.dir = ent->d_type == DT_DIR;
					dirEntry.size = size;
					entries.push_back(dirEntry);
				}

				errno = 0;
				ent = readdir(dir);
			}

			closedir(dir);
		}

		std::sort(entries.begin(), entries.end(), [](const DirEntry& _val1, const DirEntry& _val2) -> bool
		{
			if (_val1.dir != _val2.dir)
			{
				return _val1.dir;
			}
			else
			{
				return strcmp(_val1.name.c_str(), _val2.name.c_str()) <= 0;
			}
		});
		BeginChild(_pathBuffer, ImVec2(), true);
		ImGui::Columns(2);

		Text("Name");
		NextColumn();
		Text("Size");
		NextColumn();
		Separator();

		for (auto& entry : entries)
		{
			std::string name = entry.name;
			if (entry.dir) name += '/';

			if (Selectable(name.c_str(), false, ImGuiSelectableFlags_SpanAllColumns))
			{
				strcpy(_pathBuffer, dirPath);
				strncat(_pathBuffer, name.c_str(), _bufferSize - strlen(_pathBuffer));
			}

			NextColumn();
			if (!entry.dir)
			{
				int32 pow = 0;
				int32 size = entry.size;
				while (size > 1024)
				{
					size = size / 1024;
					++pow;
				}

				char* unit;
				switch(pow)
				{
				default: unit = "b"; break;
				case 1: unit = "Kb"; break;
				case 2: unit = "Mb"; break;
				case 3: unit = "Gb"; break;
				case 4: unit = "Tb"; break;
				}

				Text("%d %s", size, unit);
			}
			NextColumn();
		}

		ImGui::Columns(1);
		EndChild();
		Path::Sanitize(_pathBuffer);
	}
} // namespace ImGui