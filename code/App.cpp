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
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    //5x5 of blocks for now
    float wid = 4/5.0;    //0.8
    float hei = 2/5.0;   //0.4
    srand( time(NULL) );
    grid.push_back(new Block(-2, 1, wid, hei, 1, 0, 0));
    /*for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            float red = rand() % 2;
            float green = rand() % 2;
            float blue = rand() % 2;
            // std::cout << "x: " << i*wid-2 << ", y: " << j*-hei+1 << std::endl;
            grid.push_back(new Block(i*wid - 2, j*-hei + 1, wid, hei, red, green, blue));
        }
    }*/
}

void App::draw() {
    std::cout << "drawing" << std::endl;
    for(int i = 0; i < grid.size(); i++) {
        grid[i]->draw();
    }
}

void App::keyDown(unsigned char key, float x, float y){
    // std::cout <<"test" << std::endl;
    if (key == 27){
        // std::cout <<"testing" << std::endl;
        exit(0);
    }
    float a, b;
    grid[0]->getCoord(a, b);
    std::cout << "(x, y) before: (" << a << ", " << b << ")" << std::endl;
    switch (key) {  //For Arrow keys:
        case 100:   //Left
            grid[0]->moveLeft();
            draw();
            break;
        case 101:   //Up
            grid[0]->moveUp();
            draw();
            break;
        case 102:   //Right
            grid[0]->moveRight();
            draw();
            break;
        case 103:   //Down
            grid[0]->moveDown();
            draw();
            break;
    }
    // std::cout << "(x, y) after: (" << a << ", " << b << ")" << std::endl;
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
}
