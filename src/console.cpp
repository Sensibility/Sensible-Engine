//
// Created by steve on 2/10/18.
//

#include "../include/console.h"

Console::Console() {
	this->commands = vector<Command *>();
}

void Console::start() {
	pthread_create( &this->thread, NULL, Console::getInput, this );
}


void Console::cancel() {
	pthread_cancel( this->thread );
}


void Console::join() {
	pthread_join( this->thread, NULL );
}

void Console::registerCommand(Command *pCommand) {
	this->commands.push_back( pCommand );
}

void Console::checkCommand(string ans) {
	for (auto it = this->commands.begin(); it < this->commands.end(); ++it) {
		for (auto hook = (*it)->hooks.begin(); hook < (*it)->hooks.end(); ++hook) {
			if (*hook == ans)
				(*it)->callback();
		}
	}
}

void *Console::getInput(void *context) {
	Console *ctx = (Console *) context;
	std::string ans = "";
	while (ans != "Quit") {
		std::cin >> ans;
		std::cout << "Console Input: " << ans << std::endl;
		ctx->checkCommand( ans );
	}
	std::cout << "Goodbye" << std::endl;
	return NULL;
}
