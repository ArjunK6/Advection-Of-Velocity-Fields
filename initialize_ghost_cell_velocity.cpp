#include <iostream>
#include <vector>
#include <iomanip>

auto N = 2;

int index(int y, int x)
{
    return y * (N + 2) + x;
}
    
void initalize_non_ghost_cells(std::vector<float>& vec)
{
    for (int x = 1; x <= N; ++x)
    {
        for (int y = 1; y <= N; ++y)
            vec[index(x, y)] = 1;
    }
}

void initalize_ghost_cells_velocity(std::vector<float>& u_vec, 
                                    std::vector<float>& v_vec)
{
    for (int x = 1; x <= N; ++x)
    {
        u_vec[index(x, 0)] = u_vec[index(x, 1)];
        u_vec[index(x, N + 1)] = u_vec[index(x, N)];

        v_vec[index(x, 0)] = -v_vec[index(x, 1)];
        v_vec[index(x, N + 1)] = -v_vec[index(x, N)];
    }
    
    for (int y = 1; y <= N; ++y)
    {
        v_vec[index(0, y)] = u_vec[index(1, y)];
        v_vec[index(N + 1, y)] = u_vec[index(N, y)];

        u_vec[index(0, y)] = -v_vec[index(1, y)];
        u_vec[index(N + 1, y)] = -v_vec[index(N, y)];
    }
}

void print_grid(std::vector<float>& vec)
{
    for (int y = 0; y < N + 2; ++y)
    {
        for (int x = 0; x < N + 2; ++x)
        {
            std::cout << vec[index(x, y)] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    // initalize vectors
    std::vector<float> u_vec((N + 2) * (N + 2));
    std::vector<float> v_vec((N + 2) * (N + 2));

    initalize_non_ghost_cells(u_vec);
    initalize_non_ghost_cells(v_vec);

    std::cout << "U vector without ghost cell initialization:" << std::endl;
    print_grid(u_vec);

    std::cout << "V  vector without ghost cell initialization:" << std::endl;
    print_grid(v_vec);

    initalize_ghost_cells_velocity(u_vec, v_vec);
    
    std::cout << "U vector after initialization of ghost cells" << std::endl;
    print_grid(u_vec);

    std::cout << "V vector after initialization of ghost cells" << std::endl;
    print_grid(v_vec);
    return 0;
}