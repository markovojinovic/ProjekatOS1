/*
 * Lista.cpp
 *
 *  Created on: Jun 24, 2021
 *      Author: OS1
 */

#include "Lista.h"

Lista::Lista(){
	head=0;
	tail=0;
	number=0;
}

void Lista::put(PCB* thr){

	Data* tr=new Data;
	tr->pcb=thr;

	if(head==0)
		head=tr;
	else
		tail->next=tr;

	tail=tr;
	number++;

}

void Lista::unblockList(){

	Data* cur=head;
	for(cur;cur!=0;cur=cur->next){
		cur->pcb->unblock();
		cur->pcb=0;
	}

	head=tail=0;

}

Thread* Lista::getById(int id){

	if(id==0)return 0;

	Data* cur;
	for(cur=head;cur!=0;cur=cur->next){
		if((int)(cur->pcb->owner->getId())==(int)id){
			return cur->pcb->owner;
		}
	}

	return 0;

}

Lista::~Lista(){

	while(head!=0){
		Data* cur=head;
		head=head->next;
		delete cur;
	}

}

void Lista::del(PCB* pcb){
	Data* cur,*prev=0;
	for(cur=head,prev;cur!=0;prev=cur,cur=cur->next){
		if(cur->pcb==pcb){
			Data* tmp=cur;
			if(head==cur)
				head=cur->next;
			prev->next=cur->next;
			delete tmp;
			number--;
			break;
		}
	}
}
