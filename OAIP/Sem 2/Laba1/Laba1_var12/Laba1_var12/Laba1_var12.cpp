#include <iostream>


using namespace std;

double Multiply(int n) {
	double f = 1;

	for (int i = 1; i <= n; i++) {
		// (2i*2i)/((2i-1)*(2i+1)) = 4i^2 / (4i^2 - 1)
		f *= 4. * i * i / (4 * i * i - 1); 
	}
	return f;
}

double Multiply_R(int n) {
	if (n < 1) return 1;
	else {
		return 4. * n * n / (4 * n * n - 1) * Multiply_R(n - 1);
	}
	
}

void main(void) {
	int n, kod;
	while (true) {
		cout << "Input n: ";
		cin >> n;
		cout << "\nRecurs - 1\nNon-recurs - 0\nElse - Exit" << endl;
		cin >> kod;
		switch (kod) {
		case 0:
			cout << "Non-recursive function result: " << Multiply(n) << endl;
			break;
		case 1:
			cout << "Recursive function result: " << Multiply_R(n) << endl;
			break;
		default: return;
		}
	}
}