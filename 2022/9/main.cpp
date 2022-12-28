#include <fstream>

#include "knot.h"

int readFile(std::ifstream& ifs, std::vector<char>& dirs, std::vector<int>& steps) {
    while(ifs.good())   {
        char c;
        int i;
        ifs >> c >> i;
        // if(ifs.badbit)    return 1;
        
        dirs.push_back(c);
        steps.push_back(i);
    }

    return 0;
}

int main(void)  {
    const std::string input{"../inputs/9.txt"};
    std::ifstream ifs{input};
    if(!ifs)    return 1;
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    // Create two vectors, one for direction and one for amount of steps
    std::vector<char> directions;
    std::vector<int>  steps;

    if(readFile(ifs, directions, steps))    {
        std::cerr << "Someting went wrong while reading file " << input << '\n';
        return 2;
    }

    auto head = Head("h1");
    int nrOfTails = 9;  // set to 1 for part 1
    std::vector<Tail> tails;
    for(int i = 0; i < nrOfTails; ++i)  {
        tails.push_back(Tail("t" + std::to_string(i)));
    }

    head.setTail(&tails[0]);
    tails[0].setHead(&head);

    for(int i = 0; i < nrOfTails; ++i)  {
        if(i < nrOfTails - 1)
            tails[i].setTail(&tails[i+1]);
        if(i > 0)
            tails[i].setHead(&tails[i-1]);
    }

    for(int i = 0; i < directions.size(); ++i)  {
        head.move(directions[i], steps[i]);
    }
    std::cout << tails[nrOfTails-1].getNrOfVisited() << std::endl; // add 1 because pos(0,0) is not counted // set to 0 for part 1
    return 0;
}