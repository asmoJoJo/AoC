#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int parseNumber(const std::vector<std::string>& vs, int x, int y)
{
    int index = 1, number = 0;
    char c = vs[y][x-index];
    while(isdigit(c))
    {
        ++index;
        c = vs[y][x-index];
    }
    std::stringstream ss{vs[y].substr(x - (index - 1))};
    ss >> number;
    return number;
}

int findPartNumbers(const std::vector<std::string>& vs, int x, int y, bool pt2 = false)
{
    bool pt1 = !pt2;
    int sum = 0, number = 0, number2 = 0;
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
                    if(!number)
                        number = parseNumber(vs, j, i);
                    else if(!number2)
                        number2 = parseNumber(vs, j, i);
                    else if(pt2)
                        return 0;

                    if(pt1)
                    {
                        sum += number;
                        number = 0;
                    }
                }
            }
            else
                digitFound = false;
        }
        digitFound = false;
    }

    if(pt1)
        return sum;
    else
        return number * number2;
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
            /* ===== PART I ===== */
            // if(ispunct(vs[i][j]) && vs[i][j] != '.')
            //     sum += findPartNumbers(vs, j, i);

            /* ===== PART II ===== */
            if(vs[i][j] == '*')
                sum += findPartNumbers(vs, j, i, true);
        }
    }

    std::cout << sum << std::endl;

    return 0;
}