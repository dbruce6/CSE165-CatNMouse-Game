#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "App.h"

using namespace std;

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
        if(singleton->withinBounds(singleton->xpos, singleton->ypos)) {
            singleton->projectile->setY(singleton->ypos);
            singleton->redraw();
        }
    }
    if (singleton->left){
        singleton->xpos -=0.05;
        if(singleton->withinBounds(singleton->xpos, singleton->ypos)) {
            singleton->projectile->setX(singleton->xpos);
            singleton->redraw();
        }
    }
    if (singleton->down){
        singleton->ypos -=0.05;
        if(singleton->withinBounds(singleton->xpos, singleton->ypos)) {
            singleton->projectile->setY(singleton->ypos);
            singleton->redraw();
        }
    }
    if (singleton->right){
        singleton->xpos +=0.05;
        if(singleton->withinBounds(singleton->xpos, singleton->ypos)) {
            singleton->projectile->setX(singleton->xpos);
            singleton->redraw();
        }
    }

    if(singleton->mushroom->contains(singleton->xpos, singleton->ypos)) {  
            singleton->explode = true;
            // singleton->explosion->playOnce();
            singleton->redraw();
    }
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    mapWidth = width/250.0;
    mapHeight = height/250.0;
    // cout << "width/height:\t" << mapWidth << "/" << mapHeight << endl;
    mapHalfWidth = mapWidth/2.0;
    mapHalfHeight = mapHeight/2.0;
    // cout << mapHalfWidth << ", " << mapHalfHeight<<endl;
    
    // map/0.txt containsthe number of maps available besides itself
    // map/1.txt and so on will contain the map/layout of the level
    // Using: 0 for empty space, 1 starting loc, 2 for ending loc, 3 for CAT, 4 for obstacles
    // First line of textfile is the number of row followed by number of columns
    int m, lvl;
    ifstream infile("maps/0.txt");
    infile >> m;
    infile.close();
    // if(m == 1) { cout << ""}
    cout << "Choose from level 1 to " << m  << ": (Enter ints)"<< endl;
    while(!(cin >> lvl)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Integer only. Try Again: ";
    }
    cout << "You chose level " << lvl << "!" << endl;
    layout(lvl);

    mushroom = new TexRect("mushroom.png", -0.25, 0.9, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    projectile->setR(1.0);
    projectile->setG(0.0);
    projectile->setB(0.0);
    up = false;
    down = false;
    right = false;
    left = false;
    explosion = new AnimatedRect("fireball.bmp", 6, 6, 50, true, true, -0.25, 0.9, 0.5, 0.5);
    explode = false;
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

void App::layout(int i) {
    string filename = "maps/" + to_string(i) + ".txt";
    cout << "filename:\t" << filename << endl;
    ifstream infile(filename);
    int r, c;
    if(infile >> r >> c) {
        cout << "row, col:\t" << r << ", " << c << endl;
    }
    float blockHeight = mapHeight / r;
    float blockWidth = mapWidth / c;
    cout << "block w/h:\t" << blockWidth << ", " << blockHeight << endl;

    // map/0.txt containsthe number of maps available besides itself
    // map/1.txt and so on will contain the map/layout of the level
    // Using: 0 for empty space, 1 starting loc, 2 for ending loc, 3 for CAT, 4 for obstacles
    // First line of textfile is the number of row followed by number of columns
    for(int i = 0; i < r; i++) {    // rows
        for(int j = 0; j < c; j++) {    // columns
            int temp;
            infile >> temp;
            cout << temp << " ";
            switch (temp) {
                case 4: {   
                            // cout << "block" << endl;
                            map.push_back(new Rect(-mapHalfWidth+j*blockWidth, mapHalfHeight-i*blockHeight, blockWidth, blockHeight));
                            break;
                        }
                default: 
                    // cout <<"Error " << temp << endl;
                    break;
            }
        }
        cout << endl;
    }
}

bool App::withinBounds(float mx, float my) {
    // cout << mx << ", " << my << endl;
    // if(mx > mapHalfWidth) cout << "testing"<< endl;
    return (mx >= -mapHalfWidth && mx+projectile->getW() <= mapHalfWidth && my-projectile->getH() >= -mapHalfHeight && my <= mapHalfHeight);
}

void App::draw() {
    // std::cout << "drawing" << std::endl;
    // for(int i = 0; i < grid.size(); i++) {
    //     grid[i]->draw();
    // }
    if(explode) {
        explosion->draw(0.2);
    } else {
        mushroom->draw(0.1);
    }
    projectile->draw();
    for(int i = 0; i < map.size(); i++) {
        map[i]->draw();
    }
}

void App::keyUp(unsigned char key, float x, float y) {
    // std::cout <<"testing regular up" << std::endl;
    if(key == 'w') {
        // std::cout << "Done going up!" << std::endl;
        up = false;
    }
    if(key == 'a') {
        // std::cout << "Done going left!" << std::endl;
        left = false;
    }
    if(key == 's') {
        // std::cout << "Done going down!" << std::endl;
        down = false;
    }
    if(key == 'd') {
        // std::cout << "Done going right!" << std::endl;
        right = false;
    }
}

void App::keyDown(unsigned char key, float x, float y){
    // std::cout <<"testing regular down" << std::endl;
    if (key == 27){ //ESC key
        exit(0);
    }
    if(key == 'w') {
        // std::cout << "Going up!" << std::endl;
        up = true;
    }
    if(key == 'a') {
        // std::cout << "Going left!" << std::endl;
        left = true;
    }
    if(key == 's') {
        // std::cout << "Going down!" << std::endl;
        down = true;
    }
    if(key == 'd') {
        // std::cout << "Going right!" << std::endl;
        right = true;
    }
}

void App::specialKeyUp(int key, float x, float y) {
    // std::cout <<"Special Up called" << std::endl;
    if(key == 101) {
        // std::cout << "Going up!" << std::endl;
        up = false;
    }
    if(key == 100) {
        // std::cout << "Going left!" << std::endl;
        left = false;
    }
    if(key == 103) {
        // std::cout << "Going down!" << std::endl;
        down = false;
    }
    if(key == 102) {
        // std::cout << "Going right!" << std::endl;
        right = false;
    }
}

void App::specialKeyDown(int key, float x, float y){
    // std::cout <<"Special Down called" << std::endl;
    if(key == 101) {
        // std::cout << "Going up!" << std::endl;
        up = true;
    }
    if(key == 100) {
        // std::cout << "Going left!" << std::endl;
        left = true;
    }
    if(key == 103) {
        // std::cout << "Going down!" << std::endl;
        down = true;
    }
    if(key == 102) {
        // std::cout << "Going right!" << std::endl;
        right = true;
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
}
