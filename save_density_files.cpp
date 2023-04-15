#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
/* 0001.txt*/
int index(int x, int y, int N)
{
    return y * (N + 2) + x;
}

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

void test1_save_density_files(int N, int frameN, const std::string& dirName)
{
    std::vector<float> densities((N + 2) * (N + 2));
    for (int row = 1; row <= N; ++row)
    {
        for (int col = 1; col <= N; ++col)
        {
            densities[index(col, row, N)] = col;
        }
    }
    std::string f_name = fileName(frameN);
    save_grid(frameN, densities, dirName, N);
}

int main()
{
    int N = 3;
    test1_save_density_files(N, 1, "test_dir");
    return 0;
}