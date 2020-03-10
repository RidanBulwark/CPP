#include "graphics.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sstream>


using namespace std;
using namespace genv;

const int szelesseg = 400, magassag = 400;
const int wid = 10, hei = 10;
int Status = 0;
bool Run = true;
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
            SnakeVect.push_back(new SnakePart(HeadPosX, HeadPosY + i*10));
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

    int WhereAmIX(){
        return SHead->posX;
    }
    int WhereAmIY(){
        return SHead->posY;
    }
};

struct WallCoord{
    struct WPos{
        int x, y;
    };
    WPos WStart, WEnd;
};

struct Wall{
private:
    int WHei = magassag, WWid = szelesseg;
    int WThic = 5;
public:
//    WallCoord left;
//    left.WStart.x = WThic;
//    left.WStart.y = WThic;
//    left.WEnd.x = WThic;
//    left.WEnd.y = magassag-WThic;
//    WallCoord up;
//    up.WStart.x = WThic;
//    up.WStart.y = WThic;
//    up.WEnd.x = szelesseg-WThic;
//    up.WEnd.y = WThic;
//    WallCoord right;
//    right.WStart.x = szelesseg-WThic;
//    right.WStart.y = WThic;
//    right.WEnd.x = szelesseg-WThic;
//    right.WEnd.y = magassag-WThic;
//    WallCoord down;
//    down.WStart.x = WThic;
//    down.WStart.y = magassag-WThic;
//    downb.WEnd.x = szelesseg-WThic;
//    right.WEnd.y = magassag-WThic;
//    vector<WallCoord> WCoords = {left, right, up, down};

    void WallUP(){
        gout << color(50, 180, 50) << move_to(0, 0) << box(WWid, WThic) <<
        box(-WThic, WHei-WThic+1) << box(-WWid+WThic-1, -WThic) << box(WThic,-WHei+2*WThic-1);
        gout << refresh;
    }

    void WallColl(int x, int y){
        if(x<WThic){
            Status = 9;
        }
        if(y<WThic) {
            Status = 9;
        }
        if(x>szelesseg-WThic) {
            Status = 9;
        }
        if(y>magassag-WThic){
            Status = 9;
        }

//        for(WallCoord egyik : WCoords){
//            if((egyik.WStart.x > x < egyik.WEnd.x) && (egyik.WStart.y > y < egyik.WEnd.y))
//        }
    }
};


void CLS(){
    gout << move_to(5,5) << color(0,0,0) << box(szelesseg-12, magassag-12);
    gout << refresh;
}

int main()
{
    srand(time(0));
    while(Run){
    Snake KigyoBacsi;
    gout.open(szelesseg, magassag);
    Wall Walls;

    if(Status == 0){
        gout << color(255, 255, 255) << move_to(szelesseg/3, magassag/2-12) << text("Simple Snake Game")
        << move_to(szelesseg/3, magassag/2+12) << text("Press (Enter) to play");
        gout << color(255, 255, 255) << move_to(szelesseg/3, magassag/2+26) << text("Press (Delete) to Exit");
        gout << refresh;
        event ev;
        gin.timer(100);
        while(gin >> ev){
            if(ev.type == ev_key){
                if(ev.keycode == key_delete){
                    Run = false;
                }
                if(ev.keycode == key_enter){
                    Status = 1;
                    break;
                }
                break;
            }
        }
    }

    if(Status == 1){
//    KigyoBacsi.AddHead();
    KigyoBacsi.PlusPart(10);
    KigyoBacsi.Draw();
    Walls.WallUP();

    event ev;
    gin.timer(50);
    while(gin >> ev && Status == 1){

        if(ev.type == ev_timer){
            KigyoBacsi.Move();
            CLS();
            KigyoBacsi.Draw();
            Walls.WallColl(KigyoBacsi.WhereAmIX(), KigyoBacsi.WhereAmIY());
            cout << KigyoBacsi.WhereAmIX() << " " << KigyoBacsi.WhereAmIY() << '\n';
            if(Status == 9){
                break;
            }
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


    }

    if(Status == 9){
        gout << color(255, 255, 255) << move_to(szelesseg/3, magassag/2-12) << text("GAME OVER")
        << move_to(szelesseg/3, magassag/2+12) << text("Press (Enter) to Play");
        gout << color(255, 255, 255) << move_to(szelesseg/3, magassag/2+26) << text("Press (Delete) to Exit");
        gout << refresh;
        event ev;
        gin.timer(100);
        while(gin >> ev){
            if(ev.type == ev_key){
                if(ev.keycode == key_delete){
                    Run = false;
                }
                if(ev.keycode == key_enter){
                    cout << "egy";
                    Status = 1;
                    break;
                }
                break;
            }
        }
    }


    }
    return 0;
}
