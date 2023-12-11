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

            Pair prev = p;

            bool startsInRange = (p.s >= source) && (p.s < (source + range));
            bool endsInRange = (p.s + p.r) <= (source + range);
            bool endsAfterRange = (p.s + p.r) > (source + range);

            bool startsBeforeRange = p.s < source;
            bool fallsWithinRange = (p.s + p.r) >= source;

            if(startsInRange && endsInRange)
            {
                std::cout << "Start of p is within the range!\t" << "dest: " << destination << " source: " << source << " range: " << range << "\n";
                
                p.s = destination + (p.s - source);
                return {0,0};
            }
            else if(startsInRange && endsAfterRange)
            {
                std::cout << "Start of p is within the range!\t" << "dest: " << destination << " source: " << source << " range: " << range << "\n";
                p.r = range - (prev.s - source);
                return {prev.s + p.r, prev.r - p.r};
            }
            else if(startsBeforeRange && fallsWithinRange && endsInRange)
            {
                std::cout << "p starts before the range!\n" << "dest: " << destination << "\tsource: " << source << "\trange: " << range << "\n";

                p.s = source;
                p.r = prev.r - (source - prev.s);
                prev.r -= p.r;
                return {prev.s, prev.r};
            }
            else if(startsBeforeRange && fallsWithinRange && endsAfterRange)
            {
                std::cout << "p starts before the range!\n" << "dest: " << destination << "\tsource: " << source << "\trange: " << range << "\n";
                p.r = range;
                p.s = source;
                return {prev.s, source - prev.s};
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

    for(int index = 0; index < maps.size(); ++index)
    {
        Map m = maps[index];
        Map* pNext;
        if(index < maps.size() - 1)
            pNext = &maps[index+1];

        std::cout << m.name << ":\n";

        for(size_t i = 0; i < seeds.size(); ++i)
        {
            Pair &curr = seeds[i];
            if(seeds[i].m && seeds[i].m->name == m.name)
            {
                Pair prev = seeds[i];
                Pair newPair = m.mapRange(curr);            // newPair is always the part that's outside of the range 

                if(!newPair)
                    continue;

                if(prev.r > curr.r)
                {
                    newPair.m = &m;                         // while adding new seed ranges, we have to remember which maps were already performed. That is the map before the current one
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
            curr.m = pNext;
        }
        printVec(seeds, ' ');
        std::cout << "\n\n";
    }

    return newSeedRanges;
}

std::vector<int64_t> mapSeedsToLocationsPart2(std::vector<Pair>& seeds, std::vector<Map>& maps)
{
    for(Pair& seed : seeds)
        seed.m = &maps[0];

    std::vector<int64_t> locations;

    std::cout << "Seeds: ";
    printVec(seeds, ' ');
    std::cout << "\n\n";

    std::cout << "ROUND 1:\n";
    std::vector<Pair> splitSeeds = findLocationForSeedRanges(seeds, maps), tmp;

    for(size_t i = 0; i < seeds.size(); ++i)
        locations.push_back(seeds[i].s);  // because all the locations in a range are incremented, we're only interested in the first items of each range

    int round = 2;

    // Adding elements to vector while looping over said vector created nasty bug
    // Now we add new ranges to new vector and keep repeating this untill all ranges are handleds
    while(splitSeeds.size())
    {
        std::cout << "\nROUND " << round << ":\n";
        tmp = findLocationForSeedRanges(splitSeeds, maps);
        for(size_t i = 0; i < splitSeeds.size(); ++i)
        {
            if(splitSeeds[i].r > 0)
                locations.push_back(splitSeeds[i].s);
        }
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

    std::cout << '\n' << min << std::endl;
}