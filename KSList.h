/*
 * KSList.h
 *
 *  Created on: Jun 27, 2021
 *      Author: OS1
 */

#ifndef KSLIST_H_
#define KSLIST_H_
#include"PCB.h"

class DataK{
public:
	PCB* pcb;
	DataK* next;
	int waitingTime;
	short unlimitedWaitingTime,signalCalled;
	DataK(int wt){
		pcb=0;
		next=0;
		waitingTime=wt;
		unlimitedWaitingTime=wt==0?1:0;
	}
};

class KSList {

public:

	DataK* head,*tail;
	int number;

	KSList();
	virtual ~KSList();

	void put(PCB* thr,int wt);
	PCB* get();
	void del(PCB* pcb);
};

#endif /* KSLIST_H_ */
