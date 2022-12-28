#pragma once

#include <iostream>
#include <exception>
#include <fstream>

#include "token.h"

const char command = '$';
const char number = '8';
const char name = 'N';
const char dir = 'D';

const std::string  dir_str = "dir";

class TokenStream   {
    public:
        std::ifstream& ifs;
        
        TokenStream(std::ifstream& ifs): ifs{ifs}{};
        Token get();
        void putback(Token t);

    private:
        bool full{false};
        Token buffer {0};
};