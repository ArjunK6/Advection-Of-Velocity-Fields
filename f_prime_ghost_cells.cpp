/-----------------------------------------------------
// Arjun Kochhar, Feb 2023
//
// Program to initialize non-ghost cells in a 1d-grid
// and calculate the derivative of a function.
//-----------------------------------------------------

#include <iostream>
#include <vector>
#include <iomanip>


// function
float f_x(float x)
{
    return x * x;
}

// create vectors
const int N = 30;

// initalize vectors
void initalize_x(float low, float high, int N,
                                std::vector<float>& x_vec)
{
    auto dl = (high - low) / N;
    for (int i = 1; i <= N; i++)
    {
        auto j = low + i * dl;
        x_vec[i] = j -  dl / 2;
    }
}

// initalize vectors
void initalize_y(const std::vector<float>& x_vec,
                                std::vector<float>& y_vec)
{
    for (int i = 1; i <= N; i++)
    {
        y_vec[i] = f_x(x_vec[i]);
    }
}

// initalize ghost cells

void initalize_ghost_cells(std::vector<float>& vec)
{
    vec[0] = vec[1];
    auto n = vec.size() - 2;
    vec[n + 1] = vec[n];
}

void numerically_calculate_derivative(const std::vector<float>& x,
                                        const std::vector<float>& y,
                                        std::vector<float>& z)
{
    for (int i = 1; i <= N; i++)
    {
        auto dx = x[i + 1] - x[i - 1];
        auto dy = y[i + 1] - y[i - 1];
        auto derivative = dy / dx;
        z[i] = derivative;
    }
}                                    

void print_vector(const std::vector<float> &vec)
{
    // max of ten values in one line
    std::cout << std::fixed << std::setprecision(3);
    int count = 1;
    for (auto i: vec)
    {
        if ((count % 10) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << i << ", ";
        count++;
    }
    std::cout << std::endl;
}

void print_vectors(const std::vector<float> &x_vec,
    const std::vector<float> &y_vec,
    const std::vector<float> &z_vec)
{
    // print vectors
    std::cout << "X VECTOR: ";
    print_vector(x_vec);

    std::cout << "Y VECTOR: ";
    print_vector(y_vec);

    std::cout << "Z VECTOR: ";
    print_vector(z_vec);
}

int main()
{
    // initalize vectors:
    std::vector<float> x_vec(N + 2);
    std::vector<float> y_vec(N + 2);
    std::vector<float> z_vec(x_vec.size());    

    initalize_x(-2, 2, N, x_vec);
    initalize_y(x_vec, y_vec);
    std::cout << "Cells before ghost cell initialization" << std::endl;
    print_vectors(x_vec, y_vec, z_vec);
    std::cout << std::endl << std::endl;

    initalize_ghost_cells(x_vec);
    initalize_ghost_cells(y_vec);
    numerically_calculate_derivative(x_vec, y_vec, z_vec);

    std::cout << "Cells after ghost cell initialization" << std::endl;
    print_vectors(x_vec, y_vec, z_vec);

    return 0;
}

