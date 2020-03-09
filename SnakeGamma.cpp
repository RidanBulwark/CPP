#include "graphics.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>


using namespace std;
using namespace genv;

const int szelesseg = 400, magassag = 400;
const int wid = 10, hei = 10;
struct SnakePart {
    int posX, posY;

    SnakePart(int x, int y)
     :posX(x),
      posY(y)
      {
      }
};

struct Snake{
private:
    vector<SnakePart *> SnakeVect;
    int HeadPosX = szelesseg/2-wid;
    int HeadPosY = magassag/2-hei;
    int Direction = 1;
    SnakePart *SHead = nullptr;
public:

//    void AddHead(){
//        SnakeVect.push_back(new SnakePart(HeadPosX, HeadPosY));
//    }

    void PlusPart(int mennyit){
        for(size_t i = 0; i<mennyit+1; i++){
            SnakeVect.push_back(new SnakePart(HeadPosX, HeadPosY + i*12));
            //cout << HeadPosX << " " << HeadPosY << '\n';
        }
        SHead = SnakeVect[0];
    }

    void Draw(){
        for(size_t i = 0; i<SnakeVect.size();i++){
            gout << color(0, 20, 220) <<
            move_to(SnakeVect[i]->posX, SnakeVect[i]->posY + i*2) << box(hei, wid);
            //cout << "Spawnolni kéne";
        }
        gout << refresh;
    }

    void SUp(){
        Direction = 1;
    }
    void SLeft(){
        Direction = 2;
    }
    void SRight(){
        Direction = 3;
    }
    void SDown(){
        Direction = 4;
    }

    void Move(){
        if(Direction == 1){
            for(size_t i = SnakeVect.size()-1; i>0;i--){
                SnakeVect[i]->posX = SnakeVect[i-1]->posX;
                SnakeVect[i]->posY = SnakeVect[i-1]->posY-2;
            }
            SHead->posY -=12;
        }
        if(Direction == 2){
            for(size_t i = SnakeVect.size()-1; i>0;i--){
                SnakeVect[i]->posX = SnakeVect[i-1]->posX;
                SnakeVect[i]->posY = SnakeVect[i-1]->posY-2;
            }
            SHead->posX -=12;
        }
        if(Direction == 3){
            for(size_t i = SnakeVect.size()-1; i>0;i--){
                SnakeVect[i]->posX = SnakeVect[i-1]->posX;
                SnakeVect[i]->posY = SnakeVect[i-1]->posY-2;
            }
            SHead->posX +=12;
        }
        if(Direction == 4){
            for(size_t i = SnakeVect.size()-1; i>0;i--){
                SnakeVect[i]->posX = SnakeVect[i-1]->posX;
                SnakeVect[i]->posY = SnakeVect[i-1]->posY-2;
            }
            SHead->posY +=12;
        }
    }
};

void CLS(){
    gout << move_to(0,0) << color(0,0,0) << box(szelesseg, magassag);
    gout << refresh;
}

int main()
{
    srand(time(0));

    Snake KigyoBacsi;
    gout.open(szelesseg, magassag);

//    KigyoBacsi.AddHead();
    KigyoBacsi.PlusPart(10);
    KigyoBacsi.Draw();


    event ev;
    gin.timer(100);
    while(gin >> ev){

        if(ev.type == ev_timer){
            KigyoBacsi.Move();
            CLS();
            KigyoBacsi.Draw();
        }

        if(ev.type == ev_key)
            if(ev.keycode == key_up){
                KigyoBacsi.SUp();
            }
            if(ev.keycode == key_left){
                KigyoBacsi.SLeft();
            }
            if(ev.keycode == key_right){
                KigyoBacsi.SRight();
            }
            if(ev.keycode == key_down){
                KigyoBacsi.SDown();
            }
        }


    return 0;
}
