#include "stdafx.h"
#include "core/Path.h"

size_t Path::GetDirectoriesLength(const char* _path)
{
	size_t length = strlen(_path);
	for (int i = length - 1; i >= 0; --i)
	{
		if (_path[i] == '/')
		return i + 1;
	}
	return 0;
}

void Path::Sanitize(char* _path)
{
	std::string path = _path;

	// REPLACE ANTISLASHES BY SLASHES
	std::size_t i = 0;
	while ((i = path.find('\\', i)) != std::string::npos)
	{
		path[i] = '/';
	}

	// REMOVE ./
	i = 0;
	while ((i = path.find("./", i)) != std::string::npos)
	{
		if (i != 0 && path[i-1] != '.')
		{
			path = path.replace(i, 2, "");
		}
		else
		{
			i += 2;
		}
	}

	// REMOVE ../
	i = 0;
	while ((i = path.find("../", i)) != std::string::npos)
	{
		if (i >= 2)
		{
			size_t i2 = path.rfind('/', i - 2);
			if (i2 != std::string::npos)
			{
				if (strncmp(path.c_str() + i2 + 1, "..", 2) != 0)
				{
					path.replace(i2, i - i2 + 2, "");
					continue;
				}
			}
		}

		i += 3;
	}

	strcpy(_path, path.c_str());
}

