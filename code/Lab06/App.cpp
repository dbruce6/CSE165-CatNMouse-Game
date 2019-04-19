#include <iostream>
#include "App.h"

App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer

    if (singleton->up){
        singleton->ypos = singleton->projectile->getY();
        singleton->xpos = singleton->projectile->getX();
        singleton->ypos +=0.05;
        singleton->projectile->setY(singleton->ypos);
        singleton->redraw();
    }
    if(singleton->mushroom->contains(singleton->xpos, singleton->ypos)) {  
            singleton->explode = true;
            singleton->explosion->playOnce();
            // singleton->redraw();
    }
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    
    mushroom = new TexRect("mushroom.png", -0.25, 0.9, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    up = false;
    explosion = new AnimatedRect("fireball.bmp", 6, 6, 50, true, true, -0.25, 0.9, 0.5, 0.5);
    explode = false;

    singleton = this;
    
    timer(1);
}

void App::draw() {
    if(!explode) { 
        mushroom->draw(0.1);
        projectile->draw(); 
    } else {
        explosion->draw(1.0);
    }

}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    if (key == ' '){
        up = true;
    }
}

App::~App(){
    delete mushroom;
    delete projectile;
    delete explosion;
    std::cout << "Exiting..." << std::endl;
}
