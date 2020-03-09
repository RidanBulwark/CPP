#include "graphics.hpp"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
using namespace genv;

void beolvas(ifstream & bf, canvas &c, int szelesseg, int magassag){


    int r, g, b;
    for(int i = 0;i<magassag;i++){
        for(int j = 0;j<szelesseg;j++){
                bf >> r >> ws >> g >> b >> ws;
                c << move_to(j, i) << color(r, g, b) << dot;
        }
    }
}

int main()
{
    int szelesseg;
    int magassag;
    ifstream bf("a.kep");

    if(!bf.good()){
        cout << "He";}
    canvas c;
    bf >> szelesseg >> magassag;
    c.open(szelesseg, magassag);

    gout.open(szelesseg, magassag);
    beolvas(bf, c, szelesseg, magassag);

    event ev;
    while(gin >> ev) {
        gout << stamp(c, ev.pos_x-300, ev.pos_y-200);
        gout << refresh;
        gout << move_to(0, 0) << color(0,0,0) << box(szelesseg, magassag);
    }
    return 0;
}

