#include "graphics.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <cstdlib>


using namespace std;
using namespace genv;


struct ho{
    int x, y;

    ho(int x_, int y_):x(x_), y(y_){}

    void rajzol() {
        gout << color(255, 255, 255) << move_to(x, y) << dot;
    }

    void mozog(int dx, int dy) {
        x = (x + dx);
        y = (y + dy);
    }

    int GetY(){  // ez nem volt
        return y;
    }

};

void ujat(vector<ho *> & havak, int szelesseg, int vastagon, int mennyit){
        for(int i = 0;i<mennyit;i++){
            ho * egy = new ho(rand()%szelesseg, rand()%vastagon);
            havak.push_back(egy);
        }
}

void torol(int szelesseg, int magassag){
    gout << color(0,0,0) << move_to(0, 0) << box(szelesseg, magassag);
}

int main()
{
    int szelesseg = 600;
    int magassag = 400;
    int vastagon = 10;
    int mennyit = 1000;

    gout.open(szelesseg, magassag);
    vector<ho *> havak;
    ujat(havak, szelesseg, vastagon, mennyit);

//    *ho[i]->rajzol
//    new ho

    gin.timer(20);
    event ev;
    int null = 0;
    while(gin >> ev) {
        if(ev.type == ev_timer){
            for(size_t i = 0;i<havak.size();i++){
                if(havak[i]){
                    havak[i]->rajzol();
                    havak[i]->mozog(pow(-1, rand()%2), rand()%5);
                    if(havak[i]->y > magassag){
                        null += 1;
                        delete havak[i];
                        havak[i] = nullptr;
                    }
                }
            }
            gout << refresh;
            torol(szelesseg, magassag);
        }

        if(ev.type == ev_key){
            if(ev.keycode == key_space){
            ujat(havak, szelesseg, vastagon, mennyit);}

            else if(ev.keycode == 99){
                vector<ho* > uj;
                for(ho *pehely : havak){
                    if(pehely){ //ha nullpointerre mutat..?
                        uj.push_back(pehely);
                    }
                }
                havak = uj;
                null = 0;
            }
        }



        stringstream ss;

        ss << "Vector size:" << havak.size() << " Null pointers: " << null;
        gout << color(255, 255, 255) << move_to(20, 20) << text(ss.str());

    }
    return 0;
}

