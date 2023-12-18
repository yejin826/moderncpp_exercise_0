#include <memory>
#include <iostream>
#include <utility>
using namespace std;

#ifdef _MSC_VER
#define MY_FUNCTION __FUNCSIG__ 
#else
#define MY_FUNCTION __PRETTY_FUNCTION__
#endif

int default_constructor_count = 0;
int copy_constructor_count = 0;
int move_constructor_count = 0;
int copy_assignment_count = 0;
int move_assignment_count = 0;
int destructor_count = 0;

class MyApplication {
public:
	MyApplication() {
		default_constructor_count++;
		std::cout << MY_FUNCTION << '\n';
	}

	MyApplication(const MyApplication& other) {
		copy_constructor_count++;
		std::cout << MY_FUNCTION << '\n';
	}

	MyApplication(MyApplication&&) noexcept {
		move_constructor_count++;
		std::cout << MY_FUNCTION << '\n';
	}

	MyApplication& operator=(const MyApplication& other) {
		copy_assignment_count++;
		std::cout << MY_FUNCTION << '\n';
		return *this;
	}

	MyApplication& operator=(MyApplication&&) noexcept {
		move_assignment_count++;
		std::cout << MY_FUNCTION << '\n';
		return *this;
	}

	~MyApplication() {
		destructor_count++;
		std::cout << MY_FUNCTION << '\n';
	}
};

void TestUniquePtr() {
	// MyApplication ����
	auto p = std::make_unique<MyApplication>();

	// unique pointer �̵�
	auto p2 = std::move(p);
}

void TestSharedPtr() {
	// MyApplication ����
	auto p = std::make_shared<MyApplication>();

	// copy constructor (������ ����)
	auto p2 = p;

	// p2 �ʱ�ȭ
	p2.reset();

	// ���� ���� ��ü weak_ptr ����
	std::weak_ptr<MyApplication> weak_p = p;

	//shared_ptr ��ȯ
	auto lock = weak_p.lock();
	if (lock) {
		std::cout << "Acquired ownership\n";
	}
}

int main() 
{
	/*
	MyApplication my_app;  //�⺻ ������ ȣ��
	cout << "�⺻ ������ ȣ�� Ƚ��: " << default_constructor_count << '\n';
	*/

	TestUniquePtr();
	cout << "�⺻ ������ ȣ�� Ƚ��: " << default_constructor_count << '\n';
	cout << "���� ������ ȣ�� Ƚ��: " << copy_constructor_count << '\n';
	cout << "�̵� ������ ȣ�� Ƚ��: " << move_constructor_count << '\n';
	cout << "���� ���� ������ ȣ�� Ƚ��: " << copy_assignment_count << '\n';
	cout << "�̵� ���� ������ ȣ�� Ƚ��: " << move_assignment_count << '\n';
	cout << "�Ҹ��� ȣ�� Ƚ��: " << destructor_count << '\n';

	TestSharedPtr();
	cout << "�⺻ ������ ȣ�� Ƚ��: " << default_constructor_count << '\n';
	cout << "���� ������ ȣ�� Ƚ��: " << copy_constructor_count << '\n';
	cout << "�̵� ������ ȣ�� Ƚ��: " << move_constructor_count << '\n';
	cout << "���� ���� ������ ȣ�� Ƚ��: " << copy_assignment_count << '\n';
	cout << "�̵� ���� ������ ȣ�� Ƚ��: " << move_assignment_count << '\n';
	cout << "�Ҹ��� ȣ�� Ƚ��: " << destructor_count << '\n';

	return 0;
}