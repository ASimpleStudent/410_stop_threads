//============================================================================
// Name        : 12_stop_threads.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;
const int TOTAL_THREADS		=20;

//global to control threads
bool bDoWork = true;


void thrdfunc(){
	//lets get this threads id
	thread::id this_id = this_thread::get_id();
	
	//one way to stop threads is by checking on a flag
	//thats contolled by another thread
	//this is called busy waiting and can KILL performance
	//(spike CPU usage) if you spend too much time polling 
	//the flag value
	//you are much better off using condition variables
	//
	while(bDoWork){		
		//do some work
		cout<<"In thread:"<<this_id<<endl;
		
		//simulated work 
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	
	//cleanup and exit
	cout<<"      EXITING:"<<this_id<<endl;
}

//show starting a bunch of threads
int main()
{
	std::vector<std::thread> vecThreads;

	//how many cores (2 virtual cores per physical core)
	int numbThreads = std::thread::hardware_concurrency();

	//lets start up 1 per core
	for (int i=0;i<numbThreads/2;i++){
		vecThreads.push_back(std::thread(thrdfunc));
	}

	//let em run a bit (90 seconds)
	this_thread::sleep_for(chrono::milliseconds(90000));

	//ask them all to stop
	bDoWork = false;

	//wait for em to finish
	for(auto& t : vecThreads){
		t.join();
	}
	
	cout<<"All threads done!"<<endl;

	return 0;
}

