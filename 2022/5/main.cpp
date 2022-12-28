#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <exception>

std::ifstream& operator>>(std::ifstream& ifs, std::array<std::vector<char>, 9>& stacks)  {
    for(int i = 0; i < 9; i++)   {
        std::string line;
        getline(ifs,line);
        int stackNr = 0;
        bool newEntry = false;
        for(int j = 0; j < line.size(); j++)    {
            char c = line[j];
            if(!(j % 4))    {
                if(isspace(c))  {
                    ++stackNr;
                    continue;
                }
                if(c == '[')
                    newEntry = true;
            }
            if(newEntry)    {
                if(isalpha(c))
                    stacks[stackNr].push_back(c);
                if(c == ']')    {
                    newEntry = false;
                    ++stackNr;
                }
            }
        }
    }
    return ifs;
}

void invertStack(std::vector<char>& stack)   {
    std::vector<char> tempStack = stack;
    for(int i = 0; i < stack.size(); i++)   {
        auto c = stack[i];
        tempStack[tempStack.size() - (1 + i)] = c;
    }
    stack = tempStack;
}

void printStacks(const std::array<std::vector<char>, 9>& stacks)    {
    size_t largest = 0;
    for(auto stack : stacks)  {
        if(stack.size() > largest)
            largest = stack.size();
    }

    for(int row = largest - 1; row >= 0; row--) {
        for(int column = 0; column < stacks.size(); column++)   {
            if(stacks[column].size() <= row)
                std::cout << "     ";
            else
                std::cout << " [" << stacks[column][row] << "] ";
        }
        std::cout << '\n';
    }
    for(int i = 1; i < 10; ++i) {
        std::cout << "  " << i << "  ";
    }
    std::cout << std::endl;
}

void checkCommand(std::string& command, int amount, int& move, int& from, int& to) {
    if(command == "move")      move = amount;
    else if(command == "from") from = amount;
    else if(command == "to")   to = amount;
}

void executeOrder(const std::string& order, std::array<std::vector<char>, 9>& stacks, bool oneByOne) {
    std::string command = "";
    std::string number = "";
    int move = 0, from = 0, to = 0;
    bool digitFound = false;
    
    for(int i = 0; i < order.size(); i++)   {
        char c = order[i];
        if(isalpha(c))  {
            command += c;
            continue;
        }
        if(isdigit(c))  {
            digitFound = true;
            number += c;
        }
        if(isspace(c) || i == order.size() - 1) {
            if(digitFound)  {
                checkCommand(command, std::stoi(number), move, from, to);
                command = "";
                number = "";
                digitFound = false;
            }
            continue;            
        } 
    }
    if(oneByOne)    {
        for(move; move > 0; move--)    {
            char c = stacks[from - 1].back();
            stacks[to - 1].emplace_back(c);
            stacks[from - 1].pop_back();
        }
        return;
    }
    int stackSize = stacks[from - 1].size();
    for(int i = move; i > 0; i--) {
        char c = stacks[from - 1][stackSize - i];
        stacks[to - 1].push_back(c);
    }
    for(int i = 0; i < move; ++i)   {
        stacks[from - 1].pop_back();
    }
}

int main(void)  {
    const std::string ifname = "in.txt";
    std::ifstream ifs{ifname};
    if(!ifs)
        return 1;
    
    std::array<std::vector<char>, 9> stacks;
    ifs >> stacks;
    
    for(auto& stack : stacks)
        invertStack(stack);
    
    std::string order;
    while(getline(ifs, order))  {
    // PART 1
        // executeOrder(order, stacks, true);
    // PART 2
        executeOrder(order, stacks, false);
    }
    printStacks(stacks);

    return 0;
}