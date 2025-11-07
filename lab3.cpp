#include <iostream>
#include <utility>
#include "pch.h"
#include "sort.h"
#include <cstdlib>

using namespace std;

int main()
{
	int a[100];

	for (int i = 0; i < 100; i++) {
		a[i] = rand() % 100 + 100;
	}

	cout << "massive:\n";
	for (int i = 0; i < 100; i++) {
		cout << a[i] << "\t";
	}
	cout << "\n\n";

	Sort(a, a + 100, [](int a, int b) { return a < b; });

	cout << "sort:\n";
	for (int i = 0; i < 100; i++) {
		cout << a[i] << "\t";
	}
	cout << "\n";

}