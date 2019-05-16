#ifndef Mouse_h
#define Mouse_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "vector"
#include "Animal.h"


class Mouse : public Animal {
public:
    Mouse(float=0.0f, float=0.0f, float=0.5f, float=0.4f, float=0.2f, float=1.0f, float=1.0f, float=1.0f);

    ~Mouse();
    
};

#endif
