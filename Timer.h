/*
 * Timer.h
 *
 *  Created on: Jun 18, 2021
 *      Author: OS1
 */

//				POTENCIJALNE GRESKE!!!
#ifndef TIMER_H_
#define TIMER_H_
#include"bussy.h"
#include"Thread.h"
#include"KerSem.h"
#include<iostream.h>
class SemLst;
class Thread;

volatile int demand_context_change=0;		//inicijalizacija globalnih promenljivih
volatile int counter=defaultTimeSlice;
volatile int tsp=PCB::running->sp;
volatile int tss=PCB::running->ss;
volatile int tbp=PCB::running->bp;

#define lock asm cli
#define unlock asm sti

BusyThread bussy;							//"zaludna nit"
short bussyOn=0;

void interrupt timer(){	// prekidna rutina
	if (!demand_context_change) counter--;
	if (counter == 0 || demand_context_change) {		//ako je neograniceno vreme niti resetujemo brojac
		if(PCB::running->unlimitedTime==1)
			counter=defaultTimeSlice;
			//cuvamo kontekst starog izvrsavanja
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}

		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;

		if (! PCB::running->finished && !PCB::running->blocked && !bussyOn)		//ukoliko nije gotova, i nije blokirana
			Scheduler::put((PCB*)PCB::running);								//nit vracamo je u raspored

		PCB::running=Scheduler::get();

		if(PCB::running==0){
			PCB::running=bussy.myPCB;
			bussyOn=1;
		}else
			bussyOn=0;

		//syncPrintf("Nit koja je dohvacena iz Scedulera je: %d\n",PCB::running->owner->getId());											//testiranje da li je validna nit

		//pamtimo stari brojac, kao i kontekst
		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;
		counter = PCB::running->quant;

		asm {
			mov sp, tsp   									//vracamo stari kontekst
			mov ss, tss
			mov bp, tbp
		}
	}

														// poziv stare prekidne rutine koja se
														 // nalazila na 08h, a sad je na 60h
														 // poziva se samo kada nije zahtevana promena
														 // konteksta – tako se da se stara
														 // rutina poziva samo kada je stvarno doslo do prekida
	if(!demand_context_change){
		asm int 60h;
		//syncPrintf("ulazimo u klasicnu prekidnu rutinu\n");
		KernelSem::SemaphoreList->update();
	}

	demand_context_change = 0;
								//problem: skidanje sa steka posle promene konteksta nas odvodi na neko "levo" mesto
}

unsigned oldTimerOFF, oldTimerSEG;

void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0   			      				//  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h 				//; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 	//postavlja
		mov word ptr es:0020h, offset timer 	//novu rutinu

		mov ax, oldTimerSEG	 					//	postavlja staru rutinu
		mov word ptr es:0182h, ax 				//; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}


#endif /* TIMER_H_ */
