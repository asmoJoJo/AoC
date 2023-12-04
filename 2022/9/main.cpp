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

void print(const Head& head, const std::vector<Tail>& tails, int w, int h, bool visited = false)    {
    for(int y = h - 16; y >= -5; --y) {
        for(int x = -11; x < w - 11; ++x)  {
            bool found = false;
            if(visited) {
                for(int i = 0; i < tails[tails.size()-1].getNrOfVisited(); ++i) {
                    if(Pos(x,y) == tails[tails.size()-1].getVisited(i)) {
                        std::cout << "# ";
                        found = true;
                        break;
                    }
                }
                if(found)   continue;
                std::cout << ". ";
                continue;                
            }
            if(Pos(x, y) == head.getPos())  {
                std::cout << head.getName() << ' ';
                continue;
            }
            
            for(const Tail& t: tails)   {
                if(Pos(x,y) == t.getPos())  {
                    std::cout << t.getName() << ' ';
                    found = true;
                    break;
                }
            }
            if(found)   continue;
            if(Pos(x,y) == Pos())   {
                std::cout << "S ";
                continue;
            }
            std::cout << ". ";
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}

int main(void)  {
    const std::string input{"../inputs/test/9.txt"};
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

    auto head = Head("H");
    int nrOfTails = 9;  // set to 1 for part 1
    std::vector<Tail> tails;
    for(int i = 0; i < nrOfTails; ++i)  {
        tails.push_back(Tail(std::to_string(i+1)));
    }

    head.setTail(&tails[0]);
    tails[0].setHead(&head);

    for(int i = 0; i < nrOfTails; ++i)  {
        if(i < nrOfTails - 1)
            tails[i].setTail(&tails[i+1]);
        if(i > 0)
            tails[i].setHead(&tails[i-1]);
    }

    int w = 33, h = 33;

    // std::cout << "== Initial State ==\n\n";
    // print(head, tails, w, h);
    for(int i = 0; i < directions.size(); ++i)  {
        std::cout << "== " << directions[i] << ' ' << steps[i] << " ==\n\n";
        head.move(directions[i], steps[i]);
        // print(head, tails, w, h);
    }
    print(head,tails, w, h, true);

    std::cout << tails[nrOfTails-1].getNrOfVisited() << std::endl; // add 1 because pos(0,0) is not counted // set to 0 for part 1
    return 0;
}