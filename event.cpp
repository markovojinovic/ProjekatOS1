/*
 * event.cpp
 *
 *  Created on: Jun 29, 2021
 *      Author: OS1
 */
#include"event.h"

Event::Event (IVTNo ivtNo){
	myImpl=new KernelEv(this,ivtNo);
}

Event::~Event (){
	delete myImpl;
}

void Event::wait (){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
