#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

void removeCharsFromString(std::string &str, const std::string& charsToRemove ) {
   for (char c : charsToRemove) {
      str.erase( remove(str.begin(), str.end(), c), str.end() );
   }
}

bool isGamePossible(const std::string& s)
{
    int i = s.find(':');
    std::stringstream ss{s.substr(i + 1, s.length() - i)};
    int amount;
    std::string color;
    while(ss.good())
    {
        ss >> amount >> color;
        removeCharsFromString(color, ",;");
        if((color == "blue" && amount > 14)  ||
           (color == "green" && amount > 13) ||
           (color == "red" && amount > 12))
        {
            return false;
        }
    }
    return true;
}

int calculatePower(const std::string& s)
{
    int i = s.find(':');
    std::stringstream ss{s.substr(i + 1, s.length() - i)};
    int amount;
    int blue = 0, red = 0, green = 0;
    std::string color;
    while(ss.good())
    {
        ss >> amount >> color;
        removeCharsFromString(color, ",;");
        if(color == "blue")
        {
            if(amount > blue)
                blue = amount;
        }
        else if(color == "green")
        {
            if(amount > green)
                green = amount;
        }
        else if(color == "red")
        {
            if(amount > red)
                red = amount;
        }
    }
    return red * blue * green;
}

int main(void)
{
    const std::string fp = "../inputs/2.txt";
    std::ifstream fs{fp};
    if(!fs)
    {
        std::cerr << "No such file exitst!\n";
        return -1;
    }

    int sum = 0, index = 1;

    std::string line;
    while(fs.good())
    {
        // ======= PART I ========== //
        // std::getline(fs, line);
        // if(isGamePossible(line))
        // {
        //     sum += index;
        //     std::cout << index << '\n';
        // }
        // ++index;

        // ======== PART II ======== //
        std::getline(fs, line);
        sum += calculatePower(line);
    }
    std::cout << sum << std::endl;

    return 0;
}