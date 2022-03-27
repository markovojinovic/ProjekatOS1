/*
 * Thread.h
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

#include"PCB.h"
#include"SCHEDULE.h"

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB; // Kernel's implementation of a user's thread
class Lista;

class Thread {

public:

	PCB* myPCB;

	void start();
	void waitToComplete();
	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);

	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual ~Thread();
	static void wrapper();

protected:

	friend class PCB;
	virtual void run() {}

};

void dispatch ();

#endif /* THREAD_H_ */
