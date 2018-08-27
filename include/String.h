#ifndef _STRING_H_
#define _STRING_H_

#include <vector>
#include <string>

namespace SEString
{

	std::vector<std::string> Split(char* pInput, char pDelim)
	{
		auto result = std::vector<std::string>();
		std::stringstream ss(pInput);
		std::string item;
		while (getline(ss, item, pDelim))
			if (!item.empty())
				result.push_back(item);
		return result;
	};

	std::string Join(std::vector<std::string> pInput, char pJoin = ' ')
	{
		std::string result = "";
		for (auto& in : pInput) {
			result += in + pJoin;
		}
		return result;
	}
}

#endif _STRING_H_