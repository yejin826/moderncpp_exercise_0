#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;
using namespace chrono;

int main()
{
	// use atomic
	atomic<int> x1 = 0; // atomic 객체 x1을 생성
	
	// 시작한 시각
	auto start1 = steady_clock::now(); 

	thread th1([&]() { // 스레드1
		for (int i = 0; i < 100000000; i++)
			x1.fetch_add(1);
		});

	thread th2([&]() { // 스레드2
		for (int i = 0; i < 100000000; i++) 
			x1.fetch_add(1);
		});

	if (th1.joinable()) th1.join(); // 스레드1 연산이 끝날 때까지 기다림
	if (th2.joinable()) th2.join(); // 스레드2 연산이 끝날 때까지 기다림
	
	// 끝난 시각
	auto end1 = steady_clock::now();
	auto time1 = duration_cast<milliseconds>(end1 - start1);
	
	cout << "<atomic>\n";
	cout << x1 << '\n';
	cout << "걸린 시간: " << time1.count() << "ms\n\n";

	// use mutex
	int x2 = 0;
	mutex m;

	// 시작한 시각
	auto start2 = steady_clock::now();
	thread th3([&]() {
		lock_guard<mutex> lck(m);
		for (int i = 0; i < 100000000; i++)
			x2++;
		});

	thread th4([&]() {
		lock_guard<mutex> lck(m);
		for (int i = 0; i < 100000000; i++)
			x2++;
		});

	if (th3.joinable()) th3.join(); // 연산이 끝날 때까지 기다림
	if (th4.joinable()) th4.join();
	
	// 끝난 시각
	auto end2 = steady_clock::now();
	auto time2 = duration_cast<milliseconds>(end2 - start2);

	cout << "<mutex>\n";
	cout << x2 << '\n';
	cout << "걸린 시간: " << time2.count() << "ms\n";
	
	return 0;
}