#ifndef Animal_h
#define Animal_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "vector"


class Animal {
float z;
std::vector<AnimatedRect*> animation;
    
public:
    
    Animal(std::string="images/mouse/",float=0.0f, float=0.0f, float=0.5f, float=0.4f, float=0.2f, float=1.0f, float=1.0f, float=1.0f);
    Animal(std::string="images/mouse/",float=0.0f, float=0.0f, float=0.1f, float=0.1f);
    
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

    void draw(int dir);

    void redrawScene();

    ~Animal();
    
};

#endif
