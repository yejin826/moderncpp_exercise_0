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
	atomic<int> x1 = 0; // atomic ��ü x1�� ����
	
	// ������ �ð�
	auto start1 = steady_clock::now(); 

	thread th1([&]() { // ������1
		for (int i = 0; i < 100000000; i++)
			x1.fetch_add(1);
		});

	thread th2([&]() { // ������2
		for (int i = 0; i < 100000000; i++) 
			x1.fetch_add(1);
		});

	if (th1.joinable()) th1.join(); // ������1 ������ ���� ������ ��ٸ�
	if (th2.joinable()) th2.join(); // ������2 ������ ���� ������ ��ٸ�
	
	// ���� �ð�
	auto end1 = steady_clock::now();
	auto time1 = duration_cast<milliseconds>(end1 - start1);
	
	cout << "<atomic>\n";
	cout << x1 << '\n';
	cout << "�ɸ� �ð�: " << time1.count() << "ms\n\n";

	// use mutex
	int x2 = 0;
	mutex m;

	// ������ �ð�
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

	if (th3.joinable()) th3.join(); // ������ ���� ������ ��ٸ�
	if (th4.joinable()) th4.join();
	
	// ���� �ð�
	auto end2 = steady_clock::now();
	auto time2 = duration_cast<milliseconds>(end2 - start2);

	cout << "<mutex>\n";
	cout << x2 << '\n';
	cout << "�ɸ� �ð�: " << time2.count() << "ms\n";
	
	return 0;
}