#pragma once
#include <iostream>
using namespace std;

template <typename T>
class MyArray
{
private:
	int size;
	T* data;

public:
	MyArray(int s = 0, T e = NULL) : size{ s } {
		data = new T[size];
		for (int i = 0; i < size; i++) data[i] = e;
		//s만큼의 크기를 가진 배열 생성 후 e으로 초기화
	}
	MyArray(initializer_list<T> args) {
		size = args.size();
		data = new T[size];
		{
			int i = 0;
			for (T e : args) {
				data[i] = e;
				i++;
			}
		}
		//{}으로 요소를 받음
	}
	//~MyArray() {
	//	if (data != NULL) {
	//		cout << "메모리 해제";
	//		delete[] data;
	//	}
	//}

	void resize(int);
	void push(T&);
	void insert(int, T&);
	T pop();
	void erase(int);
	int length();

	T &operator[](int);
	bool operator== (MyArray<T>&);
	bool operator!= (MyArray<T>&);
	void operator=(const MyArray<T>&);
	void operator+=(const MyArray<T>&);

	template <typename T>
	friend ostream& operator<<(ostream&, const MyArray<T>&);
	friend ostream& operator<<(ostream&, const MyArray<string>&);
	friend ostream& operator<<(ostream&, const MyArray<char>&);
};

template <typename T>void MyArray<T>::resize(int size) {
	T* arr = new T[this->size];
	for (int i = 0; i < this->size; i++) arr[i] = data[i];

	delete[] data;
	data = new T[size + 1];
	if (size >= this->size)
		for (int i = 0; i < this->size; i++) data[i] = arr[i];
	else
		for (int i = 0; i < size; i++) data[i] = arr[i];

	this->size = size;
	//배열의 사이즈 변경
	//줄어들때는 맨 뒤부터 사라짐
}
template <typename T>void MyArray<T>::push(T& x) {
	resize(size + 1);
	data[size - 1] = x;
	//배열의 마지막에 요소 추가
}
template <typename T>T MyArray<T>::pop() {
	int x = data[size - 1];
	resize(size - 1);
	return x;
	//배열의 마지막 요소 반환과 삭제
}
template <typename T>void MyArray<T>::insert(int idx, T& x) {
	T* arr = new T[size - idx];
	for (int i = 0; i < size - idx; i++) arr[i] = data[idx + i];

	resize(size + 1);
	data[idx] = x;
	for (int i = 0; i < size - idx - 1; i++) data[idx + i + 1] = arr[i];

	delete[] arr;
}

template <typename T>void MyArray<T>::erase(int idx) {
	int sizeL = idx, sizeR = size - idx + 1;
	T* a1 = new T[sizeL];
	T* a2 = new T[sizeR];

	for (int i = 0; i < sizeL; i++) a1[i] = data[i];
	for (int i = 0; i < sizeR; i++) a2[i] = data[idx + i - 1];

	resize(size - 1);

	{
		int i;
		for (i = 0; i < sizeL; i++) data[i] = a1[i];
		for (; i < sizeR; i++) data[i] = a2[i];
	}
	delete[] a1;
	delete[] a2;
	//배열의 중간 요소 삭제
}

template <typename T>int MyArray<T>::length() {
	return size;
}

template <typename T>T& MyArray<T>::operator[](int i) {
	try {
		if (i >= size) throw "Out Of Range!!";
		else if(i < 0) return data[size + i];
		else return data[i];
	}
	catch (string i) {
		cerr << "Error message : " << i;
		exit(EXIT_SUCCESS);
	}
}
template <typename T>bool MyArray<T>::operator== (MyArray<T>& a2) {
	if (this->size != a2.size) return false;
	else {
		for (int i = 0; i < size; i++) {
			if (this->data[i] != a2.data[i]) return false;
		}
	}
	return true;
}
template <typename T>bool MyArray<T>::operator!= (MyArray<T>& a2) {
	if (this->size != a2.size) return true;
	else {
		for (int i = 0; i < size; i++) {
			if (this->data[i] != a2.data[i]) return true;
		}
	}
	return false;
}
template <typename T>void MyArray<T>::operator= (const MyArray<T>& a2) {
	this->resize(a2.size);
	for (int i = 0; i < size; i++) {
		this->data[i] = a2.data[i];
	}
}

template <typename T>void MyArray<T>::operator+= (const MyArray<T>& a2) {
	resize(size + a2.size);
	for (int i = 0; i < a2.size; i++) {
		data[i + size - a2.size] = a2.data[i];
	}
}
template <typename T>
ostream& operator<<(ostream& os, const MyArray<T>& a) {
	if (a.size == 0) os << "[]";
	else {
		os << "[ ";
		for (int i = 0; i < a.size - 1; i++) {
			os << a.data[i] << ", ";
		}
		os << a.data[a.size - 1] << " ]";
	}
	return os;
}
ostream& operator<<(ostream& os, const MyArray<string>& a) {
	if (a.size == 0) os << "[]";
	else {
		os << "[ ";
		for (int i = 0; i < a.size - 1; i++) {
			os << "\"" << a.data[i] << "\", ";
		}
		os << "\"" << a.data[a.size - 1] << "\" ]";
	}
	return os;
}
ostream& operator<<(ostream& os, const MyArray<char>& a) {
	if (a.size == 0) os << "[]";
	else {
		os << "[ ";
		for (int i = 0; i < a.size - 1; i++) {
			os << "\'" << a.data[i] << "\', ";
		}
		os << "\'" << a.data[a.size - 1] << "\' ]";
	}
	return os;
}