#include <iostream>
#include <vector>

int index(int x, int y, int N)
{
    return y * (N + 2) + x;
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

            // pull back from ghost cells
            if (qx < 0.5)
                qx = 0.5;
            if (qx > N + 0.5)
                qx = N + 0.5;
            if (qy < 0.5)
                qy = 0.5;
            if (qy > N + 0.5)
                qy = N + 0.5;

            // convert back to index coordiantes
            qx /= h;
            qy /= h;

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

int main()
{
    return 0;
}