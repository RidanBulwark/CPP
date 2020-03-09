#include "graphics.hpp"

using namespace genv;

int main(){
    gout.open(600,600);

    for (int i = 0; i < 18; i++)
    {
        int y = 300 + 15*i;
        int x = 40 + 15*i;
        gout << color(0, 40+i*10, 240-i*10);
        //bal alsó
        gout << move_to(x, 300);
        gout << line_to(300, y);
        //jobb felsõ
        gout << move_to(600 - x, 300);
        gout << line_to(300, 600 - y);

         gout << color(0, 240-i*10, 40+i*10);
        //jobb alsó
        gout << move_to(600 - x, 300);
        gout << line_to(300, y);
        //bal felsõ
        gout << move_to(x, 300);
        gout << line_to(300, 600 - y);

    }

    gout << move_to(300, 40) << color(0, 240, 40);
    gout << line_to(300, 560);
    gout << move_to(40, 300);
    gout << line_to(560, 300);
    gout << refresh;

    event ev;
    while(gin >> ev);
    return 0;
}
