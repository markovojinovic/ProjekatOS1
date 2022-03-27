/*
 * IVTEntry.h
 *
 *  Created on: Jun 30, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KernelEv.h"

class KernelEv;

typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:

	static IVTEntry** interruptVector;			//niz prekidnih rutina (ima ih koliko ima ivtp ulaza)
	KernelEv* owner;
	IVTNo ivtNo;
	pInterrupt interuptFunction,oldInteruptFunction;
	unsigned newIntAdd;
	static unsigned globalAdd;
												//treba da se dodaju ostali podaci vezani za prekid
												//pamtiti staru prekidnu rutinu

	IVTEntry(IVTNo ivtNo,pInterrupt body);
	virtual ~IVTEntry();

	static IVTEntry* getInterupt(IVTNo No);
	void setOwner(KernelEv* owner);
	void callOld();
	void inicInterupt();
	void signal();

};

#define PREPAREENTRY(numEntry, cOld)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
newEntry##numEntry.signal();\
if (cOld == 1)\
newEntry##numEntry.callOld();\
}

#endif /* IVTENTRY_H_ */
