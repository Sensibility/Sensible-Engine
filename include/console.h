#ifndef MAIN_CONSOLE_H
#define MAIN_CONSOLE_H

#include <pthread.h>
#include <iostream>
#include <functional>
#include "vector.h"

struct Command {
	std::function<void()> callback;
	std::vector<string> hooks;
};

class ConsoleCommand {
public:
	virtual std::vector<Command *> getCommands()= 0;
};

class Console {
public:
	Console();
	pthread_t thread;
	vector<Command *> commands;

	void start();

	void join();

	void cancel();

	static void *getInput(void *);

	void registerCommand(Command *pCommand);
	void checkCommand(string ans);
};


#endif //MAIN_CONSOLE_H
