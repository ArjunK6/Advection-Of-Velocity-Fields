#include <iostream>
#include <vector>
#include <cmath>

int index(int x, int y, int N)
{
    return y * N + x;
}

void create_circular_vel_field(int N, std::vector<float>& u_vec,
                                std::vector<float>& v_vec)
{
    float center_x = N / 2;
    float center_y = N / 2;

    for (int x = 1; x <= N; ++x)
    {
        for (int y = 1; y <= N; ++y)
        {
            //find vector from center of the grid to (x, y)
            float vx = x - center_x;
            float vy = y - center_y;

            /* swap (x, y) components to create the tangent vector
            at (x, y), the center of the cell */

            float tx = -vy;
            float ty = vx;

            // normalize the vectors
            float len_tangent = sqrt(tx * tx + ty * ty);

            tx /= len_tangent;
            ty /= len_tangent;

            u_vec[index(x, y, N)] = tx;
            v_vec[index(x, y, N)] = ty;
        }
    }
}

int main()
{
    return 0;
}