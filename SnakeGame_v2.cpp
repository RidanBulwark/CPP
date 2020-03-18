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

struct Coord {
    int posX, posY;
    Coord(int x, int y)
     :posX(x),
      posY(y)
      {
      }
    
    bool Coll(int x, int y){
      return (x == posX && y == posY);
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

    void Move(Irany UjIrany){
      for(size_t i = SnakeVect.size()-1; i>0;i--){
        SnakeVect[i]->posX = SnakeVect[i-1]->posX;
        SnakeVect[i]->posY = SnakeVect[i-1]->posY;
      }
      switch(UjIrany)
      {
      case Up:SHead->posY -=1;break;
      case Down:SHead->posY +=1;break;
      case Left:SHead->posX -=1;break;
      case Right:SHead->posX +=1;break;
      default:break;
      }
      cout << SHead->posX << " " << SHead->posY << '\n';
    }

    int X(){
        return SHead->posX;
    }
    int Y(){
        return SHead->posY;
    }

    bool SelfColl(){
      for(size_t i = 1;i<SnakeVect.size();i++){
        if(SnakeVect[i]->Coll(SHead->posX, SHead->posY)){
          return true;
        }
      }
      return false;
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
  bool Run = true;

  while(Run){
    Snake KigyoBacsi;
    gout.open(szelesseg*side, magassag*side);
    Wall Walls;
    Apple OneApple;
    stringstream ss;
    

    if(Status == 0){
      gout << color(255, 255, 255) << move_to(szelesseg*side/3, magassag*side/2-12) << text("Simple Snake Game")
            << move_to(szelesseg*side/4, magassag*side/2+12) << text("Press (Enter) - Play")
            << move_to(szelesseg*side/4, magassag*side/2+26) << text("Press (Esc) - Exit")
            << move_to(szelesseg*side/4, magassag*side/2+40) << text("Press (Space) - Hard Difficulty")
            << refresh;

      event ev;
      gin.timer(100);
      while(gin >> ev){
        if(ev.type == ev_key){
          switch (ev.keycode)
          {
          case key_escape:Run = false;break;
          case key_enter:Status = 1;break;
          case key_space : Status = 2;break;
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
      Irany NewDir = Up;
      bool CanMove = true;
      Score = 0;
      event ev;
      gin.timer(150);
      while(gin >> ev && Status == 1){
        if(ev.type == ev_timer){

          KigyoBacsi.Move(NewDir);
          CanMove = true;
          if(Walls.WallColl(KigyoBacsi.X(), KigyoBacsi.Y()) || KigyoBacsi.SelfColl()){
            Status = 9;
          }
          

          while(Walls.WallColl(OneApple.x, OneApple.y)){
            OneApple.Spawn();
          }

          if(OneApple.Eaten(KigyoBacsi.X(), KigyoBacsi.Y())){
            OneApple.Spawn();
            KigyoBacsi.PlusPart();
            Score += 1;
            cout << Score << '\n';
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

        if(ev.type == ev_key && CanMove){
          switch (ev.keycode)
          {
          case key_up: if(NewDir != Down){NewDir = Up; CanMove = false;} break;
          case key_down: if(NewDir != Up){NewDir = Down;CanMove = false;} break;
          case key_left: if(NewDir != Right){NewDir = Left;CanMove = false;} break;
          case key_right: if(NewDir != Left){NewDir = Right;CanMove = false;} break;
          case key_escape: Run = false; Status = 0; break;
          default:break;
          }
        }
      }
    }

    if(Status == 2){
      KigyoBacsi.Spawn();
      OneApple.Spawn();
      Walls.Spawn();
      Irany NewDir = Up;
      bool CanMove = true;
      Score = 0;
      event ev;
      gin.timer(50);
      while(gin >> ev && Status == 2){
        if(ev.type == ev_timer){
          
          KigyoBacsi.Move(NewDir);
          CanMove = true;
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
            KigyoBacsi.PlusPart();
            Score += 2;
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

        if(ev.type == ev_key && CanMove){
          switch (ev.keycode)
          {
          case key_up: if(NewDir != Down){NewDir = Up; CanMove = false;} break;
          case key_down: if(NewDir != Up){NewDir = Down;CanMove = false;} break;
          case key_left: if(NewDir != Right){NewDir = Left;CanMove = false;} break;
          case key_right: if(NewDir != Left){NewDir = Right;CanMove = false;} break;
          case key_escape: Run = false; Status = 0; break;
          default:break;
          }
        }
      }
    }

    if(Status == 9){
      ss << Score;
      gout << color(255, 255, 255) << move_to(szelesseg*side/3+10, magassag*side/2-30) << text("GAME OVER")
            << move_to(szelesseg*side/4, magassag*side/2-12) << text("Your Score: ") << text(ss.str())
            << move_to(szelesseg*side/4, magassag*side/2+12) << text("Press (Enter) - Play")
            << move_to(szelesseg*side/4, magassag*side/2+26) << text("Press (Escape) - Exit")
            << move_to(szelesseg*side/4, magassag*side/2+40) << text("Press (Space) - Hard Difficulty")
            << refresh;
      
      event ev;
      gin.timer(100);
      while(gin >> ev){
        if(ev.type == ev_key){
          switch (ev.keycode)
          {
          case key_escape:Run = false;break;
          case key_enter:Status = 1;break;
          case key_space:Status = 2;break;
          default:break;
          }
          break;
        }
      }
    }
  }
  return 0;
}
