#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "TextBox.h"
// #include "Block.h"
#include "Layout.h"
#include "Animal.h"
#include "Mouse.h"
#include "Cat.h"
#include "vector"


class App: public GlutApp {
// enum Direction { Left, Up, Right, Down};  //0, 1, 2, 3

int dir;
int levels, current_level;
int total_score, total_possible;
float mapWidth, mapHeight, mapHalfWidth, mapHalfHeight;

// std::vector<Block*> grid;
std::vector<TexRect*> map;
std::vector<TexRect*> obstacle;
std::vector<Cat*> guards;
// std::vector<int> guard_dir;
std::vector<TexRect*> cheeses;
std::vector<bool> eaten;


TexRect* mushroom;
TextBox* gameOver;
TextBox* DisplayScore;
// Rect* projectile;
// AnimatedRect* explosion;
Mouse* mouse;
AnimatedRect* death;
float xpos, ypos, speed;
int num_Cheese;
int score;

bool up, down, left, right;
// bool explode;
bool alive;
bool start;
    
public:
    
    App(int argc, char** argv, int width, int height, const char* title);

    void createMap(int i);

    void nextLevel();

    void reset();

    bool touchWalls(float mx, float my);

    bool catTouchWalls(int i, float mx, float my);

    bool touchCheese(float mx, float my);

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
