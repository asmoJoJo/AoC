#include "tokenstream.h"

Token TokenStream::get()    {
    if(full)    {
        full = false;
        return buffer;
    }

    char ch;
    ifs >> ch;
    switch (ch) {
        case command:
            return Token{ch};
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            ifs.putback(ch);
            int val;
            ifs >> val;
            return Token(number, val);
        default:
            std::string s;
            s += ch;
            while(ifs.get(ch) && isalpha(ch) || isdigit(ch) || ch == '.') s += ch;
            if(s == dir_str)    return Token{dir};
            return Token{name, s};
    }
}

void TokenStream::putback(Token t)  {
    if(full) throw std::runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}