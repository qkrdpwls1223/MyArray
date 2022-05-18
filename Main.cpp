#include "MyArray.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	MyArray<int> a1(4,0);
	cout << a1 << endl;
	MyArray< MyArray<int> > a2(4, a1);
	a2.push(a1);
	cout << a2 << endl;
	return 0;
}