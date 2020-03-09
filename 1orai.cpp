#include "graphics.hpp"
using namespace genv;


int main()
{
/*  gout.open(200,200);
    gout << move(-20, 0);
    gout << line(40, 0);
    gout << line(-20, -20);
    gout << line(-21, 20);
    gout << refresh;*/

/*  gout.open(200,200);
    gout << move_to(10, 10);
    gout << color(0, 0, 230);
    gout << box(180, 180);
    gout << color(255, 255, 255);
    gout << move_to(80, 100);
    gout << line(40, 0);
    gout << line(-20, -20);
    gout << line(-21, 20);
    gout << refresh; */


/*  gout.open(200,200);
    event ev;
    while(gin >> ev) {
        gout << move_to(ev.pos_x, ev.pos_y);

        if(ev.button == 1){
        gout << dot;}
        gout << refresh;

    //vagy
        if(ev.type == ev_mouse and ev.button == btn_left) {
            gout << move_to(ev.pos_x, ev.pos_y) << dot;
        }
        gout << refresh;
    } */

/*  gout.open(200,200);
    event ev;
    bool frst = true;
    while(gin >> ev) {
        if(frst && (ev.type == ev_mouse and ev.button == btn_left)){
            gout << move_to(ev.pos_x, ev.pos_y);
            frst = false;
        }

        if(ev.type == ev_mouse and ev.button == btn_left){
            gout << line_to(ev.pos_x, ev.pos_y);
        }
        gout << refresh;
    }*/

/*    gout.open(300,300);
    event ev;
    while (gin >> ev){
        if(ev.type == ev_mouse and ev.button == 0){
            gout << move_to(0,0)<< color(0,0,0) << box(300,300);
            gout << color(255, 255, 255);
            gout << move_to(150,150) << line_to(ev.pos_x, ev.pos_y);
        }
        gout <<refresh;
    }*/


    gout.open(600,600);
    gout << move_to(50, 300);
    gout << line_to(300, 300);
    gout << refresh;

    event ev;
    while(gin >> ev){

    }

    return 0;
}
