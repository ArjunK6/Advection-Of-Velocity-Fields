#include <iostream>
#include <vector>
#include <iomanip>

int index(int x, int y, int N)
{
    return y * (N + 2) + x;
}

void initalize_constant_vel_field(std::vector<float>& u_grid,
                                    std::vector<float>& v_grid, int N)
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            u_grid[index(i, j, N)] = 1;
            v_grid[index(i, j, N)] = 0;
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
    int N = 4;
    std::vector<float> u_grid ((N + 2) * (N + 2));
    std::vector<float> v_grid ((N + 2) * (N + 2));
    initalize_constant_vel_field(u_grid, v_grid, N);

    std::cout << "U GRID: " << std::endl;
    print_grid(u_grid, N);

    std::cout << "------------------------" << std::endl;

    std::cout << "V GRID: " << std::endl;
    print_grid(v_grid, N);

}