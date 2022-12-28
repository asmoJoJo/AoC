#include <iostream>
#include <fstream>
#include <vector>

std::ifstream& operator>>(std::ifstream& ifs, std::vector<std::vector<char>>& vcv)    {
    int index = 0;
    char c1, c2;
    while(ifs.good())  {
        ifs >> c1 >> c2;
        vcv.emplace_back();
        vcv[index].push_back(c1);
        vcv[index].push_back(c2);
        ++index;
    }
    vcv.pop_back(); // because of bug where last entry is read twice
    return ifs;
}

int playRound(const char& opp, const char& player)  {
// Opp: A = rock, B = paper, C = scissors
// Player: X = rock, Y = paper, Z = scissors
// Outcome: loss = 0, draw = 3, win = 6
    int shapeScore = 0;
    bool win = false;
    bool draw = false;

    if(player == 'X')   {
        shapeScore = 1;
        if(opp == 'C') win = true;
        else if(opp == 'A') draw = true;
    }        
    else if(player == 'Y')  {
        shapeScore = 2;
        if(opp == 'A') win = true;
        else if(opp == 'B') draw = true;
    }
    else if(player == 'Z')  {
        shapeScore = 3;
        if(opp == 'B') win = true;
        else if(opp == 'C') draw = true;
    }

    if(draw)
        return shapeScore + 3;
    
    if(win)
        return shapeScore + 6;
    
    return shapeScore;              // loss
}

int calculateTotalScore(const std::vector<std::vector<char>>& vcv)   {
    int total = 0;
    for(auto cv : vcv)  {
        char player = cv[1], opp = cv[0];
        int round = playRound(opp, player);
        total += round;
    }
    return total;
}

char chooseShape(const char& opp, const char& result)    {
// Opp: A = rock, B = paper, C = scissors
// Player: X = rock, Y = paper, Z = scissors
// Result: X = loss, Y = draw, Z = win
    if(result == 'X')   {
        if(opp == 'A') return 'Z';
        if(opp == 'B') return 'X';
        return 'Y';
    }
    if(result == 'Y')   {
        if(opp == 'A') return 'X';
        if(opp == 'B') return 'Y';
        return 'Z';
    }
    if(result == 'Z')   {
        if(opp == 'A') return 'Y';
        if(opp == 'B') return 'Z';
        return 'X';
    }
    return 0;
}

std::vector<std::vector<char>> translate(const std::vector<std::vector<char>>& vcv) {
    std::vector<std::vector<char>> vcv_new;
    for(int i = 0; i < vcv.size(); i++)  {
        auto opp = vcv[i][0], result = vcv[i][1];
        char player = chooseShape(opp, result);
        if(!player)
            std::cerr << "Something went wrong during translation..\n";
        vcv_new.emplace_back();
        vcv_new[i].push_back(opp);
        vcv_new[i].push_back(player);
    }
    return vcv_new;
}

int main(void)  {
    std::cout << "Please input filename: ";
    std::string fname;
    std::cin >> fname;
    std::ifstream ifs{fname};
    if(!ifs)
        std::cerr << "Cannot open file '" << fname << "'!" << std::endl;
    ifs.exceptions(ifs.exceptions()|std::ios_base::badbit);

    std::vector<std::vector<char>> vcv;
    ifs >> vcv;

    // part 1
    int score = calculateTotalScore(vcv);
    std::cout << "\nScore: " << score << std::endl;

    // part 2
    std::vector<std::vector<char>> vcv_new = translate(vcv);
    score = calculateTotalScore(vcv_new);
    std::cout << "\nScore: " << score << std::endl;

    return 0;
}