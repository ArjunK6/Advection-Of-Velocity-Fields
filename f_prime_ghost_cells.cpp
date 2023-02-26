//-----------------------------------------------------
// Arjun Kochhar, Feb 2023
//
// Program to initialize non-ghost cells in a 2d grid
//-----------------------------------------------------

#include <iostream>
#include <vector>
#include <iomanip>

const int N = 2;
std::vector<float> vec((N + 2) * (N + 2));

int index(float x, float y)
{
    return y * (N+2) + x;
}

void initalize_non_ghost_cells(std::vector<float>& vec)
{
    for (int x = 1; x <= N; ++x)
    {
        for (int y = 1; y <= N; ++y)
            vec[index(x, y)] = 1;
    }
}

void initalize_ghost_cells(std::vector<float>& vec)
{
    for (int x = 1; x <= N; ++x)
    {
        vec[index(x, 0)] = vec[index(x, 1)];
        vec[index(x, N + 1)] = vec[index(x, N)];
    }

    for (int y = 1; y <= N; ++y)
    {
        vec[index(0, y)] = vec[index(1, y)];
        vec[index(N + 1, y)] = vec[index(N, y)];
    }

    // initalize corners
    vec[index(0, 0)] = (vec[index(1, 0)] + vec[index(0, 1)]) / 2;
    vec[index(0, N +  1)] = (vec[index(1, N + 1)] + vec[index(0, N)]) / 2;
    vec[index(N + 1, N + 1)] = (vec[index(N + 1, N)] + vec[index(N, N + 1)]) / 2;
    vec[index(N + 1, 0)] = (vec[index(N, 0)] + vec[index(N + 1, 1)]) / 2;
}

void print_grid(const std::vector<float>& vec)
{
    std::cout << std::fixed << std::setprecision(3); 
    std::cout << "vec size = " << vec.size() << std::endl;
    for (int count = 0; auto i: vec)
    {
        std::cout << i << ", ";
        ++count;
        if (count % (N + 2) == 0)
            std::cout << std::endl;
    }
}

int main()
{
    initalize_non_ghost_cells(vec);
    std::cout << "Grid with out ghost cell initialization" << std::endl;
    print_grid(vec);

    std::cout << "------------------------" << std::endl;
    initalize_ghost_cells(vec);

    std::cout << "Grid with ghost cell initialization" << std::endl;
    print_grid(vec);

    return 0;
}
