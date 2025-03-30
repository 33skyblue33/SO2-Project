// Copyright[2025] Alicja Fuks
#include "Mutex.h"

// Locks the mutex and returns control to the main thread

void Mutex::lock(){
    while (locked.test_and_set(memory_order_acquire)) {
        this_thread::yield();
    }
}

// Unlocks the mutex and frees the related resources for other threads
void Mutex::unlock(){
    locked.clear(memory_order_release);
}