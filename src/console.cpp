//
// Created by crusherexe on 6/24/2018.
//

#include <sstream>
#include "../include/console.h"


Console::Console() {
    this->mutex_ = SDL_CreateMutex();
    if(!this->mutex_)
        throw std::runtime_error("SDL_CreateMutex == NULL");


    commands_ = std::map<std::string, command>();
}
Console::~Console() {
	if(mutex_)
		SDL_DestroyMutex(mutex_);
}

std::vector<std::string> Console::Split(char* pInput, char pDelim) {
    auto result = std::vector<std::string>();
    std::stringstream ss(pInput);
    std::string item;
    while(getline(ss, item, pDelim))
        if(!item.empty())
            result.push_back(item);
    return result;
}

void Console::Activate() {
/*
    if(!Lock())
        return;
*/

	char ans[100];
	printf("> ");
	fgets(ans, 100, stdin);

	auto tokens = this->Split(ans, ' ');
	if(!tokens.empty()) {
	    if(commands_.find(tokens[0]) != commands_.end())
	        if(commands_.at(tokens[0])(tokens) != 0)
	            std::runtime_error("Command " + tokens[0] + " failed");
	}

	printf("done\n");

/*
    UnLock();
*/
}

void Console::Register(std::string pCommand, command pCallback){
    if(commands_.find(pCommand) == commands_.end())
        commands_.insert(std::pair<std::string, command>(pCommand, pCallback));
    else
        fprintf(stderr, "Command %s already registerd.\n", pCommand.c_str());
}

bool Console::Lock() {
	if (this->mutex_)
		return SDL_TryLockMutex(this->mutex_) == 0;
	return false;
}

void Console::UnLock() {
    SDL_mutexV(this->mutex_);
}
