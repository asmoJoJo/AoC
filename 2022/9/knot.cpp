#include "knot.h"

void Knot::addPos() {
    for(Pos p: visited)
        if(pos == p)    return;
    visited.push_back(pos);
}

void Head::move(char dir, int steps) {
    if(!tail)   std::cerr << "No Tail is set!!\n";

    for(int step = 0; step < steps; ++step)  {
        switch(dir) {
            case 'U':
                pos.y++;
                break;
            case 'D':
                pos.y--;
                break;
            case 'L':
                pos.x--;
                break;
            case 'R':
                pos.x++;
                break;
            default:
                break;
        }
        tail->move(dir, steps);
    }
}

void Tail::getDifference(int& deltaX, int& deltaY)  {
    Pos target = Pos();

    if(head)    {
        target.x = head->pos.x;
        target.y = head->pos.y;
    }
    else if(head_t) {
        target.x = head_t->pos.x;
        target.y = head_t->pos.y;
    }
    deltaX = target.x - pos.x;
    deltaY = target.y - pos.y;
}

void Tail::move(char dir, int steps)    {
    if(!head && !head_t)   {
        std::cerr << "No Head is set!!\n";
        return;
    }
    
    int diffX, diffY;
    getDifference(diffX, diffY);

    // Head and Tail are still touching
    if(diffX <= 1 && diffX >= -1 && diffY <= 1 && diffY >= -1)    return;     
    
    // Movement either horizontally or vertically
    else if(!diffX && diffY > 1)  pos.y++;
    else if(!diffX && diffY < -1) pos.y--;
    else if(diffX > 1 && !diffY)  pos.x++;
    else if(diffX < -1 && !diffY) pos.x--;

    // Horizontal and Vertical movement
    else if((diffX == 1 && diffY > 1) || (diffX > 1 && diffY == 1))    {
        pos.x++;
        pos.y++;
    }
    else if((diffX == 1 && diffY < -1) || (diffX > 1 && diffY == -1))    {
        pos.x++;
        pos.y--;
    }
    else if((diffX == -1 && diffY > 1) || (diffX < -1 && diffY == 1))    {
        pos.x--;
        pos.y++;
    }
    else if(diffX == -1 && diffY < -1 || (diffX < -1 && diffY == -1))    {
        pos.x--;
        pos.y--;
    }
    addPos();
    if(tail)    {
        tail->move(dir, steps);
    }
}

bool operator==(Pos p1, Pos p2) {
    if(p1.x == p2.x && p1.y == p2.y) return true;
    return false;
}