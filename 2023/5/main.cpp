#include "../../helper/helper.h"

#include <sstream>

struct Pair
{
    int64_t s, r;

    Pair(int64_t start, int64_t range) : s{start}, r{range} {}
};


struct Map
{
    std::string name;
    std::vector<int64_t> ranges;

    Map(const std::string& name) : name{name} {}
    int64_t map(int64_t in)
    {
        for(int64_t i = 0; i < ranges.size(); i+=3)
        {
            int64_t destination = ranges[i];
            int64_t source = ranges[i + 1];
            int64_t range = ranges[i + 2];
        
            if(in >= source && in < source + range)
                return in - source + destination;
        }
        return in;
    }
    Pair mapRange(Pair& p)
    {
        for(int64_t i = 0; i < ranges.size(); i+=3)
        {
            int64_t destination = ranges[i];
            int64_t source = ranges[i + 1];
            int64_t range = ranges[i + 2];
        
            if((p.s >= source) && (p.s < (source + range)))       // Seed range starts within in mapping range and ends either before or after mapping range
            {
                if(p.r > range)
                    p.r = (range - (p.s - source));
                p.s = p.s - source + destination;
                return p;
            }
            // else if((p.s < source) && ((p.s + p.r) < (source + range)))    // Seed range starts before, but ends within mapping range
            // {
            //     int newAmount = p.r - (source - p.s);
            //     p.r = p.r - newAmount;
            //     return {destination, newAmount};
            // }
            // else if((p.s < source) && ((p.s + p.r) >= (source + range)))       // Seed range starts before and ends after mapping range
            // {

            // }
        }
        return {0,0};
    }
    void addRange(int64_t d, int64_t s, int64_t r)
    {
        ranges.push_back(d);
        ranges.push_back(s);
        ranges.push_back(r);
    }
};

std::vector<Pair> parseInput(std::vector<Map>& maps, std::vector<int64_t>& seeds, const std::vector<std::string>& vs)
{
    std::string sub{vs[0].substr(vs[0].find(':') + 1)};   // read first line of input containing seed numbers
    std::stringstream ss{sub};
    int64_t seed;

    while(ss.good())
    {
        ss >> seed;
        seeds.push_back(seed);
    }

    std::vector<Pair> pairs;
    for(int i = 0; i < seeds.size(); i+=2)
        pairs.push_back({seeds[i], seeds[i+1]});

    int64_t d, s, r;

    for(int64_t i = 1; i < vs.size(); ++i)
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

    return pairs;
}

std::vector<int64_t> mapSeedsToLocations(std::vector<int64_t>& seeds, std::vector<Map>& maps)
{
    std::vector<int64_t> locations;

    for(int64_t seed : seeds)
    {
        for(Map map : maps)
        {
            seed = map.map(seed);
        }
        locations.push_back(seed);
    }
    return locations;
}

std::vector<int64_t> mapSeedsToLocationsPart2(std::vector<Pair>& seeds, std::vector<Map>& maps)
{
    std::vector<int64_t> locations;

    for(const Pair& p : seeds)
        std::cout << "[" << p.s << "," << p.r << "] ";
    std::cout << "\n\n";

    for(Map& m : maps)
    {
        size_t size = seeds.size();

        std::cout << m.name << '\n';

        for(size_t i = 0; i < size; ++i)
        {
            int64_t prevStart = seeds[i].s, prevRange = seeds[i].r;

            Pair p = m.mapRange(seeds[i]);
            if(p.r < prevRange)  // if a range had to broken up, we put the remainder at the end of seeds
            {
                if(p.s != prevStart)   // the range is broken up starting at the front
                {
                    int64_t newRange = prevRange - p.r;
                    int64_t newStart = prevStart + p.r;
                    seeds.push_back({newStart, newRange});
                }
                else if(p.s == prevStart)
                {
                    seeds.push_back(p);
                }
            }
                for(const Pair& p : seeds)
        std::cout << "[" << p.s << "," << p.r << "] ";
        }
        std::cout << "\n\n";
    }

    for(size_t i = 0; i < seeds.size(); ++i)
        locations.push_back(seeds[i].s);  // because all the locations in a range are incremented, we're only interested in the first items of each range

    return locations;
}

int main(void)
{
    std::vector<std::string> vs;
    std::ifstream ifs = getIfsStream({"../inputs/5.txt"});
    ifs >> vs;

    std::vector<Map> maps;
    std::vector<int64_t> seeds;

    auto pairs = parseInput(maps, seeds, vs);

    auto locations = mapSeedsToLocationsPart2(pairs, maps);

    int64_t min = 0x7ffffffffff;   // 0111 1111 1111...

    for(int64_t i : locations)
        min = ((min) < (i) ? (min) : (i));

    std::cout << min << std::endl;
}