#ifndef Mouse_h
#define Mouse_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "vector"


class Mouse {
// float x, y, w, h, r, g, b;
float z;
vector<AnimatedRect*> animation;

enum Direction { Left, Up, Right, Down};  //0, 1, 2, 3
    
public:
    
    Mouse(float=0.0f, float=0.0f, float=0.5f, float=0.4f, float=0.2f, float=1.0f, float=1.0f, float=1.0f));
    Mouse(float=0.0f, float=0.0f, float=0.5f, float=0.1f, float=0.1f);

    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    float getH() const;
    
    float getR() const;
    float getG() const;
    float getB() const;
    
    void setX(float);
    void setY(float);
    void setZ(float);
    void setW(float);
    void setH(float);
    
    void setR(float);
    void setG(float);
    void setB(float);

    bool contains(float, float) const;
    
    void draw(Direction dir);

    int translate(Direction dir);

    void redrawScene();

    ~Mouse();
    
};

#endif
