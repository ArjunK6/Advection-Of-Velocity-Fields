#include <iostream>
#include <cassert>

float linear_interpolate(float x1, float x2, float y1, float y2, float x)
{
	float t = (x - x1) / (x2 - x1);
	float y = (1 - t) * y1 + (t * y2);
	return y;
}

float bilinearly_interpolate(float x11, float x12, float x21, float x22, 
                                float y11, float y12, float y21, float y22,
                                float v1, float v2, float v3, float v4, float x, float y)
{
    // x_ij means x-coordinate on ith row and jth column
    float w1 = linear_interpolate(x11, x12, v1, v2, x);
    float w2 = linear_interpolate(x21, x22, v3, v4, x);

    float w = linear_interpolate(y11, y21, w1, w2, y);
    return w;
}

void test1_bilinear_interpolate()
{
    float x11 = 10; float x12 = 20; 
    float x21 = 10; float x22 = 20;

    float y11 = 5; float y12 = 5;
    float y21 = 10; float y22 = 10;

    float v1 = 0; float v2 = 10;
    float v3 = 30; float v4 = 40;
    
    float x = x11; float y = y11;

    float epsilon = 0.000001f;

    // Test that bilinear interpolated value at the lower left corner is = to v1;
    float value = bilinearly_interpolate(x11, x12, x21, x22, y11, y12, y21, y22, 
                                            v1, v2, v3, v4, x, y);
    bool pass = (value - 0) < epsilon || (0 - value) < epsilon;
    assert(pass);

    std::cout << "Test 1: Passed" << std::endl;      
}

void test2_bilinear_interpolate()
{
    float x11 = 10; float x12 = 20; 
    float x21 = 10; float x22 = 20;

    float y11 = 5; float y12 = 5;
    float y21 = 10; float y22 = 10;

    float v1 = 0; float v2 = 10;
    float v3 = 30; float v4 = 40;
    
    float x = x12; float y = y12;

    float epsilon = 0.000001f;

    // Test that bilinear interpolated value at the bottom right corner is = v2
    float value = bilinearly_interpolate(x11, x12, x21, x22, y11, y12, y21, y22, 
                                            v1, v2, v3, v4, x, y);
    bool pass = (value - v2) < epsilon || (v2 - value) < epsilon;
    assert(pass);

    std::cout << "Test 2: Passed" << std::endl;      
}

void test3_bilinear_interpolate()
{
    float x11 = 10; float x12 = 20; 
    float x21 = 10; float x22 = 20;

    float y11 = 5; float y12 = 5;
    float y21 = 10; float y22 = 10;

    float v1 = 0; float v2 = 10;
    float v3 = 30; float v4 = 40;
    
    float x = x21; float y = y21;

    float epsilon = 0.000001f;

    // Test that bilinear interpolated value at the top left corner is = to v3;
    float value = bilinearly_interpolate(x11, x12, x21, x22, y11, y12, y21, y22, 
                                            v1, v2, v3, v4, x, y);
    bool pass = (value - v3) < epsilon || (v3 - value) < epsilon;
    assert(pass);

    std::cout << "Test 3: Passed" << std::endl;      
}

void test4_bilinear_interpolate()
{
    float x11 = 10; float x12 = 20; 
    float x21 = 10; float x22 = 20;

    float y11 = 5; float y12 = 5;
    float y21 = 10; float y22 = 10;

    float v1 = 0; float v2 = 10;
    float v3 = 30; float v4 = 40;
    
    float x = x22; float y = y22;

    float epsilon = 0.000001f;

    // Test that bilinear interpolated value at the top right corner is = to v4;
    float value = bilinearly_interpolate(x11, x12, x21, x22, y11, y12, y21, y22, 
                                            v1, v2, v3, v4, x, y);
    bool pass = (value - v4) < epsilon || (v4 - value) < epsilon;
    assert(pass);

    std::cout << "Test 4: Passed" << std::endl;      
}

void test5_bilinear_interpolate()
{
    float x11 = 10; float x12 = 20; 
    float x21 = 10; float x22 = 20;

    float y11 = 5; float y12 = 5;
    float y21 = 10; float y22 = 10;

    float v1 = 0; float v2 = 10;
    float v3 = 30; float v4 = 40;
    
    float x = x22; float y = y22;

    float epsilon = 0.000001f;

    /* Test that at the center of the rectangle, the bilinear interpolated value is: 
          w1 = (v1 + v2) / 2 = 5;
          w2 = (v3 + v4) / 2 = 35;
          w = (w1 + w2) / 2 = 20;
    */
    float value = bilinearly_interpolate(x11, x12, x21, x22, y11, y12, y21, y22, 
                                            v1, v2, v3, v4, x, y);
    float expected = 20;
    bool pass = (value - expected) < epsilon || (expected - value) < epsilon;
    assert(pass);

    std::cout << "Test 5: Passed" << std::endl;      
}

int main()
{
	test1_bilinear_interpolate();
    test2_bilinear_interpolate();

    test3_bilinear_interpolate();
    test4_bilinear_interpolate();
    
    test5_bilinear_interpolate();
    
	return 0;
}