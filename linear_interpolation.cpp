#include <iostream>
#include <cassert>

float linear_interpolate(float x1, float x2, float y1, float y2, float x)
{
	float t = (x - x1) / (x2 - x1);
	float y = (1 - t) * y1 + (t * y2);
	return y;
}

void test1_linear_interpolate()
{
	// Test on a line where x & y coordinates are the same;
	// This line makes a 45 degree angle with the x-axis;

	float x = 0.5f;
	float y = linear_interpolate(0, 1, 0, 1, x);
	float epsilon = 0.000001;

	bool pass = (y - x) < epsilon || (x - y) < epsilon;
	assert(pass);

	std::cout << "Passed" << std::endl;
}

int main()
{
	test1_linear_interpolate();
	return 0;
}