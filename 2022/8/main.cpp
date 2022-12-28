#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

const std::string input = "in.txt";

std::ifstream& operator>>(std::ifstream& ifs, std::vector<std::vector<int>>& vvi)  {
    int index = 0;
    std::string line;
    while(getline(ifs, line))   {
        char c;
        std::stringstream ss{line};
        vvi.emplace_back();
        while(ss >> c)    {
            vvi[index].push_back((int)(c-48));
        }
        ++index;
    }
    return ifs;
}

void checkTrees(std::vector<std::vector<int>>& vvi, std::vector<std::vector<bool>>& vvb, int rows, int columns, bool forward)   {
    // highest tree in column/row
    std::vector<int> highestInRow(columns, -1);
    std::vector<int> highestInColumn(rows, -1);

    if(forward) {
        for(int row = 0; row < rows - 1; ++row)   {
            for(int column = 0; column < columns - 1; ++column) {
                if(vvi[row][column] > highestInRow[column]) {
                    vvb[row][column] = true;
                    highestInRow[column] = vvi[row][column];
                }
                if(vvi[row][column] > highestInColumn[row]) {
                    vvb[row][column] = true;
                    highestInColumn[row] = vvi[row][column];
                }
            }
        }
        return;
    }

    for(int row = rows - 1; row > 0; --row)   {
        for(int column = columns - 1; column > 0; --column) {
            if(vvi[row][column] > highestInRow[column]) {
                vvb[row][column] = true;
                highestInRow[column] = vvi[row][column];
            }
            if(vvi[row][column] > highestInColumn[row]) {
                vvb[row][column] = true;
                highestInColumn[row] = vvi[row][column];
            }
        }
    }
}

int partOne(const std::vector<std::vector<bool>>& vvb, int rows, int columns)  {
    int visibleTrees = 2 * columns + 2 * (rows - 2);
    
    for(int row = 1; row < rows - 1; ++row) {
        for(int column = 1; column < columns - 1; ++ column)    {
            if(vvb[row][column])
                ++visibleTrees;
        }
    }
    return visibleTrees;
}

int partTwo(const std::vector<std::vector<int>>& vvi, int rows, int columns)   {
    int furtherst = -1;
    
    for(int row = 1; row < rows - 1; ++row) {
        for(int column = 1; column < columns - 1; ++column)  {
            const int current = vvi[row][column];
            int distanceLeft = 1, distanceRight = 1, distanceUp = 1, distanceDown = 1;
            
            // check left
            for(int i = column - 1; i > 0; --i)    {
                if(vvi[row][i] < current) ++distanceLeft;
                else    break;
            }
            
            // check right
            for(int i = column + 1; i < columns - 1; ++i)    {
                if(vvi[row][i] < current) ++distanceRight;
                else    break;
            }
            
            // check up
            for(int i = row - 1; i > 0; --i)    {
                if(vvi[i][column] < current) ++distanceUp;
                else    break;
            }
            
            // check down
            for(int i = row + 1; i < rows - 1; ++i)    {
                if(vvi[i][column] < current) ++distanceDown;
                else    break;
            }
            int totalDistance = distanceLeft * distanceRight * distanceUp * distanceDown;
            if(totalDistance > furtherst) furtherst = totalDistance;
        }
    }
    return furtherst;
}

int main(void)  {
    std::ifstream ifs{input};
    if(!ifs)    {
        std::cerr << "Error reading " << input << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> vvi;
    ifs >> vvi;

    int nrOfRows = vvi.size(), nrOfColumns = vvi[0].size();

    // part I
    // std::vector<std::vector<bool>> vvb(nrOfRows, std::vector<bool>(nrOfColumns, false));

    // checkTrees(vvi, vvb, nrOfRows, nrOfColumns, true);
    // checkTrees(vvi, vvb, nrOfRows, nrOfColumns, false);

    // print(vvb);
    // std::cout << "Nr of visible trees: " << partOne(vvb, nrOfRows, nrOfColumns) << std::endl;

    // part II
    std::cout << partTwo(vvi, nrOfRows, nrOfColumns) << std::endl;
}