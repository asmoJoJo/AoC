#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

struct Pair
{
    int nrOfWins;
    int nrOfInstances = 1;

    Pair(int wins) : nrOfWins{wins} {}
    void AddInstances(int amount) { nrOfInstances += amount; }
private:
    Pair() = default;
};

void parseString(const std::string& s, std::vector<int>& winningNrs, std::vector<int>& ownedNrs)
// Format:
// <string> <int> <char>    <int> <int>...<int>  <char>  <int>...<int>
//     useless info            winning numbers    delim   numbers you have
{
    std::string card;
    int cardNr, number;
    char semiColon, ch = 0;
    std::stringstream ss{s};

    ss >> card >> cardNr >> semiColon >> ch;
    while(isdigit(ch))
    {
        ss.unget();
        ss >> number;
        winningNrs.push_back(number);
        ss >> ch; 
    }   // delim will be taken out of ss already in last iteration

    while(ss.good())
    {
        ss >> number;
        ownedNrs.push_back(number);
    }
}

int calculatePointsPerCard(const std::string& s)
{
    int score = 0, cardNr = 0;
    std::vector<int> winningNumbers, ownedNumbers;
    parseString(s, winningNumbers, ownedNumbers);

    for(int w : winningNumbers)
        for(int o : ownedNumbers)
            if(w == o)
                ++score;
    return score;
}

int countScratchCards(std::vector<Pair>& pairs)
{
    int amount = 0;
    for(int i = 0; i < pairs.size(); ++i)
    {
        amount += pairs[i].nrOfInstances;
        for(int j = i + 1; j < i + pairs[i].nrOfWins + 1; ++j)
            pairs[j].AddInstances(pairs[i].nrOfInstances);
    }
    return amount;
}

int main(void)
{
    const std::string fp = "../inputs/4.txt";
    std::ifstream fs{fp};
    if(!fs)
    {
        std::cerr << "No such file exitst!\n";
        return -1;
    }

    std::string line;
    std::vector<Pair> pairs;
    int sum = 0;

    while(fs.good())
    {
        std::getline(fs, line);
        int score = calculatePointsPerCard(line);

        // ===== PARTE UNO ===== //
        // if(score)
        //     sum += pow(2, score - 1);

        // ===== PART II ===== //
        pairs.push_back({score});
    }

    // Only for part 2
    sum = countScratchCards(pairs);

    for(int i = 0; i < pairs.size(); ++i)
        std::cout << "Card " << i+1 << " has " << pairs[i].nrOfWins << " wins and " << pairs[i].nrOfInstances << " instances\n"; 

    std::cout << sum << std::endl;
}