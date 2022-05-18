#include "MyArray.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>void MyArray<T>::resize(int size) {
	int* arr = new int[this->size + 1];
	for (int i = 0; i < this->size; i++) arr[i] = data[i];

	delete[] data;
	data = new int[size + 1];
	for (int i = 0; i < size; i++) data[i] = 0;
	if (size >= this->size)
		for (int i = 0; i < this->size; i++) data[i] = arr[i];
	else
		for (int i = 0; i < size; i++) data[i] = arr[i];

	this->size = size;
	//배열의 사이즈 변경
	//줄어들때는 맨 뒤부터 사라짐
}
template <class T>void MyArray<T>::print() {
	for (int i = 0; i < size; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
	//1 2 3 4 형식으로 배열을 한줄로 출력함
}
template <class T>void MyArray<T>::push(int x) {
	resize(size + 1);
	data[size - 1] = x;
	//배열의 마지막에 요소 추가
}
template <class T>T MyArray<T>::pop() {
	int x = data[size - 1];
	resize(size - 1);
	return x;
	//배열의 마지막 요소 반환과 삭제
}
template <class T>void MyArray<T>::insert(int x) {

}
template <class T>void MyArray<T>::erase(int x) {
	int sizeL = x, sizeR = size - x + 1;
	int* a1 = new int[sizeL];
	int* a2 = new int[sizeR];

	for (int i = 0; i < sizeL; i++) a1[i] = data[i];
	for (int i = 0; i < sizeR; i++) a2[i] = data[x + i - 1];

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
template <class T>int MyArray<T>::length() {
	return size;
}

template <class T>T& MyArray<T>::operator[](int i) {
	try {
		if (i >= size) throw "Out Of Range!!";
		else return data[i];
	}
	catch (string i){
		cerr << "Error message : " << i;
		exit(EXIT_SUCCESS);
	}
}
template <class T>bool MyArray<T>::operator== (MyArray<T>& a2) {
	if (this->size != a2.size) return false;
	else {
		for (int i = 0; i < size; i++) {
			if (this->data[i] != a2.data[i]) return false;
		}
	}
	return true;
}
template <class T>bool MyArray<T>::operator!= (MyArray<T>& a2) {
	if (this->size != a2.size) return true;
	else {
		for (int i = 0; i < size; i++) {
			if (this->data[i] != a2.data[i]) return true;
		}
	}
	return false;
}
template <class T>void MyArray<T>::operator= (const MyArray<T>& a2) {
	this->resize(a2.size);
	for (int i = 0; i < size; i++) {
		this->data[i] = a2.data[i];
	}
}
 
//MyArray MyArray::operator+ (const MyArray& a2) {
//	MyArray result(size + a2.size);
//	for (int i = 0; i < result.size; i++) {
//		if (i < size) result.data[i] = this->data[i];
//		else result.data[i] = a2.data[i - size];
//	}
//	return result;
//}
template <class T>void MyArray<T>::operator+= (const MyArray<T>& a2) {
	resize(size + a2.size);
	for (int i = 0; i < a2.size; i++) {
		data[i + size - a2.size] = a2.data[i];
	}
}