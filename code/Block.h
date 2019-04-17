#ifndef Block_h
#define Block_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

class Block{
//protected:

//Top-left corner: 
    float x;
    float y;
//Dimensions: 
    float w;
    float h;
//Color: 
    float r;
    float g;
    float b;
    
public:
    Block(float x, float y, float w, float h, float r, float g, float b);
    virtual ~Block();
    
    void getCoord(float& _x, float& _y);
    void getDimension(float& _w, float& _h);
    void getColor(float& _r, float& _g, float& _b);
    void setCoord(float _x, float _y);
    void setDimension(float _w, float _h);
    void setColor(float _r, float _g, float _b);
    
    void draw();
    
    bool moveLeft();
    bool moveUp();
    bool moveRight();
    bool moveDown();
};

#endif
