/*
 * KerSem.h
 *
 *  Created on: Jun 26, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_
#include"semaphor.h"
#include"KSList.h"
#include"SemLst.h"
class Semaphore;
class KSList;
class SemLst;

typedef unsigned int Time;

class KernelSem{

public:

	int value;
	KSList* blocked;
	Semaphore* owner;
	static SemLst* SemaphoreList;

	virtual int wait (Time maxTimeToWait);
	virtual void signal();
	int val () const;
	void updateBlocked();

	KernelSem(Semaphore* owner,int val);
	virtual ~KernelSem();

};


#endif /* KERSEM_H_ */
