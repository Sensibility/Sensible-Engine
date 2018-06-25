#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <sstream>
#include <string>
#include <vector>
#include <map>

typedef int (*command)(std::vector<std::string>&);

std::map<std::string, command> commands_;
class Console
{
public:
	static void Activate()
	{
		char ans[100];
		printf("> ");
		fgets(ans, 100, stdin);

		auto tokens = Split(ans, ' ');
		if(!tokens.empty()) {
			if(commands_.find(tokens[0]) != commands_.end())
				if(commands_.at(tokens[0])(tokens) != 0)
					std::runtime_error("Command " + tokens[0] + " failed");
		}

		printf("done\n");
	};
	static void Register(std::string pCommand, command pCallback)
	{
		if(commands_.find(pCommand) == commands_.end())
			commands_.insert(std::pair<std::string, command>(pCommand, pCallback));
		else
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
