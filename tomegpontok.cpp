#include "graphics.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace genv;

const int szelesseg = 400;
const int magassag = 400;

struct pont{
    int holx, holy;
    int mag = 5;
    int szel = 5;

    pont(int holx_, int holy_):holx(holx_), holy(holy_){}

    void rajzol(){
        gout << color(10, 10, 220) << move_to(holx, holy) << box(mag, szel);
    }


    void mozog(){
        int px = szelesseg;
        int py = magassag;
    }

};

void torol(int szelesseg, int magassag){
    gout << color(0,0,0) << move_to(0,0) << box(szelesseg, magassag) << refresh;
}

int main()
{
    gout.open(szelesseg,magassag);

    pont p1(szelesseg/2, 40);
    pont p2(40, magassag/2);
    pont p3(szelesseg-50, magassag/2 +50);
    p1.rajzol();
    p2.rajzol();
    p3.rajzol();


    event ev;
        float dx = 0;
        float dy = 0;
        int times = 0;
    while(gin >> ev) {
        gin.timer(50);

        if(ev.type == ev_timer){
            dx = p1.holx - p2.holx;
            dy = p1.holy - p2.holy;
            p1.holx -= 0.2*dx;
            p1.holy -= 0.2*dy;
            p1.rajzol();

            dx = p2.holx - p3.holx;
            dy = p2.holy - p3.holy;
            p2.holx -= 0.2*dx;
            p2.holy -= 0.2*dy;
            p2.rajzol();

            dx = p3.holx - p1.holx;
            dy = p3.holy - p1.holy;
            p3.holx -= 0.2*dx;
            p3.holy -= 0.2*dy;
            p3.rajzol();

            times += 1;
            if(times == 30){
                torol(szelesseg, magassag);
                times = 0;
                p1.holx = szelesseg/2;
                p1.holy = 40;
                p2.holx = 40;
                p2.holy = magassag/2;
                p3.holx = szelesseg-50;
                p3.holy = magassag/2 + 50;
                p1.rajzol();
                p2.rajzol();
                p3.rajzol();
                 dx = 0;
                 dy = 0;
            }
        }
        gout << refresh;


    }
    return 0;
}
