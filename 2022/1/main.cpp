#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::ifstream& operator>>(std::ifstream& ifs, std::vector<int>& vi)    {
    int totalCal = 0;
    std::string line;
    while(std::getline(ifs, line))   {
        if(!line.size())   {
            vi.push_back(totalCal);
            totalCal = 0;
            continue;
        }
        totalCal += std::stoi(line);
    }
    return ifs;
}

int findSumTopThree(std::vector<int> vi)    {
    int totalCal = 0;
    for(int i = 0; i < 3; i++) {
        auto it = std::max_element(vi.begin(), vi.end());
        if(it != vi.end())  {
            totalCal += *it;
            vi.erase(it);
        }
        else
            return -1;
    }

    return totalCal;
}

int main()  {

    // Open input file
    std::cout << "Please enter name of input file: ";
    std::string fname;
    std::cin >> fname;
    std::ifstream ifs{fname};
    if(!ifs)    {
        std::cerr << "'" << fname << "' was not found!\n";
        return 1;
    }
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    // Read input and put into vector
    std::vector<int> vi;
    ifs >> vi;

    // Part I of day 1
    // Look for total Calories of Elf with most Calories
    // auto it = std::max_element(vi.begin(), vi.end());
    // if(it != vi.end())  {
    //     std::cout << "Total Calories: " << *it << std::endl;
    // }

    // Part II of day 1
    int total = findSumTopThree(vi);
    if(total == -1) {
        std::cerr << "An error has occurred.." << std::endl;
        return 1;
    }

    std::cout << total << std::endl;
    
    return 0;
}