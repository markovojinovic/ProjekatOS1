/*
 * KSList.cpp
 *
 *  Created on: Jun 27, 2021
 *      Author: OS1
 */

#include "KSList.h"

KSList::KSList() {
	head=tail=0;
	number=0;
}

KSList::~KSList() {
	while(head!=0){
		DataK* cur=head;
		head=head->next;
		delete cur;
	}
}

void KSList::put(PCB* thr,int wt){

	DataK* tr=new DataK(wt);
	tr->pcb=thr;

	if(head==0)
		head=tr;
	else
		tail->next=tr;

	tail=tr;
	number++;

}
PCB* KSList::get(){

	if(number==0)
		return 0;

	DataK* del=head;
	PCB* ret=head->pcb;
	head=head->next;
	number--;
	delete del;

	return ret;
}
void KSList::del(PCB* pcb){

	DataK* cur,*prev=0;
	for(cur=head,prev;cur!=0;prev=cur,cur=cur->next){
		if(cur->pcb==pcb){
			DataK* tmp=cur;
			if(head==cur)
				head=cur->next;
			prev->next=cur->next;
			delete tmp;
			number--;
			break;
		}
	}

}
