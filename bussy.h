/*
 * bussy.h
 *
 *  Created on: Jun 20, 2021
 *      Author: OS1
 */

#ifndef BUSSY_H_
#define BUSSY_H_

#include"Thread.h"

class BusyThread: public Thread{
private:
public:
	BusyThread(){}
protected:
	void run(){
		while(1){
		//	syncPrintf("Idle\n");
		}
	}
};


#endif /* BUSSY_H_ */
