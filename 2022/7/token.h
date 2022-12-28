#pragma once

#include <string>

class Token {
    public:
        char kind;
        int value;
        std::string name;

        Token(): kind{0}{};                                     // default
        Token(char ch): kind{ch}{};                             // token that is neither name or value
        Token(char ch, int v): kind{ch}, value{v}{};            //  ,, has value i.e. file size
        Token(char ch, std::string n): kind{ch}, name{n}{};     //  ,, has a name i.e. directory or file name
};