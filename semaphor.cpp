/*
 * semaphor.cpp
 *
 *  Created on: Jun 26, 2021
 *      Author: OS1
 */

#include "semaphor.h"
class Semaphor;

Semaphore::Semaphore(int init) {
	myImpl=new KernelSem(this,init);
}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::wait (Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal(){
	myImpl->signal();
}

int Semaphore::val () const{
	return myImpl->val();
}
