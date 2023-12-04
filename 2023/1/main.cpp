#include <iostream>
#include <fstream>
#include <string>

const std::string numbers = "0123456789";

int parseIntFromString(const std::string& s)
{
    if(s.substr(0, 3) == "one")
        return 1;
    if(s.substr(0, 3) == "two")
        return 2;
    if(s.substr(0, 5) == "three")
        return 3;
    if(s.substr(0, 4) == "four")
        return 4;
    if(s.substr(0, 4) == "five")
        return 5;
    if(s.substr(0, 3) == "six")
        return 6;
    if(s.substr(0, 5) == "seven")
        return 7;
    if(s.substr(0, 5) == "eight")
        return 8;
    if(s.substr(0, 4) == "nine")
        return 9;
    return 0;
}

int parseInt(const std::string& s)
{
    char fst = 0, snd = 0;
    for(int i = 0; i < s.length(); ++i)
    {
        // in case c is a digit
        if(s[i] >= '0' && s[i] <= '9')
        {
            for(char n : numbers)
            {
                if(s[i] == n)
                    snd = s[i];
            }
        }

        // in case c is character
        else
        {
            int tmp = parseIntFromString(s.substr(i, s.length() - i));
            if(tmp)
                snd = tmp + '0';
        }
        
        if(!fst)
            fst = snd;
    }

    if(!fst)
        return 0;
    if(!snd)
        snd = fst;

    char n[3] = {fst, snd, '\0'};
    std::cout << n << '\n';
    return std::stoi(n);
}


int main(void)
{
    const std::string fp = "../inputs/1.txt";
    std::ifstream fs{fp};
    if(!fs)
    {
        std::cerr << "No such file exitst!\n";
        return -1;
    }

    int sum = 0;

    std::string line;
    while(fs.good())
    {
        std::getline(fs, line);
        sum += parseInt(line);
    }

    std::cout << sum << std::endl;

    return 0;
}