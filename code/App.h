#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"
#include "TexRect.h"
#include "vector"


class App: public GlutApp {
TexRect* background;
TexRect* background2;
std::vector<TexRect*> backs;
AnimatedRect* kittie = new AnimatedRect("cat.png", 4, 2, 80, true, true, -0.5, -0.25, 1, 0.5);
float offset = 0.0;
int counter = 0;
    
public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
    
    void keyDown(unsigned char key, float x, float y);
    
    ~App();
    
    friend void timer(int);
    
};

#endif
