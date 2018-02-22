
#include <iostream>
#include <vector>

using namespace std;

int fibonacci(int n) {
	if (n <= 1) {
		return n;
	}

	int a = 0;
	int b = 1;

	for (int i = 2; i <= n; i++) {
		int c = a + b;
		a = b;
		b = c;
	}
	return b;
}

int fibonacciRic(int n, int a = 0, int b = 1, int i = 1) {
	if (n <= 1) {
		return n;
	}
	if (i == n) {
		return b;
	}
	return fibonacciRic(n, b, a + b, i + 1);
}

int fibonacciVecRic(int n, vector<int>* values = nullptr) {
	if (values == nullptr) {
		values = new vector<int>(n + 1, -1);
		(*values)[1] = 0;
		(*values)[2] = 1;
	}

	if ((*values)[n] == -1) {
		(*values)[n] = fibonacciVecRic(n - 1, values) + fibonacciVecRic(n - 2, values);
	}
	return (*values)[n];
}

int domino(int n) {
	// return fibonacciRic(n+2);
	return fibonacciVecRic(n + 2);
	// return fibonacci(n+2);
}

int main(int len, char* argv[]) {
	cout << fibonacciRic(stoi(argv[1]));

	return 0;
}