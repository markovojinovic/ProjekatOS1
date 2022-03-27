/*
 * PCB.cpp
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include<dos.h>

PCB::PCB(unsigned long stackSize,unsigned int timeSlice,Thread* owner) {

	myId=PCB::globalId++;

	this->stackSize=stackSize;
	this->timeSlice=timeSlice;
	stackSize/=sizeof(unsigned);
	stack=new unsigned[stackSize];
	inicStack(Thread::wrapper);

	finished=started=blocked=signal=0;
	unlimitedTime=timeSlice==0?1:0;
	quant=timeSlice;
	waiting=new Lista();

	this->owner=owner;

	threadList->put(this);

}

PCB::~PCB() {

	delete[] stack;
	delete waiting;
	threadList->del(this);

}

void PCB::inicStack(void (*body)){

	#ifndef BCC_BLOCK_IGNORE

		stack[stackSize-1] = 0x200;
		stack[stackSize-2] = FP_SEG(body);
		stack[stackSize-3] = FP_OFF(body);
		stack[stackSize-4] = FP_OFF(stack+stackSize-12);

		sp = FP_OFF(stack+stackSize-12);		//-12 treba da stoji kao gore!!! kad se vrati tajmer
		ss = FP_SEG(stack+stackSize-12);
		bp=sp;

		//komentarisani delovi su za rezim sa tajmerom kada se ulazi u prekidnu rutinu

	#endif

}

void PCB::unblock(){
	if(blocked==1){
		blocked=0;
	if(!finished)
		Scheduler::put(this);
	}
}
void PCB::start(){
	if(!started){
		Scheduler::put(this);
		started=1;
	}
}
void PCB::waitToComplete(){
	if(finished!=1){
		PCB::running->blocked=1;
		waiting->put(PCB::running);
		dispatch();
	}
}


