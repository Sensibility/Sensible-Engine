#ifndef MAIN_CONSOLE_H
#define MAIN_CONSOLE_H

#include <pthread.h>
#include <iostream>

class Console {
public:
	pthread_t thread;

	void start();

	void join();

	void cancel();

	static void *getInput(void *) {
		std::string ans = "";
		while (ans != "Quit") {
			std::cout << "Console Input: " << ans << std::endl;
			std::cin >> ans;
		}
		std::cout << "Goodbye" << std::endl;
		return NULL;
	}

};


#endif //MAIN_CONSOLE_H
