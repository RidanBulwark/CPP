#include "graphics.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <time.h>

using namespace std;
using namespace genv;

const int szelesseg = 600, magassag = 400;

struct block
{
    block():szel(rand()% 30 + 20),
        mag(rand()% 30 + 20)
    {
        x = (rand()%(szelesseg - szel));
        y = (rand()%(magassag - mag));
    }

    void draw()
    {
        int keret = 2;
        if(kijelolt)
        {
            keret = 4;
        }
        gout << color(200, 0, 0) << move_to(x, y) << box(szel, mag)
             << color(255, 255, 40) << move_to(x, y) << box(szel, keret)
             << box(-keret, mag-keret+1) << box(-szel+keret-1, -keret) 
             << box(keret, -mag+keret) << refresh;
    }

    void mozgat(int x, int y)
    {
        this->x = x;
        this->y = y;
        draw();
    }

    void elkap(int ex, int ey){
        dx = ex-x;
        dy = ey-y;
    }

    void kijelol()   //Setter
    {
        kijelolt = true;
    }
    bool kijelolte()
    {
        return kijelolt;
    }
    void elenged()   //Getter
    {
        kijelolt = false;
    }

    bool folotte(int ex, int ey)
    {
        return (x < ex and ex < x + szel and
                y < ey and ey < y + mag);
    }

private:
    int x, y, szel, mag, dx, dy;
    bool kijelolt = false;

};

void torol()
{
    gout << color(0, 0, 0) << move_to(0, 0) << box(szelesseg, magassag) << refresh;
}

int main()
{
    srand(time(0));
    gout.open(600, 400);

    vector<block *> blocks;
    //block * elkapott = nullptr;
//    int elkapott;

    for(size_t i = 0; i<10; i++)
    {
        blocks.push_back(new block);
    }

    for(block * egyik: blocks)
    {
        egyik->draw();
    }

    bool lenyomva = false;

    gout << refresh;

    event ev;
    while(gin >> ev)
    {
        gin.timer(20);

        if(ev.type == ev_mouse)
        {
            if(ev.button == btn_left)
            {
                lenyomva = true;
                for(block *egyik : blocks)
                {
                    egyik->elenged();
                    egyik->draw();
                    if(egyik->folotte(ev.pos_x, ev.pos_y))
                    {
                        egyik->kijelol();
                        egyik->draw();
                    }
                    egyik->elkap(ev.pos_x, ev.pos_y);
                }

//                for(size_t i = 0;i<blocks.size();i++){
//                    if(blocks[i].folotte(ev.pos_x, ev.pos_y)){
//                        elkapott = i;
//                    }
//                    if(elkapott != -1){
//                        blocks[i].kijelol();
//                    }
                }
            }
            else if(ev.button == -btn_left)
            {
                lenyomva = false;
            }
            else if(ev.button == 0 and lenyomva)
            {
                for(block * egyik: blocks)
                {
                    if(egyik->kijelolte())
                    {
                        egyik->mozgat(ev.pos_x, ev.pos_y);
                        egyik->draw();
                    }
                }
            }
        }





    return 0;
}

