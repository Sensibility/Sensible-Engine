#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef int (*command)(std::vector<std::string>&);

class Console
{
public:

	Console();
	~Console();

	void Activate();
	void Register(std::string, command);
private:
    void HandleAns(std::string);
    bool Lock();
	void UnLock();
	std::vector<std::string> Split(char*, char);
	SDL_mutex* mutex_;

	std::map<std::string, command> commands_;
};

#endif
