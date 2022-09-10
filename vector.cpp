#include <iostream>
using namespace std;

template<typename T>
class Vector {
	T *_data;
	size_t _size;
	size_t _capacity;
	void realloc() {
		++this->_capacity;
		this->_capacity *= 2;
		if (!this->_data) {
			this->_data = new T[this->_capacity] { };
			this->_size = 0;
			return;
		}
		T *new_data = new T[this->_capacity];
		for (size_t i = 0; i < this->_size; i++)
			new_data[i] = this->_data[i];
		delete[] this->_data;
		this->_data = new_data;
	}

public:
	Vector() {
		this->_size = 0;
		this->_capacity = 1;
		this->_data = new T[this->_capacity] { };
	}

	Vector(size_t _capacity) {
		this->_size = 0;
		this->_capacity = _capacity;
		this->_data = new T[this->_capacity] { };
	}

	Vector(const Vector<T> &v) {
		this->_capacity = v._capacity;
		this->_size = v._size;
		this->_data = new T[this->_capacity] { };
		for (size_t i = 0; i < this->_size; i++) {
			this->_data[i] = v._data[i];
		}
	}

	~Vector() {
		if (this->_data)
			delete[] this->_data;
	}

	size_t size() {
		return this->_size;
	}

	size_t capacity() {
		return this->_capacity;
	}

	void shrink_to_fit() {
		if (!this->_data) {
			this->_capacity = 1;
			this->_size = 0;
			this->_data = new T[this->_capacity] { };
			return;
		}
		this->_capacity = this->_size;
		T *new_data = new T[this->size];
		for (size_t i = 0; i < this->_size; i++)
			new_data[i] = this->_data[i];
		delete[] this->_data;
		this->_data = new_data;
	}

	T* data() {
		return this->_data;
	}

	T* at(size_t i) {
		if (i >= this->_size)
			throw out_of_range("at() called with index out of range!");
		return this->_data + i;
	}

	T* back() {
		return this->_data + this->_size - 1;
	}

	T& operator[](size_t i) {
		if (i >= this->_size)
			throw out_of_range("operator[]() called with index out of range!");
		return this->_data[i];
	}

	void push(T el) {
		if (this->_size >= this->_capacity)
			this->realloc();
		this->_data[this->_size] = el;
		++this->_size;
	}

	T pop() {
		T t { this->_data[this->_size - 1] };
		this->_data[this->_size - 1] = 0;
		--this->_size;
		return t;
	}

	void clear() {
		if (this->_data)
			delete[] this->_data;
		this->_data = new T[this->_capacity] { };
		this->_size = 0;
	}

	bool empty() {
		return this->_size == 0;
	}

	void operator=(const Vector<T> &v) {
		if (this->_capacity < v._capacity)
			this->_capacity = v._capacity;
		this->_size = v._size;
		if (this->_data)
			delete[] this->_data;
		this->_data = new T[this->_capacity] { };
		for (size_t i = 0; i < this->_size; i++) {
			this->_data[i] = v._data[i];
		}
	}

	//friend ostream& operator<<(ostream &out, Vector<T> v);
};

template<class T>
ostream& operator<<(ostream &out, Vector<T> v) {
	for (size_t i = 0; i < v.size(); i++)
		out << v[i] << " ";
	return out;
}

int main() {
	Vector<int> v;
	v.push(1);
	v.push(2);
	v.push(3);
	v[2] = 4;

	cout << v.size() << " " << v.capacity() << endl;
	cout << v.pop() << endl;
	cout << v.pop() << endl;
	cout << v.pop() << endl;
	cout << v.size() << " " << v.capacity() << endl;
	v.push(12);
	v.push(13);
	v.push(14);
	cout << *v.at(1) << endl;
	cout << v << endl;
	cout << v.size() << " " << v.capacity() << endl;
	cout << "----" << endl;
	Vector<int> v2 = v;
	cout << v2 << endl;
	v2.push(112);
	Vector<int> v3 { v2 };
	cout << v3 << endl;
	v3.push(111);
	v = v3;
	cout << v << endl;

	return 0;
}
