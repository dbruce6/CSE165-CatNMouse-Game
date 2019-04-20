#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
// #include "Block.h"
#include "Layout.h"
#include "vector"


class App: public GlutApp {
float mapWidth, mapHeight, mapHalfWidth, mapHalfHeight;

// std::vector<Block*> grid;
std::vector<Rect*> map;

TexRect* mushroom;
Rect* projectile;
AnimatedRect* explosion;
float xpos, ypos;

bool up, down, left, right;
bool explode;
    
public:
    
    App(int argc, char** argv, int width, int height, const char* title);

    void layout(int i);

    bool touchWalls(float mx, float my);

    bool withinBounds(float mx, float my);
    
    void draw();

    void keyUp(unsigned char key, float x, float y);
    
    void keyDown(unsigned char key, float x, float y);

    void specialKeyUp(int key, float x, float y);
    
    void specialKeyDown(int key, float x, float y);
    
    ~App();
    
    friend void timer(int);
    
};

#endif
