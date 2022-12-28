#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
namespace st = std;

#define FILE_PATH "./data.txt"

void readData(st::list<st::string> &data) {
    st::ifstream f (FILE_PATH);
    st::string lineContent;
    if(f.is_open()) {
        while(f.good())    {
            st::getline(f, lineContent);
            data.push_back(lineContent);
        }
    }
    else {
        st::cout << "Couldn't open file\n";
    }
    f.close();
}

char findCommonBit(st::list<st::string> &data, int index, bool mostCommon = false)  {
    auto zeroCounter = 0, oneCounter = 0;
    auto it = data.begin();
    for(it; it != data.end(); ++it)    {
        auto bit = (*it)[index];
        if(bit == '0') zeroCounter++;
        else    oneCounter++;
    }
    if((mostCommon && oneCounter >= zeroCounter) || (!mostCommon && oneCounter < zeroCounter))  {
        return '1';
    }
    return '0';
}

int binaryToInteger(const st::string &binary) {
    auto sum = 0;
    auto exp = binary.size() - 1;
    for(auto i = 0; i < binary.size(); i++) {
        auto bit = (int)binary[i] - 48;                 // 48 = OFFSET for converting char to corresponding int
        sum += bit * pow(2, exp);
        --exp;
    }
    return sum;
}

st::string findMostSimilarNumber(st::list<st::string> data, bool mostCommon = false) {
    for(auto i = 0; i < 12; i++)    {
        char commonBit = findCommonBit(data, i, mostCommon);
        for(auto it = data.begin(); it != data.end(); ++it)  {
            auto bit = (*it)[i];         
            if(bit != commonBit)    {
                if(data.size() == 1)    break;
                it = data.erase(it);
                --it;
            }
            
        }
    }
    return *data.begin();
}

int main()  {
    st::list<st::string> data;
    readData(data);

    st::string gammaRate = "000000000000", epsilonRate = "000000000000";
    for(auto i = 0; i < 12; i++)    {
        gammaRate[i] = findCommonBit(data, i, true);
        epsilonRate[i] = findCommonBit(data, i);
    }

    // int powerOutput = binaryToInteger(gammaRate) * binaryToInteger(epsilonRate);         //  uncomment to find out
    // st::cout << "powerOutput= " << powerOutput << st::endl;                              //  answer to part 1

    auto oxyGenRating = findMostSimilarNumber(data, true);
    auto co2ScrubRating = findMostSimilarNumber(data);

    st::cout << "OxygenRating binary: " << oxyGenRating << "\tDecimal: " << binaryToInteger(oxyGenRating) << st::endl;
    st::cout << "CO2 Rating binary: " << co2ScrubRating << "\tDecimal: " << binaryToInteger(co2ScrubRating) << st::endl;
    st::cout << "LifeSupport Rating: " << binaryToInteger(oxyGenRating) * binaryToInteger(co2ScrubRating);

    return 0;
}