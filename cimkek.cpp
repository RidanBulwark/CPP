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
protected:
    int x, y, szel, mag, dx, dy;
    bool kijelolt = false;
    int ertek = 0;

public:

    bool valtoztam = false;

    block()
        : szel(rand()% 30 + 20),
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
        // gout << color(200, 0, 0) << move_to(x, y) << box(szel, mag)
        //      << color(255, 255, 40) << move_to(x, y) << box(szel, keret)
        //      << box(-keret, mag-keret+1) << box(-szel+keret-1, -keret)
        //      << box(keret, -mag+keret) << refresh;
        stringstream ss;
        ss << ertek;
        string kiirat;
        ss >> kiirat;
        gout << color(255, 255, 40) << move_to(x, y) << box(szel, mag);
        gout << color(200, 0, 0) << move_to(x+keret, y+keret) << box(szel-2*keret, mag-2*keret);
        if(ertek >= 0){
            gout << color(255, 255, 255) << move_to(x+szel/2-4, y+mag/2+6) << text(kiirat);
        }
        else{
            gout << color(255, 255, 255) << move_to(x+szel/2-8, y+mag/2+6) << text(kiirat);
        }

        valtoztam = false;
        // gout << refresh;
    }

    void mozgat(int x, int y)
    {
        this->x = x - szel/2;
        this->y = y - mag/2;
        valtoztam = true;
        // draw();
    }

    // ez annyira nem kell am
    // void elkap(int ex, int ey)
    // {
    //     // dx = ex-x;
    //     // dy = ey-y;
    //     x += ex - (x + szel/2);
    //     y += ey - (y + mag/2);
    // }

    void kijelol()   //Setter
    {
        kijelolt = true;
        valtoztam = true;
    }
    void elenged()
    {
        kijelolt = false;
        valtoztam = true;
    }
    bool kijelolte() //Getter
    {
        return kijelolt;
    }

    bool folotte(int ex, int ey)
    {
        return (x < ex and ex < x + szel and
                y < ey and ey < y + mag);
    }

    void ertekno(){
        ertek += 1;
        valtoztam = true;
    }
    void ertekcsokk(){
        ertek -= 1;
        valtoztam = true;
    }
};

struct SpecBlock : block{
    public:
    void draw()
    {
        int keret = 2;
        if(kijelolt)
        {
            keret = 4;
        }
        // gout << color(200, 0, 0) << move_to(x, y) << box(szel, mag)
        //      << color(255, 255, 40) << move_to(x, y) << box(szel, keret)
        //      << box(-keret, mag-keret+1) << box(-szel+keret-1, -keret)
        //      << box(keret, -mag+keret) << refresh;
        stringstream ss;
        ss << ertek;
        string kiirat;
        ss >> kiirat;
        gout << color(20, 200, 200) << move_to(x, y) << box(szel, mag);
        gout << color(255, 20, 255) << move_to(x+keret, y+keret) << box(szel-2*keret, mag-2*keret);
//        cout << "Hali";
        if(ertek >= 0){
            gout << color(255, 255, 255) << move_to(x+szel/2-4, y+mag/2+6) << text(kiirat);
        }
        else{
            gout << color(255, 255, 255) << move_to(x+szel/2-12, y+mag/2+6) << text(kiirat);
        }

        valtoztam = false;
        // gout << refresh;
    }

    void ertekno(){
        ertek += 5;
        valtoztam = true;
    }
    void ertekcsokk(){
        ertek -= 5;
        valtoztam = true;
    }
};

void torol()
{
    gout << color(0, 0, 0) << move_to(0, 0) << box(szelesseg, magassag);
}



int main()
{
    srand(time(0));
    gout.open(600, 400);

    vector<block*> blocks;
    block *elkapott = nullptr;
//    int elkapott;

    for(size_t i = 0; i<9; i++)
    {
        blocks.push_back(new block());
    }
    SpecBlock * SBlock = new SpecBlock();
    SBlock->draw();
    for(block *egyik: blocks)
    {
        egyik->draw();
    }



    bool lenyomva = false;

    gout << refresh;
    // gin.timer(20);

    event ev;
    while(gin >> ev)
    {

        if(ev.type == ev_mouse)
        {
            if(ev.button == btn_left)
            {
                lenyomva = true;
                elkapott = nullptr;
                for(block *egyik : blocks)
                {
                    egyik->elenged();
                    SBlock->elenged();
                    if(SBlock->folotte(ev.pos_x,ev.pos_y)){
                        SBlock->kijelol();
                        elkapott = SBlock;
                        break;
                    }
                    if(egyik->folotte(ev.pos_x, ev.pos_y))
                    {
                        egyik->kijelol();
                        // egyik->elkap(ev.pos_x, ev.pos_y);
                        elkapott = egyik;
                        break;
                    }
                }
            }
            else if(ev.button == -btn_left)
            {
                lenyomva = false;
                for(block *egyik : blocks){
                    if(egyik != elkapott){
                        egyik->elenged();
                    }
                }
                if(SBlock != elkapott){
                    SBlock->elenged();
                }
            }
            else if(ev.button == 0 and lenyomva)
            {
                if (elkapott != nullptr)
                {
                    elkapott->mozgat(ev.pos_x, ev.pos_y);
                }
                // for(block *egyik: blocks)
                // {
                //     if(egyik->kijelolte())
                //     {
                //         egyik->mozgat(ev.pos_x, ev.pos_y);
                //         break;
                //     }
                // }
            }

        }

        if(ev.button == btn_wheelup){
            for(block *b : blocks){
                if(b->kijelolte()){
                    b->ertekno();
                }
            }
            if(SBlock->kijelolte()){
                SBlock->ertekno();
            }
        }
        if(ev.button == btn_wheeldown){
            for(block *b : blocks){
                if(b->kijelolte()){
                b->ertekcsokk();
            }
        }
            if(SBlock->kijelolte()){
                SBlock->ertekcsokk();
            }
        }

        bool kell_frissiteni = false;
        for (block *b : blocks)
        {
            if (b->valtoztam)
            {
                kell_frissiteni = true;
            }
        }
        if(SBlock->valtoztam)
        {
            kell_frissiteni = true;
        }

        if (kell_frissiteni)
        {
            torol();
            SBlock->draw();
            for (block *b : blocks)
            {
                b->draw();
            }
            gout << refresh;
        }



    }

    return 0;
}
