/*
 * IVTEntry.cpp
 *
 *  Created on: Jun 30, 2021
 *      Author: OS1
 */

#include "IVTEntry.h"
#include<dos.h>

IVTEntry::IVTEntry(IVTNo ivtNo,pInterrupt body) {
	this->ivtNo=ivtNo;
	interuptFunction=body;

#ifndef BCC_BLOCK_IGNORE
	oldInteruptFunction = getvect(ivtNo);
	setvect(ivtNo, interuptFunction);
#endif

	newIntAdd=globalAdd;
	globalAdd+=4;

	IVTEntry::interruptVector[(int)ivtNo]=this;		//kada se zavrsi inicijalizacija objekta, pokazivac
													//na njega se smesta u niz prekidnih rutina
}

IVTEntry::~IVTEntry() {
											//vracanje stare prekidne rutine
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldInteruptFunction);
#endif

}

IVTEntry* IVTEntry::getInterupt(IVTNo No){
	return IVTEntry::interruptVector[(int)No];
}

void IVTEntry::setOwner(KernelEv* owner){
	this->owner=owner;
}

void IVTEntry::callOld(){
	oldInteruptFunction();
	dispatch();
}

void IVTEntry::signal(){
	owner->signal();
}
