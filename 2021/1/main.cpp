#include <iostream>
#include <fstream>
#include <string>
#include <vector>
namespace st = std;

void readDataIntoVector(st::vector<int> &vec) {
    // Create a stream object. Connect it to a file on disk. 
    st::ifstream f("./data.txt");

    // Read the file’s contents into our stream object. 
    st::string lineContent;
    if(f.is_open()) {
        while(f) {
            st::getline(f, lineContent);
            int depth = std::stoi(lineContent);
            vec.push_back(depth);
        }
    }

    // Close the file.
    f.close();
}

bool isDeeper(int depth1, int depth2)   {
    return (depth1 > depth2);
}

bool isDeeperGroup(int group1[], int group2[])  {
    int sumGroupOne = group1[0] + group1[1] + group1[2];
    int sumGroupTwo = group2[0] + group2[1] + group2[2];
    return sumGroupOne > sumGroupTwo;
}

int countDeeperMeasurements(st::vector<int> &vec, bool group = false)   {
    auto counter = 0;
    for(auto i = 1; i < vec.size(); i++)    {
        if(group)  {
            if(vec[i+3] != 0)    {
                int group1[] = {vec[i+1], vec[i+2], vec[i+3]};
                int group2[] = {vec[i], vec[i+1], vec[i+2]};
                if(isDeeperGroup(group1, group2)) counter++;
            }   else    {break;}
        }   else    {
            if(isDeeper(vec[i + 1], vec[i])) counter++;
        }    
    }
    return counter;
}

int main()  {
    st::vector<int> data(1);
    readDataIntoVector(data);
    int deeperDepths = countDeeperMeasurements(data, true);
    st::cout << "Number of deeper measurements: " << deeperDepths;

    return 0;
}