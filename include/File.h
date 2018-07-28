#ifndef _FILE_H
#define _FILE_H
#include <vector>

class File
{
public:
	static std::vector<std::string> ReadFile(const char* pFileName)
	{
		char line[255];

		auto file = std::vector<std::string>();

		FILE * fp = fopen(pFileName, "r");

		if(fp != nullptr)
		{
			while(fgets(line, sizeof(line), fp) != nullptr)
			{
				file.emplace_back(line);
			}
			fclose(fp);
		}

		return file;
	}
	static std::string ReadFileToStr(const char* pFileName)
	{
		char line[255];

		auto file = std::string();

		FILE * fp = fopen(pFileName, "r");

		if(fp != nullptr)
		{
			while(fgets(line, sizeof(line), fp) != nullptr)
			{
				file += std::string(line);
			}
			fclose(fp);
		}

		return file;
	}

	static std::vector<const char*>* ReadFileC(const char* pFileName)
	{
		auto readFile = ReadFile(pFileName);
		auto cfile = new vector<const char*>();
		for(auto& str: readFile)
		{
			cfile->push_back(str.c_str());
		}
		return cfile;
	}
private:
};

#endif _FILE_H