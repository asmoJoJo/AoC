#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int findPartNumbers(const std::vector<std::string>& vs, int x, int y)
{
    int sum = 0, number = 0;
    bool digitFound = false;
    for(int i = y - 1; i < y + 2; ++i)
    {
        for(int j = x - 1; j < x + 2; ++j)
        {
            if(isdigit(vs[i][j]))
            {
                if(!digitFound)
                {
                    digitFound = true;
                    int index = 1;
                    char c = vs[i][j-index];
                    while(isdigit(c))
                    {
                        ++index;
                        c = vs[i][j-index];
                    }
                    std::stringstream ss{vs[i].substr(j - (index -1))};
                    ss >> number;
                    sum += number;
                }
                else
                    continue;
            }
            else
                digitFound = false;
        }
        digitFound = false;
    }

    return sum;
}

int main(void)
{
    const std::string fp = "../inputs/3.txt";
    std::ifstream fs{fp};
    if(!fs)
    {
        std::cerr << "No such file exitst!\n";
        return -1;
    }

    int sum = 0;
    std::vector<std::string> vs;
    std::string line;
    while(fs.good())
    {
        std::getline(fs, line);
        vs.push_back(line);
    }

    for(int i = 0; i < vs.size(); ++i)
    {
        for(int j = 0; j < vs[i].length(); ++j)
        {
            if(ispunct(vs[i][j]) && vs[i][j] != '.')
                sum += findPartNumbers(vs, j, i);
        }
    }

    std::cout << sum << std::endl;

    return 0;
}