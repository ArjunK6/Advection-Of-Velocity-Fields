#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


float linear_interpolate(float x1, float x2, float y1, float y2, float x)
{
    float t = (x - x1) / (x2 - x1);
    float y = (1 - t) * y1 + t * y2;
    return y;
}

int index(int x, int y, int N)
{
    return y * (N + 2) + x;
}

void initialize_sin_wave_velocity_field(std::vector<float>& u_vec, 
                                        std::vector<float>& v_vec, float amplitude, int N)
{
    float pi = 3.1415926535897932384626433832795;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {        
            float angle = linear_interpolate(1, N, 0, (6 * pi), i);
            float tx = 1;
            float ty = amplitude * cos(angle);          

            // normalize tangent vectors
            float len = sqrt((tx * tx) + (ty * ty));
            tx /= len;
            ty /= len;

            u_vec[index(i, j, N)] = tx;
            v_vec[index(i, j, N)] = ty;
        }
    }
}    

void print_grid(const std::vector<float>& vec, int N)
{
    std::cout << std::fixed << std::setprecision(3); 
    for (int count = 0; auto i: vec)
    {
        std::cout << i << ", ";
        ++count;
        if (count % (N + 2) == 0)
            std::cout << std::endl;
    }
    std::cout << "----------------------------------" << std::endl << std::endl;
}

int main()
{
    int N = 6;
    std::vector<float> u_vec ((N + 2) * (N + 2));
    std::vector<float> v_vec (u_vec.size());
    float amplitude = 4.0f;

    initialize_sin_wave_velocity_field(u_vec, v_vec, amplitude, N);

    std::cout << "U_VEC: " << std::endl;
    print_grid(u_vec, N);

    std::cout << "V_VEC: " << std::endl;
    print_grid(v_vec, N);
    return 0
}