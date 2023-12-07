#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ifstream getIfsStream(const std::string& filename);
std::ifstream& operator>>(std::ifstream& ifs, std::vector<std::string>& vec);

template <class T>
void printVec(const std::vector<T>& v, char delim = '\n');

#include "helper.cpp"