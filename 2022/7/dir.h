#pragma once

#include <vector>
#include <sstream>
#include <algorithm>

#include "tokenstream.h"

struct File {
    std::string fName;
    int size{0};

    File(int size, std::string fName): size{size}, fName{fName}{};
};

struct Directory {
    std::string dName;
    int size{0};
    
    Directory* parentDir = NULL;
    std::vector<Directory *> subDirectories;
    std::vector<File> files;

    Directory(std::string n, int d, Directory* p):    dName{n}, size{d}, parentDir{p}{}

    Directory* cd(TokenStream& ts);
    void ls(TokenStream& ts);
    void touch(const int size, const std::string& fName);
    void mkdir(const std::string dName);
    void deleteDir();

    ~Directory(){deleteDir();};
};

int computeSize(Directory* dir);
int partOne(Directory* dir);
void findvalidDirs(Directory* dir, const int& amount, std::vector<int>& valids);
int partTwo(Directory* dir);