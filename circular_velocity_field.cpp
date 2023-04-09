#include <iostream>
#include <cmath>
#include <vector>

int index(int x, int y, int N)
{
    return y * (N + 2) + x;
}

void initialize_circular_velocity_field(std::vector<float>& u_grid, 
                                            std::vector<float>& v_grid, int N)
{
    float ox = N / 2; float oy = N/2;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            // (s, t) is the radial vector from the center of the cell (i, j) 
            // to the center of the grid (N / 2, N / 2)
            float s = i - N / 2;
            float t = j = N / 2;

            // normalize 
            float len = sqrt(s * s + t * t);

            if (len == 0)
            {
                s = 1;
                t = 0;
            }
            else 
            {
                s = s / len;
                t = t / len;
            }

            // create tangent vector on the circle by swapping x & y components of the 
            // radial vector

            float tx = -t; 
            float ty = s;

            u_grid[index(i, j, N)] = tx;
            v_grid[index(i, j, N)] = ty;
        }
    }
}

int main()
{
    return 0;
}