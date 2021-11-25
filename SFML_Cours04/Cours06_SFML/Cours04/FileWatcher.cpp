#include "FileWatcher.hpp"

FileWatcher::FileWatcher(const char* _filePath)
{
	this->filePath = _filePath;
	init = false;
}

FileWatcher::~FileWatcher()
{
}

bool FileWatcher::checkFileModification(float dt)
{
	checktimer -= dt;
	if (checktimer <= 0)
	{
		checktimer = checkCD;
		struct stat result;
		if (stat(filePath, &result) == 0)
		{
			if (!init)
			{
				init = true;
				lastChangedFile = result.st_mtime;
			}
			else if (lastChangedFile < result.st_mtime)
			{
				printf("The file has been changed, reloading \n");
				lastChangedFile = result.st_mtime;
				return true;
			}
		}
	}
		return false;
}

void FileWatcher::appendCommandsFromFile(Turtle* entity)
{
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "Assets/test.txt", "rb");
	if (err != 0)
		printf("The file was not opened\n");


	if (fp != NULL && !feof(fp))
	{
		char line[256] = {};
		while (true)
		{
			int64_t nb = 0;
			int64_t spd = 0;
			fscanf_s(fp, "%s %lld %lld\n", line, 256, &nb, &spd);
			std::string s = line;
			if (s == "Advance")
				entity->appendCommand(CommandList::CommandType::Advance, nb, spd);
			else if (s == "Turn")
				entity->appendCommand(CommandList::CommandType::Turn, nb, spd);
			else if (s == "PenUp")
				entity->appendCommand(CommandList::CommandType::PenUp, nb, spd);
			else if (s == "PenDown")
				entity->appendCommand(CommandList::CommandType::PenDown, nb, spd);

			if (feof(fp))
				break;
		}

	}
	fclose(fp);
}
