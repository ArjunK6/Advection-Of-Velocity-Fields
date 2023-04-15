#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

int index(int x, int y, int N)
{
    return y * (N + 2) + x;
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
            
            if (len_tangent == 0)
            {
                tx = 1;
                ty = 0;
            }
            else
            {
                tx /= len_tangent;
                ty /= len_tangent;
            }

            // I want to advect 2 densities under two velocity fields with different speeds 
            // and see how it behaves
            if (len_tangent > N / 4)
            {
                tx *= 2; 
                ty *= 2;
            }
            u_vec[index(x, y, N)] = tx;
            v_vec[index(x, y, N)] = ty;
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
    int N = 8;
    std::vector<float> u_grid((N + 2) * (N + 2));
    std::vector<float> v_grid((N + 2) * (N + 2));
    print_grid(u_grid, N);
    print_grid(v_grid, N);

    create_circular_vel_field(N, u_grid, v_grid);

    print_grid(u_grid, N);
    print_grid(v_grid, N);

    return 0;
}
