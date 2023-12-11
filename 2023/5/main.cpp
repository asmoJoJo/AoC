#include "../../helper/helper.h"

#include <sstream>

struct Map;

class Pair
{
public:
    int64_t s, r;

    Map* m{nullptr};

    Pair(int64_t start, int64_t range) : s{start}, r{range} {}
    Pair(int64_t start, int64_t range, Map* map) : s{start}, r{range}, m{map} {}

};
bool operator==(Pair& a, Pair& b)    { return (a.s == b.s && a.r == b.r); }
bool operator!=(Pair& a, Pair& b)    { return !(a == b); }
bool operator!(const Pair& p)   { return !(p.s || p.r); }
std::ostream& operator<<(std::ostream& os, const Pair& p)   { return os << "[" << p.s << "," << p.r << "]"; }


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
        for(size_t i = 0; i < ranges.size(); i+=3)
        {
            int64_t destination = ranges[i];
            int64_t source = ranges[i + 1];
            int64_t range = ranges[i + 2];

            if(p.s >= source && p.s < source + range)   // start of p is within the range
            {
                Pair prev = p;
                p.s = destination + (p.s - source);
                if(prev.s + p.r <= source + range)         // p falls completely within range
                    break;
                else if(prev.s + p.r > source + range)     // end of p is outside range
                {
                    p.r = range - (prev.s - source);
                    return {prev.s + p.r, prev.r - p.r};
                }
            }
            else if(p.s < source)                       // p starts before the range
            {
                if(p.s + p.r < source)                                  // p ends before range
                    break;

                Pair prev = p;
                p.s = source;
                if(prev.s + p.r >= source && prev.s + p.r < source + range)   // p ends within range
                {
                    p.r = prev.r - (source - prev.s);
                    prev.r -= p.r;
                    return {prev.s, prev.r};
                }
                else if(prev.s + p.r >= source + range)                    // p ends after range
                {
                    // TODO
                    p.r = range;
                    p.s = source;
                    return {prev.s, source - prev.s};
                }
            }
            
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

std::vector<Pair> findLocationForSeedRanges(std::vector<Pair>& seeds, std::vector<Map>& maps)
{
    std::vector<Pair> newSeedRanges;

    for(Map m : maps)
    {
        std::cout << m.name << ":\n";

        for(size_t i = 0; i < seeds.size(); ++i)
        {
            if(seeds[i].m && seeds[i].m->name == m.name)
            // this is the last performed map, so starting next iteration we can start mapping this range again
            {
                seeds[i].m = nullptr;
                continue;
            }
            if(!(seeds[i].m))
            {
                Pair prev = seeds[i], &curr = seeds[i];
                Pair newPair = m.mapRange(curr);            // newPair is always the part that's outside of the range 

                if(!newPair)
                    continue;

                if(prev.r > curr.r)
                {
                    newPair.m = &m;                         // while adding new seed ranges, we have to remember which maps were already performed. We do that by adding a pointer to the last performed map
                    if(newPair.r + curr.r == prev.r)        // the range is cut in half
                    {
                        newSeedRanges.push_back(newPair);
                    }
                    else if(newPair.r + curr.r < prev.r)    // the range is cut in three; newPair is the part before the range, curr the part within range
                                                            // calculate the part that comes after the range
                    {
                        int64_t newRange = prev.r - (newPair.r + curr.r);
                        int64_t newStart = curr.s + curr.r;
                        newSeedRanges.push_back(newPair);
                        newSeedRanges.push_back({newStart, newRange, &m});
                    }
                }
            }
        }
        printVec(seeds, ' ');
        std::cout << "\n\n";
    }

    return newSeedRanges;
}

std::vector<int64_t> mapSeedsToLocationsPart2(std::vector<Pair>& seeds, std::vector<Map>& maps)
{
    std::vector<int64_t> locations;

    std::cout << "Seeds: ";
    printVec(seeds, ' ');
    std::cout << "\n\n";

    // Adding elements to vector while looping over said vector created nasty bug

    std::cout << "ROUND 1:\n";
    std::vector<Pair> splitSeeds = findLocationForSeedRanges(seeds, maps), tmp;

    for(size_t i = 0; i < seeds.size(); ++i)
        locations.push_back(seeds[i].s);  // because all the locations in a range are incremented, we're only interested in the first items of each range

    int round = 2;

    while(splitSeeds.size())
    {
        std::cout << "\nROUND " << round << ":\n";
        tmp = findLocationForSeedRanges(splitSeeds, maps);
        for(size_t i = 0; i < splitSeeds.size(); ++i)
            locations.push_back(splitSeeds[i].s);
        splitSeeds = tmp;
        ++round;
    }

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

    printVec(locations);

    int64_t min = 0x7ffffffffff;   // 0111 1111 1111...

    for(int64_t i : locations)
        min = ((min) < (i) ? (min) : (i));

    std::cout << min << std::endl;
}