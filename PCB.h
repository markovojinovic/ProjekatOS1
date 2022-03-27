/*
 * PCB.h
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include"Thread.h"
#include"Lista.h"
class Lista;

typedef int ID;

class PCB {

public:

	friend class Thread;

	unsigned *stack,ss,sp,bp;
	unsigned long stackSize;
	short finished,started,blocked,unlimitedTime,signal;
	unsigned int timeSlice;
	int quant;
	Thread* owner;
	Lista* waiting;
	ID myId;
	static ID globalId;
	static Lista* threadList;

	static PCB* running;

	PCB(unsigned long stackSize,unsigned int timeSlice,Thread* owner);
	void inicStack(void (*body));

	virtual ~PCB();

	void unblock();
	void start();
	void waitToComplete();

};

#endif /* PCB_H_ */
