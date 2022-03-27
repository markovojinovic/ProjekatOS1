/*
 * SemLst.cpp
 *
 *  Created on: Jun 27, 2021
 *      Author: OS1
 */

#include "SemLst.h"

int syncPrintf(const char *format, ...) ;

SemLst::SemLst():head(0),tail(0),number(0) {
	//syncPrintf("posle konstruktora head: %d\n",head);
}

SemLst::~SemLst() {

	while(head!=0){
		DataS* cur=head;
		head=head->next;
		delete cur;
	}

}

void SemLst::add(KernelSem* sem){

	//syncPrintf("usao\n");
	//syncPrintf("u funkciji head: %d\n",number);

	DataS* tr=new DataS;
	tr->sem=sem;

	if(number==0)
		head=tr;
	else
		tail->next=tr;

	tail=tr;
	number++;

}

void SemLst::update(){

	DataS* cur=head;
	for(cur;cur!=0;cur=cur->next){
		cur->sem->updateBlocked();
	}

}

void SemLst::del(KernelSem* sem){

	DataS* cur,*prev=0;
	for(cur=head,prev;cur!=0;prev=cur,cur=cur->next){
		if(cur->sem==sem){
			DataS* tmp=cur;
			if(head==cur)
				head=cur->next;
			prev->next=cur->next;
			delete tmp;
			number--;
			break;
		}
	}

}
