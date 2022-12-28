#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
const std::string fname = "in.txt";

int findPriority(const char& c) {
    if(islower(c)) return c - 96;       // a = 1,...,z = 26
    else if(isupper(c)) return c - 38;  // A = 27,..., Z = 52
    return 0;
}

int main()  {
    std::ifstream ifs{fname};
    std::string line;
    int sum = 0;
    std::vector<std::string> vs;
    while(std::getline(ifs, line))  {
        
        // PART I
        // int halfIndex = ceil(line.size() / 2.0);
        // for(int i = 0; i < halfIndex; i++)  {
        //     char c1 = line[i];
        //     bool found = false;
        //     for(int j = halfIndex; j < line.size(); j++)    {
        //         char c2 = line[j];
        //         if(c1 == c2)    {
        //             sum += findPriority(c2);
        //             found = true;
        //             break;
        //         }
        //     }
        //     if(found) break;
        // }

        // PART II
        vs.emplace_back(line);
    }
    for(int i = 0; i < vs.size(); i++)  {
        if(i % 3 == 2)  {                                       // one group of elfs
            std::string s1 = vs[i-2], s2 = vs[i-1], s3 = vs[i];
            for(int j = 0; j < s1.size(); j++)   {
                std::string c(1, s1[j]);                        // "convert" char to string of single character, necessary for find func
                size_t foundInS2 = s2.find(c);
                if(foundInS2 == std::string::npos) continue;    // if not found in 2nd string look for next character
                size_t foundInS3 = s3.find(c);
                if(foundInS3 == std::string::npos) continue;    // if not found in 3rd string look for next character
                sum += findPriority(c[0]);                      // char found in all 3 strings, "convert" string to char, necessary for findPriority func
                break;                                          // common item has been found in this group
            }
        }
    }

    std::cout << sum << std::endl;
    return 0;
}