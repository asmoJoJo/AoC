#include "../../helper/helper.h"

#include <sstream>

struct Map
{
    std::string name;
    std::vector<int> ranges;

    Map(const std::string& name) : name{name} {}
    int map(int in)
    {
        for(int i = 0; i < ranges.size(); i+=3)
        {
            int destination = ranges[i];
            int source = ranges[i + 1];
            int range = ranges[i + 2];
        
            if(in >= source & in < source + range)
                return in - source + destination;
        }
        return in;
    }
    void addRange(int d, int s, int r)
    {
        ranges.push_back(d);
        ranges.push_back(s);
        ranges.push_back(r);
    }
};

void parseInput(std::vector<Map>& maps, std::vector<int>& seeds, const std::vector<std::string>& vs)
{
    std::string sub{vs[0].substr(vs[0].find(':') + 1)};   // read first line of input containing seed numbers
    std::stringstream ss{sub};
    int seed;

    while(ss.good())
    {
        ss >> seed;
        seeds.push_back(seed);
    }

    int d, s, r;

    for(int i = 1; i < vs.size(); ++i)
    {
        if(isalpha(vs[i][0]))
        {
            sub = vs[i].substr(0, vs[i].find(':') - 4);
            maps.push_back({sub});
        }
        else if(isdigit(vs[i][0]))
        {
            std::stringstream sss{vs[i]};
            sss >> d >> s >> r;
            maps[maps.size() - 1].addRange(d, s, r);
        }
    }
}

std::vector<int> mapSeedsToLocations(std::vector<int>& seeds, std::vector<Map>& maps)
{
    std::vector<int> locations;

    for(int seed : seeds)
    {
        for(Map map : maps)
        {
            seed = map.map(seed);
        }
        locations.push_back(seed);
    }
    return locations;
}

std::vector<int> mapSeedsToLocationsPart2(std::vector<int>& seeds, std::vector<Map>& maps)
{
    std::vector<int> locations;

    for(int i = 0; i < seeds.size(); i+=2)
    {
        int start = seeds[i];
        int range = seeds[i+1];
        for(int j = 0; j < range; ++j)
        {
            int seed = start + j;
            for(Map map : maps)
            {
                seed = map.map(seed);
            }
            locations.push_back(seed);
        }
        std::cerr << i << "...";
    }
    return locations;
}

int main(void)
{
    std::vector<std::string> vs;
    std::ifstream ifs = getIfsStream({"../inputs/5.txt"});
    ifs >> vs;

    std::vector<Map> maps;
    std::vector<int> seeds;

    parseInput(maps, seeds, vs);

    auto locations = mapSeedsToLocationsPart2(seeds, maps);

    int min;
    min |= 0x7fffffff; // 0111 1111 11...

    for(int i : locations)
    {
        min = ((min) < (i) ? (min) : (i));
    }

    std::cout << min << std::endl;
}