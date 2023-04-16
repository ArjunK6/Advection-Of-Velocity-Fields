#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <vector>

const int Nframes = 100;
const int N = 256;
const float dt = 0.01;

int index(int x, int y, int N)
{
    return y * (N + 2) + x;
}

// void initalize_ghost_cells(std::vector<float>& grid)
// {
    
// }

std::string fileName(int frameN) 
{
    std::ostringstream stream;
    stream << "density_" << std::setw(4) << std::setfill('0') <<
        frameN << ".txt";
    return stream.str();
}

void save_grid(int frameN, const std::vector<float>& densities, 
                        const std::string& dirName, int N)
{
    if (!std::filesystem::exists(dirName))
        std::filesystem::create_directory(dirName);

    std::string file_name = fileName(frameN);
    std::string file_path = dirName + "/" + file_name;
    std::ofstream file{file_path};
    if (!file.good())
    {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }
    for (int row = 1; row <= N; ++row)
    {
        for (int col = 1; col <= N; ++col)
        {
            file << densities[index(col, row, N)] << "  ";
        }
        file << std::endl;
    }   
}

float linear_interpolate(float x1, float x2, float y1, float y2, float x)
{
	float t = (x - x1) / (x2 - x1);
	float y = (1 - t) * y1 + (t * y2);
	return y;
}

float bilinearly_interpolate(float x11, float x12, float x21, float x22, 
                                float y11, float y12, float y21, float y22, float v1, 
                                    float v2, float v3, float v4, float x, float y)
{
    float w1 = linear_interpolate(x11, x12, v1, v2, x);
    float w2 = linear_interpolate(x21, x22, v3, v4, x);

    float w = linear_interpolate(y11, y21, w1, w2, y);
    return w;
}

void advect_densities(float h, float dt, int N, const std::vector<float>& u_grid,
                         const std::vector<float>& v_grid, const std::vector<float>& old_density_grid, 
                            std::vector<float>& new_density_grid)
{
    for (int x = 1; x <= N; ++x)
    {
        for (int y = 1; y <= N; ++y)
        {
            float u = u_grid[index(x, y, N)];
            float v = v_grid[index(x, y, N)];

            float qx = (x * h) - (u * dt);
            float qy = (y * h) - (v * dt);

            // convert to index based
            qx /= h;
            qy /= h;
            
            // pull back from ghost cells
            if (qx < 0.5)
                qx = 0.5;
            if (qx > N + 0.5)
                qx = N + 0.5;
            if (qy < 0.5)
                qy = 0.5;
            if (qy > N + 0.5)
                qy = N + 0.5;

        
            // billinearly interpoalte density
            int x11 = int(floor(qx));
            int x12 = x11 + 1;
            int x21 = x11;
            int x22 = x12;
            
            int y11 = int(floor(qy));
            int y21 = y11 + 1;
            int y12 = y11;
            int y22 = y21;

            float d1 = old_density_grid[index(x11, y11, N)];
            float d2 = old_density_grid[index(x12, y12, N)];
            float d3 = old_density_grid[index(x21, y21, N)];
            float d4 = old_density_grid[index(x22, y22, N)];

            float density = bilinearly_interpolate(x11, x12, x21, x22, y11, y12, y21, y22, 
                                                    d1, d2, d3, d4, qx, qy);
            new_density_grid[index(x, y, N)] = density;
        }
    }
}

void initalize_ghost_cells_velocity(std::vector<float>& u_grid, 
                                    std::vector<float>& v_grid, int N)
{
    for (int x = 1; x <= N; ++x)
    {
        u_grid[index(x, 0, N)] = u_grid[index(x, 1, N)];
        u_grid[index(x, N + 1, N)] = u_grid[index(x, N, N)];

        v_grid[index(x, 0, N)] = -v_grid[index(x, 1, N)];
        v_grid[index(x, N + 1, N)] = -v_grid[index(x, N, N)];
    }
    
    for (int y = 1; y <= N; ++y)
    {
        u_grid[index(0, y, N)] = -u_grid[index(1, y, N)];
        u_grid[index(N + 1, y, N)] = -u_grid[index(N, y, N)];

        v_grid[index(0, y, N)] = v_grid[index(1, y, N)];
        v_grid[index(N + 1, y, N)] = v_grid[index(N, y, N)];
    }

    u_grid[index(0, 0, N)] = (u_grid[index(1, 0, N)] + u_grid[index(0, 1, N)]) / 2;
    u_grid[index(0, N +  1, N)] = (u_grid[index(1, N + 1, N)] + u_grid[index(0, N, N)]) / 2;
    u_grid[index(N + 1, N + 1, N)] = (u_grid[index(N + 1, N, N)] + u_grid[index(N, N + 1, N)]) / 2;
    u_grid[index(N + 1, 0, N)] = (u_grid[index(N, 0, N)] + u_grid[index(N + 1, 1, N)]) / 2;

    v_grid[index(0, 0, N)] = (v_grid[index(1, 0, N)] + v_grid[index(0, 1, N)]) / 2;
    v_grid[index(0, N +  1, N)] = (v_grid[index(1, N + 1, N)] + v_grid[index(0, N, N)]) / 2;
    v_grid[index(N + 1, N + 1, N)] = (v_grid[index(N + 1, N, N)] + v_grid[index(N, N + 1, N)]) / 2;
    v_grid[index(N + 1, 0, N)] = (v_grid[index(N, 0, N)] + v_grid[index(N + 1, 1, N)]) / 2;
}

