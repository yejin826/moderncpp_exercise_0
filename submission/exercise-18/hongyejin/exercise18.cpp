#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int x2 = 0;

int main()
{
	// use mutex
	mutex m;
	condition_variable cv;

	thread th3([&]() {
		for (int i = 0; i < 100000000; i++) {
			lock_guard<mutex> lck(m);
			x2++;
		}
		cv.notify_all();
	});

	thread th4([&]() {
		for (int i = 0; i < 100000000; i++) {
			lock_guard<mutex> lck(m);
			x2++;
		}
		cv.notify_all();
	});

	thread th5([&]() {
		unique_lock<mutex> lck(m);

		cv.wait(lck, []() {
			return x2 == 200000000;
		});

		cout << x2 << "\n";
	});

	if (th3.joinable()) th3.join(); // 연산이 끝날 때까지 기다림
	if (th4.joinable()) th4.join();
	if (th5.joinable()) th5.join();

	return 0;
}