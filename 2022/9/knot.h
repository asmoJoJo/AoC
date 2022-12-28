#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Pos  {
    int x;
    int y;

    Pos(): x{0}, y{0} {};
    Pos(int x, int y): x{x}, y{y} {};
};

class Tail;

class Knot {
    public:
        Knot(std::string n): name{n}{};
        Pos getPos() {return pos;};
        void addPos();
        int getNrOfVisited() {return visited.size();};
        virtual void move(char dir, int steps) = 0;
        void setTail(Tail* t) {tail = t;};
        Tail* getTail() {return tail;};
        std::string getName()   {return name;};
    
    protected:
        Tail* tail{NULL};
        Pos pos;
        std::vector<Pos> visited;
        std::string name;
};



class Head: public Knot{
    friend class Tail;
    
    public:
        Head(std::string n): Knot(n) {};
        void move(char dir, int steps);
};

class Tail: public Knot{
    friend class Head;

    protected:
        Head* head{NULL};
        Tail* head_t{NULL};
        void getDifference(int& deltaX, int& deltaY);

    public:
        Tail(std::string n): Knot(n) {};
        void move(char dir, int steps);
        void setHead(Head* h) {head = h;};
        void setHead(Tail* h) {head_t = h;};    // Every tail can have another tail
        Head* getHead() {return head;};
        Tail* getHead_T() {return head_t;};
};

bool operator==(Pos p1, Pos p2);