#include <iostream>

int sum(int, int);

void main(void) {
	int x, y;

	printf("Enter value x & y: ");
	scanf_s("%d%d", &x, &y);

	std::cout << "Sum: " << x << " + " << y << " = " << sum(x,y)  << std::endl;
	//return 0;
}

int sum(int x, int y) {
	return x + y;
}