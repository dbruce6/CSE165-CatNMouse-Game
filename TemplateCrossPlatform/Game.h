#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
    TexRect* mushroom;
    Rect* projectile;
    
    bool projectileVisible;
    bool mushroomVisible;
    bool up;
    bool left;
    bool right;
    bool down;
    bool hit;
    float theta;
    float deg;
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    void handleKeyUp(unsigned char, float, float);
    void specialKeyUp(int key, float x, float y);
    void specialKeyDown(int key, float x, float y);
    
    void action();

    ~Game();

};

#endif 
