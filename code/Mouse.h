#ifndef Mouse_h
#define Mouse_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "vector"
#include "Animal.h"


class Mouse : public Animal {
    bool moving;
    std::vector<TexRect*> notMoving;
public:
    Mouse(float=0.0f, float=0.0f, float=0.5f, float=0.1f, float=0.1f);
    
    void setX(float);
    void setY(float);

    bool getMoving();
    void setMoving(bool);

    void draw(int);
    
    ~Mouse();
};

#endif
