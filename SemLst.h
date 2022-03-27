/*
 * SemLst.h
 *
 *  Created on: Jun 27, 2021
 *      Author: OS1
 */

#ifndef SEMLST_H_
#define SEMLST_H_
#include"KerSem.h"
class KernelSem;

class DataS{
public:
	KernelSem* sem;
	DataS* next;
	DataS(){
		sem=0;
		next=0;
	}
};

class SemLst {
private:

	DataS* head,*tail;
	int number;

public:

	SemLst();
	virtual ~SemLst();
	void add(KernelSem* sem);
	void update();
	void del(KernelSem* sem);

};

#endif /* SEMLST_H_ */
