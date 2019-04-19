#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "App.h"


App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer

    singleton->ypos = singleton->projectile->getY();
    singleton->xpos = singleton->projectile->getX();

    if (singleton->up){
        singleton->ypos +=0.05;
        singleton->projectile->setY(singleton->ypos);
        singleton->redraw();
    }
    if (singleton->left){
        singleton->xpos -=0.05;
        singleton->projectile->setX(singleton->xpos);
        singleton->redraw();
    }
    if (singleton->down){
        singleton->ypos -=0.05;
        singleton->projectile->setY(singleton->ypos);
        singleton->redraw();
    }
    if (singleton->right){
        singleton->xpos +=0.05;
        singleton->projectile->setX(singleton->xpos);
        singleton->redraw();
    }
    // if(singleton->mushroom->contains(singleton->xpos, singleton->ypos)) {  
    //         singleton->explode = true;
    //         singleton->explosion->playOnce();
    //         // singleton->redraw();
    // }
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    // mushroom = new TexRect("mushroom.png", -0.25, 0.9, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    up = false;
    down = false;
    right = false;
    left = false;
    // explosion = new AnimatedRect("fireball.bmp", 6, 6, 50, true, true, -0.25, 0.9, 0.5, 0.5);
    // explode = false;
    //5x5 of blocks for now
    // float wid = 4/5.0;    //0.8
    // float hei = 2/5.0;   //0.4
    // srand( time(NULL) );
    // grid.push_back(new Block(-2, 1, wid, hei, 1, 0, 0));
    /*for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            float red = rand() % 2;
            float green = rand() % 2;
            float blue = rand() % 2;
            // std::cout << "x: " << i*wid-2 << ", y: " << j*-hei+1 << std::endl;
            grid.push_back(new Block(i*wid - 2, j*-hei + 1, wid, hei, red, green, blue));
        }
    }*/

    singleton = this;

    timer(1);
}

void App::draw() {
    // std::cout << "drawing" << std::endl;
    // for(int i = 0; i < grid.size(); i++) {
    //     grid[i]->draw();
    // }
    projectile->draw();
}

void App::keyUp(unsigned char key, float x, float y) {
    if(key == 'w') {
        // std::cout << "Done going up!" << std::endl;
        up = false;
    }
    if(key == 'a') {
        // std::cout << "Done going left!" << std::endl;
        left = false;
    }
    if(key == 's') {
        // std::cout << "Done going up!" << std::endl;
        down = false;
    }
    if(key == 'd') {
        // std::cout << "Done going right!" << std::endl;
        right = false;
    }
}

void App::keyDown(unsigned char key, float x, float y){
    // std::cout <<"test" << std::endl;
    if (key == 27){
        // std::cout <<"testing" << std::endl;
        exit(0);
    }
    if(key == 'w') {
        // std::cout << "Done going up!" << std::endl;
        up = true;
    }
    if(key == 'a') {
        // std::cout << "going left!" << std::endl;
        left = true;
    }
    if(key == 's') {
        // std::cout << "Done going up!" << std::endl;
        down = true;
    }
    if(key == 'd') {
        // std::cout << "going right!" << std::endl;
        right = true;
    }
    // float a, b;
    // grid[0]->getCoord(a, b);
    // std::cout << "(x, y) before: (" << a << ", " << b << ")" << std::endl;
    // switch (key) {  //For Arrow keys:
    //     case 100:   //Left
    //         // grid[0]->moveLeft();
    //         // draw();
    //         left = true;
    //         break;
    //     case 101:   //Up
    //         // grid[0]->moveUp();
    //         // draw();
    //         up = true;
    //         break;
    //     case 102:   //Right
    //         // grid[0]->moveRight();
    //         // draw();
    //         right = true;
    //         break;
    //     case 103:   //Down
    //         // grid[0]->moveDown();
    //         // draw();
    //         down = true;
    //         break;
    // }
    // std::cout << "(x, y) after: (" << a << ", " << b << ")" << std::endl;
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
}
