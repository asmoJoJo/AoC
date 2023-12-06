std::ifstream& operator>>(std::ifstream& ifs, std::vector<std::string>& vec)
{
    std::string line;
    while(ifs.good())
    {
        std::getline(ifs, line);
        vec.push_back(line);
    }
    return ifs;
}

std::ifstream getIfsStream(const std::string& filename)
{
    std::ifstream ifs{filename};
    if(!ifs)
    {
        std::cerr << "No such file exitst!\n";
        ifs.clear(std::ios_base::failbit);
    }
    return ifs;
}

template <class T>
void printVec(const std::vector<T>& v)
{
    for(const T& t : v)
        std::cout << t << '\n';
    std::cout << std::endl; 
}