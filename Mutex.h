#pragma once
#include <thread>
#include <iostream>
#include <atomic>
using namespace std;

class Mutex
{
private: 
	atomic_flag locked = ATOMIC_FLAG_INIT;
	
public:
	void lock();
	void unlock();

};