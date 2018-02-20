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
bool bDoWork 		= true;

//void thrdfunc(int i){
void thrdfunc(){
	//lets get this threads id
	 std::thread::id this_id  = std::this_thread::get_id();
	
	//does the following need protection?
	//if you dont care about a few extra cycles 
	//(as is the case for UI loops) then no
	while(bDoWork){	
//		std::cout<<"In thread:"<<std::to_string(i)<<std::endl;												//avoid the unweildly GUID
//		std::cout<<"In thread:"<<this_id<<std::endl;	//can also do std::to_string(i) to 
		
		//snooze for a bit to simulate work
		std::this_thread::sleep_for(std::chrono::milliseconds(1));	
	}
//	std::cout<<"Thread:"<<std::to_string(i)<<" exiting"<<std::endl;
	std::cout<<"Thread:"<<this_id<<" exiting"<<std::endl;	
}

int main(){
	
	//create a bunch of threads
	std::vector<std::thread> threads;
	for(int i = 0; i < 20; ++i){
//		threads.push_back(std::thread(thrdfunc,i));
		threads.push_back(std::thread(thrdfunc));
	}
	

	//let em run a bit (90 seconds)
	std::this_thread::sleep_for(std::chrono::milliseconds(90000));
	
	//ask them all to stop
	bDoWork = false;
	
	//wait for em to finish
	for(auto& thread : threads){
		thread.join();
	}

	cout<<"All threads done!"<<endl;

	return 0;
}
