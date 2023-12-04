#include "dir.h"

Directory* Directory::cd(TokenStream& ts)   {
    Token t = ts.get();
    if(t.name == "..") {
        auto d = this->parentDir;
        return d;
    }
    for(auto d : subDirectories)  {
        if(d->dName == t.name)
            return d;
    }
    std::stringstream ss;
    ss << "Cannot change into directory '" << t.name << "'\n";
    throw std::runtime_error(ss.str());
}

void Directory::ls(TokenStream& ts)   {
    Token t = ts.get();
    while(t.kind == dir || t.kind == number)   {
        if(t.kind == dir)   {
            t = ts.get();
            if(t.kind != name)  {
                std::cerr << "Name of directory is expected, but instead received '" << t.kind << "'\n";
                return;
            }
            this->mkdir(t.name);
        }
        else if(t.kind == number)   {
            int fSize = t.value;
            t = ts.get();
            if(t.kind != name)  {
                std::cerr << "Name of file is expected, but instead received '" << t.kind << "'\n";
                return;
            }
            this->touch(fSize, t.name);
        }
        else    {
                ts.putback(t);
                return;
        }
        t = ts.get();
    }
    ts.putback(t);
}

void Directory::touch(const int size, const std::string& fName)  {
    std::cout << "Creating file '" << fName << "'.\n";
    for(auto f : files) {
        if(f.fName == fName)    {
            std::cerr << "File already exists!\n";
            return;
        }
    }
    this->files.push_back(File{size, fName});
    std::cout << "File '" << fName << "' succesfully created.\n";
}

void Directory::mkdir(const std::string dName) {
    std::cout << "Creating directory '" << dName << "'.\n";
    for(auto d : subDirectories)    {
        if(d->dName == dName) {
            std::cerr << "Directory already exists!\n";
            return;
        }
    }
    auto d = new Directory(dName, 0, this);
    this->subDirectories.push_back(d);
    std::cout << "Directory '" << dName << "' succesfully created.\n";
}

void Directory::deleteDir() {
    for(Directory* d : subDirectories)  {
        delete d;
    }
}

int computeSize(Directory* dir)    {
    // This function must only be called once,
    // after all files and directories are created.
    for(auto f: dir->files)
        dir->size += f.size;
    for(auto d: dir->subDirectories)    {
        dir->size += computeSize(d);
    }
    return dir->size;
}

int partOne(Directory* dir) {
    int total = 0;
    if(dir->size <= 100000)
        total += dir->size;
    for(auto d: dir->subDirectories)    {
        total += partOne(d);
    }
    return total;
}

void findvalidDirs(Directory* dir, const int& amount, std::vector<int>& valids)  {
    for(auto d: dir->subDirectories)    {
        findvalidDirs(d, amount, valids);
        if(d->size >= amount)   valids.push_back(d->size);
    }
}

int partTwo(Directory* dir) {
    const int available = 70000000;
    const int unusedNeeded = 30000000;
    
    int totalUsed = computeSize(dir);

    int amountToFreeUp = abs(unusedNeeded - (available - totalUsed));

    std::vector<int> valids;
    findvalidDirs(dir, amountToFreeUp, valids);
    
    std::sort(valids.begin(), valids.end());
    return *valids.begin();
}