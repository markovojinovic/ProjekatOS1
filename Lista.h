/*
 * Lista.h
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */

#ifndef LISTA_H_
#define LISTA_H_
#include"Thread.h"
class Thread;
class PCB;

class Data{
public:
	PCB* pcb;
	Data* next;
	Data(){
		pcb=0;
		next=0;
	}
};

class Lista {

public:

	 Data* head,*tail;
	 int number;

	Lista ();
	virtual ~Lista();

	void put(PCB* thr);
	void unblockList();
	Thread* getById(int id);
	void del(PCB* pcb);

};

#endif /* LISTA_H_ */
