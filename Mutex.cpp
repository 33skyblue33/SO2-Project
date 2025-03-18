#include "Mutex.h"

void Mutex::lock()
{
	while (locked.test_and_set(memory_order_acquire))
	{
		this_thread::yield();
	}
}

void Mutex::unlock()
{
	locked.clear(memory_order_release);
}