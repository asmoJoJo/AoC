#include "dir.h"

Directory* execute(TokenStream& ts, const std::string& cmd, Directory* d)    {
    if(cmd == "cd")     {
        d = d->cd(ts);
        std::cout << "Changed into directory '" << d->dName << "'.\n";
    }
    else if(cmd == "ls")    d->ls(ts);
    return d;
}

Directory* readCommand(TokenStream& ts, Directory* d) {
    Token t = ts.get();
    if(t.kind != name)  {
        std::cerr << "Name of a command is expected, but instead received '" << t.kind << "'\n";
    }
    std::string cmdName = t.name;
    return execute(ts, cmdName, d);
}

Directory* statement(TokenStream& ts, Directory* d)  {
    Token t = ts.get();
    if(t.kind == command)
        return readCommand(ts, d);
    else    {                    // No clue what to do with Token
        std::stringstream ss;
        ss << "Cannot parse character(s) '" << t.name << "!'\n";
        ts.putback(t);
        throw std::runtime_error(ss.str());
    }
}

Directory* initFS() {
    auto d = new Directory("root", 0, NULL);
    d->mkdir("/");
    return d;
}

int main(void)  {
    std::ifstream ifs{"in.txt"};
    if(!ifs)
        return 1;
    TokenStream ts{ifs};
    try {
        auto root = initFS();
        auto d = root;
        while(ts.ifs.good())
            d = statement(ts, d);
        std::cout << "smallest= " << partTwo(root) << '\n';
    }
    catch(std::exception& e)    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    catch(...)  {
        std::cerr << "exception \n";
        return 3;
    }
}