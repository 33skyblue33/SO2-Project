#include "Mutex.h"
#include <vector>
#include <string>

Mutex mutex;

void print(string text)
{
	mutex.lock();
	cout << text << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	mutex.unlock();
}

int main()
{
	vector<thread> T;

	for (int i = 0;i < 5;i++)
	{
		T.emplace_back(print, "ala" + to_string(i + 1));
	}

	for (auto& t : T)
	{
		t.join();
	}

	return 0;
}

