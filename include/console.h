#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "SEMap.h"

typedef int (*command)(std::vector<std::string>&, void*);
struct Command
{
	Command(): command_(nullptr), context_(nullptr) { }
	Command(command pCommand) : command_(pCommand), context_(nullptr) { }
	Command(command pCommand, void* pContext) : command_(pCommand), context_(pContext) { }

	int operator()(std::vector<std::string>& pStr)
	{
		return command_(pStr, context_);
	}

	command command_;
	void* context_;
};

SEMap<std::string, Command> commands_ = SEMap<std::string, Command>();
class Console
{
public:
	static void Activate()
	{
		char ans[100];
		printf("> ");
		fgets(ans, 100, stdin);
		char* pos;
		if ((pos = strchr(ans, '\n')) != nullptr)
			*pos = '\0';

		auto tokens = Split(ans, ' ');
		if(!tokens.empty()) {
			if (tokens[0] == "Print")
				Print();
			else if(commands_[tokens[0]](tokens) != 0)
				std::runtime_error("Command " + tokens[0] + " failed");
		}

		printf("done\n");
	}

	static void DeRegister(std::string pStr)
	{
		commands_.Erase(pStr);
	}

	static void Print()
	{
		for(auto& cmd: commands_)
		{
			printf("%s\n", cmd.first.c_str());
		}
	}

	static void Register(std::string pCommand, Command pCallback)
	{
		if(!commands_.Insert(pCommand, pCallback))
			fprintf(stderr, "Command %s already registerd.\n", pCommand.c_str());
	}

private:
	static std::vector<std::string> Split(char* pInput, char pDelim)
	{
		auto result = std::vector<std::string>();
		std::stringstream ss(pInput);
		std::string item;
		while(getline(ss, item, pDelim))
			if(!item.empty())
				result.push_back(item);
		return result;
	};
};

#endif
