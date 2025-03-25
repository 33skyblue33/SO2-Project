#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Mutex.h";
using namespace std;

Mutex logMutex;

//Thread safe function to ensure clean console output
void logMessage(const string& message) {
    logMutex.lock();
    cout << message << endl;
    logMutex.unlock();
}

//Function that performs thinking and eating actions for given philosophers
void philosopher(int id, Mutex* forks, int philosophers, int iter = -1) {
    for (int i = 0; (iter == -1 ? i >= 0 : i < iter); i++) {
        logMessage("Filozof " + to_string(id+1) + " mysli.");
        this_thread::sleep_for(chrono::milliseconds(1000));

        Mutex& leftFork = forks[id];
        Mutex& rightFork = forks[(id + 1) % philosophers];

        if (id % 2 == 0) {
            leftFork.lock();
            rightFork.lock();
        }
        else {
            rightFork.lock();
            leftFork.lock();
        }

        logMessage("Filozof " + to_string(id+1) + " je.");
        this_thread::sleep_for(chrono::milliseconds(1000));

        leftFork.unlock();
        rightFork.unlock();
    }
}

//Creates and executes threads for a number of philosophers given by a program argument
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "You have to specify the number of philosophers as a parameter!";
        return -1;
    }

    if (argc > 2) {
        cout << "You specified more than one argument!";
        return -1;
    }

    try {
        int philosophers = atoi(argv[1]);
        vector<thread> threads;
        Mutex* forks = new Mutex[philosophers];

        for (int i = 0; i < philosophers; ++i) {
            threads.emplace_back(philosopher, i, forks, philosophers, 2);
        }

        for (auto& t : threads) {
            t.join();
        }

        delete[] forks;
        return 0;
    }
    catch (exception e) {
        cout << "Wrong argument format. You must specify a number of philosophers.";
        return -1;
    }

}