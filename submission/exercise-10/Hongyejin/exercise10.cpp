#include <iostream>
#include <cstdint> // size_t

using namespace std;

template<typename T>
class MyVector {
public:

    MyVector() : data_(nullptr), capacity_(3), size_(0) { // �ʱ�ȭ
        data_ = new T[capacity_];
    }

    // ���� ������
    MyVector(const MyVector& a) : capacity_(a.capacity_), size_(a.size_) {
        // �����ʹ� �״�� �������� �ȵ�, ���� ��ü�� ����Ű�� ��
        data_ = new T[capacity_];

        for (int i = 0; i < size_; i++) {
            data_[i] = a[i];
        }
    }

    // �̵� ������
    MyVector(MyVector&& a) noexcept : data_(a.data_), capacity_(a.capacity_), size_(a.size_) {
        delete a;
    }
    
    
    // �̵� ���� ������
    MyVector& operator=(const MyVector& a) noexcept {
        data_ = move(a.data_);
        capacity_ = move(a.capacity_);
        size_ = move(a.size_);

        return *this;
    }

    MyVector& operator=(MyVector&& a) noexcept {
        data_ = move(a.data_);
        capacity_ = move(a.capacity_);
        size_ = move(a.size_);

        return *this;
    }
    
   // ~MyVector() {
   //    delete[] data_;
   // }

    void push_back(const T& n) {
        if (capacity_ <= size_) {
            // �뷮 �ø���
            capacity_ *= 2;

            // �޸� ���� �Ҵ�
            T* new_data = new T[capacity_];

            // ����
            copy(data_, data_ + size_, new_data);

            // ���� �޸� ����
            delete[] data_;

            // ���� ������ ��ü
            data_ = new_data;
        }

        data_[size_] = n;
        size_++;
    }

    void pop_back() {
        // ������ ���̱�
        if (size_ > 0) {
            size_--;
        }
    }

    const T& operator[](size_t i) const {
        return data_[i];
    }

    size_t size() const {
        return size_;
    }

private:
    T* data_; // ���Ϳ� ���� ������
    size_t capacity_;
    size_t size_;
};

// Use case
int main()
{
    {
        MyVector<int> v;

        v.push_back(1); // v.size() == 1
        //cout << v.size()<<endl;
        v.push_back(2); // v.size() == 2
        //cout << v.size() << endl;
        v.push_back(3); // v.size() == 3
        //cout << v.size() << endl;
        v.push_back(4); // v.size() == 4
        //cout << v.size() << endl;
        v.push_back(5); // v.size() == 5
        //cout << v.size() << endl;
        v.pop_back();
        //cout << v.size() << endl;
        //cout << v[3] << endl;

        MyVector<int> v2 = move(v);
        cout << v2.size() << endl;
        cout << v.size() << endl;
        // v2.size() == 5 
        // v.size() == 0
    } // v �Ҹ�


    return 0;
}