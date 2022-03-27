/*
 * KernelEv.cpp
 *
 *  Created on: Jun 29, 2021
 *      Author: OS1
 */

#include "KernelEv.h"
#include"SCHEDULE.H"

KernelEv::KernelEv(Event* owner,IVTNo ivtNo) {
	this->owner=owner;
	this->ivtNo=ivtNo;
	creator=PCB::running;
	value=0;
	blocked=0;										//pokazivac na blokiranu nit na dogadjaju
	interupt=IVTEntry::getInterupt(ivtNo);
	interupt->setOwner(this);
}

KernelEv::~KernelEv() {
	owner=0;
	creator=0;
	blocked=0;
}

void KernelEv::wait(){

	if(PCB::running==creator){
		if(value==0){
			PCB::running->blocked=1;
			blocked=PCB::running;
			dispatch();
		}
		else
			value=0;
	}

}
void KernelEv::signal(){

	if(blocked==0)
		value=1;
	else{
		blocked->blocked=0;
		Scheduler::put(blocked);
		blocked=0;
		dispatch();
	}

}
