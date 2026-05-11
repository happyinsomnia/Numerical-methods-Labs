#include <gridIO.hpp>
#include <fstream>

void SaveGrid(const std::string &path, const Grid &grid)
{
    std::ofstream file(path);
    
    if (!file.is_open())
    {
        std::cout << " Couldn't open file by path " + path << std::endl;
        return;
    }

    file << " x:   y: " << '\n';

    for (size_t i = 0; i < grid.x.size(); i++)
    {
        file << grid.x[i] << "   " << grid.y[i] << '\n';
    }
}
