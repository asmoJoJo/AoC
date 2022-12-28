#include <iostream>
#include <fstream>
#include <string>
#include <vector>
namespace st = std;

#define FILEPATH "./data.txt"
#define FILE_SIZE 1000

void readData(st::vector<st::string> &data) {
    st::ifstream f (FILEPATH);
    st::string lineContent;
    int index = 0;

    if(f.is_open()) {
        while(f)    {
            st::getline(f, lineContent);
            if(index < FILE_SIZE)  {
                data[index] = lineContent;
                index++;
            }
        }
    }
    f.close();
}

void moveSubMarine(st::string movement, int const &nrOfSteps, int &horizontalPos, int &depth, int &aim)  {
    if(movement.compare("up") == 0) {
        aim -= nrOfSteps;
        st::cout << movement << st::endl;
    }
    else if(movement.compare("down") == 0) {
        aim += nrOfSteps;
        st::cout << movement << st::endl;
    }
    else if(movement.compare("forward") == 0) {
        horizontalPos += nrOfSteps;
        depth += nrOfSteps * aim;
        st::cout << movement << st::endl;
    }
}

void processData(st::vector<st::string> &source, int &horizontalPos, int &depth)   {
    st::string movement, delimiter = " ";
    int nrOfSteps, aim = 0;
    for(auto i = 0; i < FILE_SIZE; i++) {
        movement = source[i].substr(0, source[i].find(delimiter));
        nrOfSteps = st::stoi(source[i].substr(source[i].find(delimiter) + 1));
        moveSubMarine(movement, nrOfSteps, horizontalPos, depth, aim);
    }
}

void printData(const st::vector<st::string> &data)  {
    int nrOfLines = 0;
    for(auto &line: data)   {
        st::cout << line << st::endl;
        nrOfLines++;
    }
    st::cout << nrOfLines << st::endl;
}

int main()  {
    auto horizontalPos = 0, depth = 0, aim = 0;
    st::vector<st::string> data(FILE_SIZE);
    readData(data);

    processData(data, horizontalPos, depth);

    st::cout << "horizontal: " << horizontalPos << "\tdepth: " << depth << "\tproduct: " << horizontalPos * depth; 
    return 0;
}