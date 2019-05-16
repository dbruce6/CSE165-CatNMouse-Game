#ifndef Cat_h
#define Cat_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "vector"
#include "Animal.h"


class Cat : public Animal {
    int dir;
public:
    Cat(float=0.0f, float=0.0f, float=0.5f, float=0.1f, float=0.1f);

    int getDir() {return dir;};
    bool setDir(int);

    bool TouchWalls(std::vector<TexRect*> map, std::vector<TexRect*>obstacle, float speed, float mx, float my);
    
    ~Cat();
};

#endif
