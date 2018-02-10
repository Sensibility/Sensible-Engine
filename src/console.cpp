//
// Created by steve on 2/10/18.
//

#include "../include/console.h"

void Console::start() {
	pthread_create( &this->thread, NULL, this->getInput, NULL );
}


void Console::cancel() {
	pthread_cancel( this->thread );
}


void Console::join() {

	pthread_join( this->thread, NULL );
}