// Initalize velocity fields

void create_circular_vel_field(int N, std::vector<float>& u_grid,
                                std::vector<float>& v_grid)
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

            u_grid[index(x, y, N)] = tx;
            v_grid[index(x, y, N)] = ty;
        }
    }
    initalize_ghost_cells_velocity(u_grid, v_grid, N);
}

void initialize_sin_wave_velocity_field(std::vector<float>& u_vec, 
                                        std::vector<float>& v_grid, float amplitude, int N)
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
            v_grid[index(i, j, N)] = ty;
        }
    }
    initalize_ghost_cells_velocity(u_vec, v_grid, N);
}    

void create_double_circular_vel_field(int N, std::vector<float>& u_vec,
                                std::vector<float>& v_grid)
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
            v_grid[index(x, y, N)] = ty;
        }
    }
    initalize_ghost_cells_velocity(u_vec, v_grid, N);
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
    initalize_ghost_cells_velocity(u_grid, v_grid, N);
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


void simulate_advection(const std::string& output_dir, const std::vector<float>& u_grid, 
    const std::vector<float>& v_grid, std::vector<float> density_grid1)
{
    std::vector<float> density_grid2 (density_grid1.size());
    float h = 1.0f / N;

    for (int frame = 0; frame <= Nframes; ++frame)
    {
        save_grid(frame, density_grid1, output_dir, N);   
        advect_densities(h, dt, N, u_grid, v_grid, density_grid1, density_grid2);
        density_grid1 = density_grid2;
    }
}

void simulate_constant_vel_field()
{
    std::vector<float> u_grid ((N + 2) * (N + 2));
    std::vector<float> v_grid ((N + 2) * (N + 2));
    initalize_constant_vel_field(u_grid, v_grid, N);

    std::vector<float> density_grid1 ((N + 2) * (N + 2));
    density_grid1[index(2, N/2, N)] = 1;

    simulate_advection("Const_Vel_Field", u_grid, v_grid, density_grid1);
}

void simulate_circular_vel_field()
{
    std::vector<float> u_grid ((N + 2) * (N + 2));
    std::vector<float> v_grid ((N + 2) * (N + 2));
    create_circular_vel_field(N, u_grid, v_grid);

    std::vector<float> density_grid1 ((N + 2) * (N + 2));
    density_grid1[index(178, N/2, N)] = 1;

    simulate_advection("Circular_Vel_Field", u_grid, v_grid, density_grid1);
}

void simiulate_sin_wave_vel_field()
{
    std::vector<float> u_grid ((N + 2) * (N + 2));
    std::vector<float> v_grid ((N + 2) * (N + 2));
    initialize_sin_wave_velocity_field(u_grid, v_grid, 4, N);

    std::vector<float> density_grid1 ((N + 2) * (N + 2));
    density_grid1[index(20, 150, N)] = 1;

    simulate_advection("Sin_Wave_Vel_Field", u_grid, v_grid, density_grid1);
}

void simulate_double_speed_circular_vel_field()
{
    std::vector<float> u_grid ((N + 2) * (N + 2));
    std::vector<float> v_grid ((N + 2) * (N + 2));
    create_double_circular_vel_field(N, u_grid, v_grid);

    std::vector<float> density_grid1 ((N + 2) * (N + 2));
    density_grid1[index(128+50, N / 2, N)] = 1;
    density_grid1[index(128+100, N / 2, N)] = 1;


    simulate_advection("Double_Speed_Circular_Vel_Field", u_grid, v_grid, density_grid1);
}

int main()
{
    // simulate_constant_vel_field();
    // simulate_circular_vel_field();
    // simiulate_sin_wave_vel_field();
    simulate_double_speed_circular_vel_field();
    return 0;
}
