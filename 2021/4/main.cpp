#include <iostream>
#include <fstream>
#include <vector>
#include <string>
namespace st = std;

const auto nrOfRows = 5;
const auto nrOfColumns = nrOfRows;

void parseInt(const st::string &line, st::vector<int> &numbers, const char delim = ' ')    {
    auto found = 0;
    for(auto i = 0; i <= line.size(); i++)   {
        if(line[i] == delim || i == line.size())  {
            auto s = line.substr(found, i - found);
            if(!s.empty())  {
                auto number = st::stoi(s);
                numbers.push_back(number);
            }
            found = i + 1;
        }
    }
}

void readFile(st::string filePath, st::vector<int> &intVec, const char delim = ' ') {
    st::ifstream f(filePath);
    st::string line;
    if(f.is_open())    {
        while(f.good())  {
            st::getline(f, line);
            parseInt(line, intVec, ',');
        }
    }
}

void readFile(st::string filePath, st::vector<st::vector<int>> &vecOfIntVecs, const char delim = ' ') {
    st::ifstream f(filePath);
    st::string line;
    auto index = 0;
    vecOfIntVecs.emplace_back();
    if(f.is_open())    {
        while(f.good())  {
            st::getline(f, line);
            if(line.empty())    {
                vecOfIntVecs.emplace_back();
                index++;
            }
            parseInt(line, vecOfIntVecs[index]);
        }
    }
}

int main()  {
    st::vector<int> numbers;
    readFile("./numbers.txt", numbers);

    st::vector<st::vector<int>> boards;
    readFile("./data.txt", boards);

    st::vector<st::vector<bool>> bingo;
    for(auto i = 0; i < boards.size(); i++) {
        bingo.emplace_back();
        for(auto j = 0; j < boards[0].size(); j++)  {
            bingo[i].push_back(false);
        }
    }

    for(auto &numberCalled: numbers)    {
        for(auto boardNr = 0; boardNr < boards.size(); boardNr++) {
            for(auto column = 0; column < nrOfColumns; column++)   {
                for(auto row = 0; row < nrOfRows; row++)    {
                    if(numberCalled == boards[boardNr][row + column * nrOfRows])    {
                        bingo[boardNr][row + column * nrOfRows] = true;
                    }
                }
            }
        }
    }
}