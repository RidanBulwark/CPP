#include "graphics.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sstream>


using namespace std;
using namespace genv;

const int szelesseg = 50, magassag = 50;
const int side = 8;
int Status = 0;
bool Run = true;
struct Coord {
    int posX, posY;

    Coord(int x, int y)
     :posX(x),
      posY(y)
      {
      }
    
    void Coll(int x, int y){
      if(x == posX && y == posY){
        Status = 9;
      }
    }
};

enum Irany{
  Up = 1,
  Down = -1,
  Left = 2,
  Right = -2
};

struct Snake{
private:
    vector<Coord *> SnakeVect;
    int HeadPosX = szelesseg/2;
    int HeadPosY = magassag/2;
    Coord *SHead = nullptr;
public:
  Irany Direction = Up;
    void Spawn(){
      for(size_t i = 0; i<3; i++){
        SnakeVect.push_back(new Coord(HeadPosX, HeadPosY + i));  
      }
      SHead = SnakeVect[0];
    }

    void PlusPart(){
        Coord *Tail = SnakeVect[SnakeVect.size()-1];
        SnakeVect.push_back(new Coord(Tail->posX, Tail->posY));
    }

    void Draw(){
        for(Coord *s: SnakeVect){
          gout << color(0, 20, 220) <<
          move_to(s->posX*side, s->posY*side) << box(side, side);
        }
    }

    void Move(Irany Direction){
      for(size_t i = SnakeVect.size()-1; i>0;i--){
        SnakeVect[i]->posX = SnakeVect[i-1]->posX;
        SnakeVect[i]->posY = SnakeVect[i-1]->posY;
      }
      switch(Direction)
      {
      case Up:SHead->posY -=1;break;
      case Down:SHead->posY +=1;break;
      case Left:SHead->posX -=1;break;
      case Right:SHead->posX +=1;break;
      default:break;
      }
      //cout << SHead->posX << " " << SHead->posY << '\n';
    }

    int X(){
        return SHead->posX;
    }
    int Y(){
        return SHead->posY;
    }

    void SelfColl(){
      for(size_t i = 1;i<SnakeVect.size();i++){
        SnakeVect[i]->Coll(SHead->posX, SHead->posY);
      }
    }
};

struct Wall{
private:
  vector<Coord *> WallVect;
public:
    void Spawn(){
      for(int i = 0;i<15;i++){
        WallVect.push_back(new Coord(i, 19));
      }
      for(int i = 15;i<35;i++){
        WallVect.push_back(new Coord(i, 38));
      }
    }

    void Draw(){
        for(Coord *w: WallVect){
          gout << color(50, 180, 50) << move_to(w->posX*side, w->posY*side) << box(side, side);  
        }
        gout << move_to(0, 0) 
             << box(szelesseg*side, side) 
             << box(-side, magassag*side-side+1) 
             << box(-szelesseg*side+side-1, -side) 
             << box(side,-magassag*side+2*side-1);
    }

    bool WallColl(int x, int y){
        if(x==0 || y==0 || x==szelesseg-1 || y==magassag-1){
          return true;
        }
        for(Coord *w:WallVect){
          if(x==w->posX && y==w->posY){
             return true; 
          }
        }
      return false;
    }
};

struct Apple{
    int x = 3, y = 5;

    void Spawn(){
       x = (rand()%(szelesseg-2))+1;
       y = (rand()%(magassag-2))+1;
    }

    void Draw(){
      gout << color(240, 20, 20) << move_to(x*side, y*side) << box(side, side);
    }

    bool Eaten(int x, int y){
      return(this->x == x && this->y==y);
    }
};


void CLS(){
    gout << move_to(0,0) << color(0,0,0) << box(szelesseg*side, magassag*side) 
    << refresh;
}

int main()
{
  srand(time(0));
  int Score = 0;

  while(Run){
    Snake KigyoBacsi;
    gout.open(szelesseg*side, magassag*side);
    Wall Walls;
    Apple OneApple;
    stringstream ss;
    

    if(Status == 0){
      gout << color(255, 255, 255) << move_to(szelesseg*side/3, magassag*side/2-12) << text("Simple Snake Game")
            << move_to(szelesseg*side/3, magassag*side/2+12) << text("Press (Enter) to play")
            << move_to(szelesseg*side/3, magassag*side/2+26) << text("Press (Esc) to Exit")
            << refresh;

      event ev;
      gin.timer(100);
      while(gin >> ev){
        if(ev.type == ev_key){
          switch (ev.keycode)
          {
          case key_escape:Run = false;break;
          case key_enter:Status = 1;break;
          default:break;
          }
          break;
        }
      }
    }

    if(Status == 1){
      KigyoBacsi.Spawn();
      OneApple.Spawn();
      Walls.Spawn();
      event ev;
      gin.timer(150);
      while(gin >> ev && Status == 1){
        if(ev.type == ev_timer){
          
          KigyoBacsi.Move(KigyoBacsi.Direction);
          if(Walls.WallColl(KigyoBacsi.X(), KigyoBacsi.Y())){
            Status = 9;
          }
          KigyoBacsi.SelfColl();

          while(Walls.WallColl(OneApple.x, OneApple.y)){
            OneApple.Spawn();
          }

          if(OneApple.Eaten(KigyoBacsi.X(), KigyoBacsi.Y())){
            OneApple.Spawn();
            KigyoBacsi.PlusPart();
            Score += 1;
          }  

          if(Status == 9){
            break;
          }

          CLS();
          KigyoBacsi.Draw();
          Walls.Draw();
          OneApple.Draw();
          gout << refresh;  
        }

        if(ev.type == ev_key){
          switch (ev.keycode)
          {
          case key_up: if(KigyoBacsi.Direction != Down){KigyoBacsi.Direction = Up;}; break;
          case key_down: if(KigyoBacsi.Direction != Up){KigyoBacsi.Direction = Down;}; break;
          case key_left: if(KigyoBacsi.Direction != Right){KigyoBacsi.Direction = Left;} break;
          case key_right: if(KigyoBacsi.Direction != Left){KigyoBacsi.Direction = Right;} break;
          case key_escape: Run = false; Status = 0; break;
          default:break;
          }
        }
      }
    }

    if(Status == 9){
      ss << Score;
      gout << color(255, 255, 255) << move_to(szelesseg*side/3, magassag*side/2-24) << text("GAME OVER")
            << move_to(szelesseg*side/3, magassag*side/2-12) << text("Your Score: ") << text(ss.str())
            << move_to(szelesseg*side/3, magassag*side/2+12) << text("Press (Enter) to Play")
            << color(255, 255, 255) << move_to(szelesseg*side/3, magassag*side/2+26) << text("Press (Escape) to Exit")
            << refresh;
      Score = 0;
      event ev;
      gin.timer(100);
      while(gin >> ev){
        if(ev.type == ev_key){
          switch (ev.keycode)
          {
          case key_escape:Run = false;break;
          case key_enter:Status = 1;break;
          default:break;
          }
          break;
        }
      }
    }
  }
  return 0;
}
