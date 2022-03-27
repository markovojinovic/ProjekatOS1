/*
 * KerSem.cpp
 *
 *  Created on: Jun 26, 2021
 *      Author: OS1
 */

#include"KerSem.h"
#include<dos.h>

KernelSem::KernelSem(Semaphore* owner,int val){
	this->owner=owner;
	blocked=new KSList();
	value=val;

	SemaphoreList->add(this);
}
KernelSem::~KernelSem(){
	delete blocked;
	SemaphoreList->del(this);
}

int KernelSem::wait (Time maxTimeToWait){
	asm cli;
	value--;
	if(value<0){
		PCB::running->blocked=1;
		blocked->put(PCB::running,maxTimeToWait);
		dispatch();
	}
	asm sti;
	return !PCB::running->signal;
}

void KernelSem::signal(){
	asm cli;
	if(value<0){
		PCB* put=blocked->get();
		put->blocked=0;
		Scheduler::put(put);
		//put->signal=1;
	}
	value++;
	asm sti;
}

int KernelSem::val () const{
	return value;
}

int syncPrintf(const char *format, ...) ;

void KernelSem::updateBlocked(){
	DataK* cur=blocked->head;
	for(cur;cur!=0;cur=cur->next){
		if(!cur->unlimitedWaitingTime)
			cur->waitingTime--;
		if(cur->waitingTime==0 && !cur->unlimitedWaitingTime){
			cur->pcb->blocked=0;
			cur->pcb->signal=1;
			if(!cur->pcb->finished)
				Scheduler::put(cur->pcb);
			blocked->del(cur->pcb);
			value++;
		}
	}
}
