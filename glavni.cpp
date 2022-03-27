/*
 * glavni.cpp
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */

#include"Timer.h"
#include"KerSem.h"
#include"IVTEntry.h"
#include"user.h"
int PCB::globalId=1;
PCB* PCB::running=0;
Lista* PCB::threadList=new Lista();
SemLst* KernelSem::SemaphoreList=new SemLst();
IVTEntry** IVTEntry::interruptVector=new IVTEntry*[256];
unsigned IVTEntry::globalAdd=0x246;
class PCB;
class Thread;
class KernelSem;

int userMain (int argc, char* argv[]);

int main(int argc, char** argv){

	inic();

	Thread glavni;
	PCB::running=glavni.myPCB;		//dodeljuje se glavna nit runningu

    int ret=userMain(argc,argv);

	restore();

	return ret;

}

void dispatch(){
	asm cli;
	demand_context_change = 1;
	timer();
	asm sti;
}
