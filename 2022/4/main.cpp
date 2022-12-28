#include <iostream>
#include <fstream>
#include <string>

bool hasOverlap(int& start1, int& end1, int& start2, int& end2, bool fully = true) {
    bool completeOverlap = (start1 <= start2 && end1 >= end2) || (start1 >= start2 && end1 <= end2);
    if(fully) return completeOverlap;
    bool partialOverlap =  (start1 >= start2 && start1 <= end2) || (end1 >= start2 && end1 <= end2)
        || (start2 >= start1 && start2 <= end1) || (end2 >= start1 && end2 <= end1);
    return completeOverlap || partialOverlap;
}

int main(void)  {
    const std::string fname = "in.txt";
    std::ifstream ifs{fname};
    if(!ifs)
        return 1;
    int nrOfFullyContained{0}, nrOfOverlaps{0};
    int index = 0;
    while(ifs.good()) {
        index++;
        int start1, end1, start2, end2;
        char c1, c2, c3;
        ifs >> start1 >> c1 >> end1 >> c2 >> start2 >> c3 >> end2;
        // PART 1
        // if(hasOverlap(start1, end1, start2, end2))
        //     ++nrOfFullyContained;
        // PART 2
        if(hasOverlap(start1, end1, start2, end2, false))  {
            ++nrOfOverlaps;
        }
    }
    std::cout << nrOfOverlaps << std::endl;    
}