/*
 * KernelEv.h
 *
 *  Created on: Jun 29, 2021
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include"Thread.h"
#include"event.h"
#include"PCB.h"
#include "IVTEntry.h"

class Event;
class IVTEntry;

typedef unsigned char IVTNo;

class KernelEv {

public:

	PCB* blocked,*creator;
	Event* owner;
	short value;
	IVTNo ivtNo;
	IVTEntry* interupt;			//prekidna rutina koja je vezana za konkretan dogadjaj

	KernelEv(Event* owner,IVTNo ivtNo);
	virtual ~KernelEv();

	void wait();
	void signal();

};

#endif /* KERNELEV_H_ */
