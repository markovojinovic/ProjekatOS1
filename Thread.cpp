/*
 * Thread.cpp
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */
#include"Thread.h"
//#include"Timer.h"
#include<iostream.h>

class Thread;

#define lock asm cli
#define unlock asm sti

Thread::Thread (StackSize stackSize, Time timeSlice){
	myPCB=new PCB(stackSize,timeSlice,this);
}

Thread::~Thread(){
	delete myPCB;
}

void Thread::start(){
	myPCB->start();
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

ID Thread::getId(){
	return myPCB->myId;
}

ID Thread::getRunningId(){
	return PCB::running->owner->getId();
}

Thread * Thread::getThreadById(ID id){
	return PCB::threadList->getById(id);
}

void Thread::wrapper(){
	PCB::running->owner->run();
	PCB::running->finished=1;
	PCB::running->waiting->unblockList();
	dispatch();
}
