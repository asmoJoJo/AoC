#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(void)  {
    const std::string ifname = "in.txt";
    std::ifstream ifs{ifname};
    if(!ifs)
        return 1;
    
    char c;
    std::string fourChars;
    int nrOfProcessedChars = 0;
    int nrOfDistinctChars = 14; // part 1, set to 4; part 2 set to 14
    bool found = false;
    while(ifs >> c) {
        ++nrOfProcessedChars;
        fourChars.push_back(c);
        if(nrOfProcessedChars >= nrOfDistinctChars) {
            found = false;
            for(int i = 0; i < fourChars.size() - 1; i++)   {
                for(int j = i + 1; j < fourChars.size(); j++)   {
                    if(fourChars[i] == fourChars[j])    {
                        found = true;
                        break;
                    }
                }
                if(found)
                    break;
            }
            if(!found)
                break;
            fourChars.erase(0, 1);
        }
    }
    std::cout << nrOfProcessedChars << std::endl;

    return 0;
}