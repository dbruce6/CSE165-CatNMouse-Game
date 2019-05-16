#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "App.h"

using namespace std;

App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once

    // If you want to manipulate the app in here
    // do it through the singleton pointer

    // if(singleton->score >= singleton->num_Cheese) {
    //     cout << "Next Level!" << endl;
    //     singleton->nextLevel();
    // }

    for(int i = 0; i < singleton->guards.size(); i++) {
        bool cat_in_graphic = singleton->withinBounds(singleton->guards[i]->getX(), singleton->guards[i]->getY() );
        bool cat_not_hitting_walls = !singleton->guards.at(i)->TouchWalls(singleton->map, singleton->obstacle, singleton->speed, singleton->guards.at(i)->getX(), singleton->guards.at(i)->getY());
        bool catOK = cat_in_graphic && cat_not_hitting_walls;
        if(!catOK) {
            if(singleton->guards.at(i)->getDir() == 0) {
                singleton->guards.at(i)->setDir(2);
            } else {
                singleton->guards.at(i)->setDir(0);
            }
        }

        if(singleton->guards.at(i)->getDir() == 0) {  // Going Left
            singleton->guards[i]->setX(singleton->guards[i]->getX() - singleton->speed);
        } else {    // Going Right
            singleton->guards[i]->setX(singleton->guards[i]->getX() + singleton->speed);
        }
    }

    singleton->ypos = singleton->mouse->getY();
    singleton->xpos = singleton->mouse->getX();

    if(singleton->alive) {
        if (singleton->up){
            singleton->ypos +=singleton->speed;
        }
        if (singleton->left){
            singleton->xpos -=singleton->speed;
        }
        if (singleton->down){
            singleton->ypos -=singleton->speed;
        }
        if (singleton->right){
            singleton->xpos +=singleton->speed;
        }

        if(singleton->withinBounds(singleton->xpos, singleton->ypos) && !singleton->touchWalls(singleton->xpos, singleton->ypos)) {
            singleton->mouse->setX(singleton->xpos);
            singleton->mouse->setY(singleton->ypos);
            singleton->redraw();
        }

        singleton->touchCheese(singleton->xpos, singleton->ypos);

        for(int i = 0; i < singleton->obstacle.size(); i++) {
            if(singleton->obstacle[i]->contains(singleton->xpos, singleton->ypos)) {
                singleton->alive = false;
                singleton->death->setX(singleton->xpos);
                singleton->death->setY(singleton->ypos);
                singleton->death->playOnce();
                singleton->redraw();
            }
        }

        for(int i = 0; i < singleton->guards.size(); i++) {
            if(singleton->guards.at(i)->contains(singleton->xpos, singleton->ypos)) {
                singleton->alive = false;
                singleton->death->setX(singleton->xpos);
                singleton->death->setY(singleton->ypos);
                singleton->death->playOnce();
                singleton->redraw();
            }
        }

         if(singleton->mushroom->contains(singleton->xpos, singleton->ypos)) {
            singleton->redraw();
            singleton->nextLevel();

        }
    }

    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){

    mapWidth = width/250.0;
    mapHeight = height/250.0;
    mapHalfWidth = mapWidth/2.0;
    mapHalfHeight = mapHeight/2.0;
    speed = 0.01;

    // map/0.txt containsthe number of maps available besides itself
    // map/1.txt and so on will contain the map/layout of the level
    // First line of textfile is the number of row followed by number of columns
    ifstream infile("maps/0.txt");
    infile >> levels;
    current_level = 1;
    total_score = 0;
    total_possible = 0;
    createMap(current_level);
    score = 0;
    dir = 2;
    start = true;
    up = false;
    down = false;
    right = false;
    left = false;
    alive = true;

    singleton = this;

    timer(1);
}

void App::createMap(int i) {
    string filename = "maps/" + to_string(i) + ".txt";
    ifstream infile(filename);
    int r, c;
    if(infile >> r >> c) {
        // cout << "row, col:\t" << r << ", " << c << endl;
    }
    float blockHeight = mapHeight / r;
    float blockWidth = mapWidth / c;
    for(int i = 0; i < r; i++) {    // rows
        for(int j = 0; j < c; j++) {    // columns
            float x = -mapHalfWidth+j*blockWidth;
            float y = mapHalfHeight-i*blockHeight;

            int temp;
            infile >> temp;
            // cout << temp << " ";
            switch (temp) {
                case 1: {   // Starting the mouse:
                            mouse = new Mouse(x, y, 1.0f, 0.1f, 0.1f);
                            mouse->setMoving(false);
                            death = new AnimatedRect("images/dyinganimation/dyinganimation.png", 4, 4, 75, true, true, x, y, 0.1f, 0.1f);
                            break;
                        }
                case 2: {   // Goal:
                            mushroom = new TexRect("images/goal/0.png", x, y, blockWidth, blockHeight);
                            break;
                        }
                case 3: {   // Cat or some patrolling bot here: Cats will patrol left to right
                            guards.push_back(new Cat(x, y, 1.0f, blockWidth/3, blockHeight/3));
                            break;
                        }
                case 4: {   // Walls that form the layout of the level:
                            map.push_back(new TexRect("images/wall/wall.png", x, y, blockWidth, blockHeight));     //White walls
                            break;
                        }
                case 5: {   // Poison
                            obstacle.push_back(new TexRect("images/poison/0.png", x, y, blockWidth, blockHeight));
                            break;
                        }
                case 6: {
                            // Cheese!
                            num_Cheese++;
                            total_possible++;
                            eaten.push_back(false);
                            cheeses.push_back(new TexRect("images/cheese/0.png", x, y, blockWidth, blockHeight));
                        }
                default:
                    cout <<"Error " << temp << endl;
                    break;
            }
        }
    }
    lose = new TexRect("images/gameoverscreen/gameoverscreen.png", -2, 1, 4, 2);
}

void App::nextLevel() {
    current_level++;
    if(current_level > levels) {
        // TODO
    } else {
        // Clear out all the vectors used!
        map.clear();
        obstacle.clear();
        guards.clear();
        cheeses.clear();
        eaten.clear();

        // Reset the statistics for the level
        num_Cheese = 0;
        score = 0;

        createMap(current_level);
    }
}

void App::reset() {
    // Clear out all the vectors used!
    map.clear();
    obstacle.clear();
    guards.clear();
    cheeses.clear();
    eaten.clear();

    // Reset the statistics for the level
    num_Cheese = 0;
    score = 0;
    current_level = 1;
    total_score = 0;
    total_possible = 0;
    alive = true;

    createMap(current_level);
}

bool App::touchWalls(float mx, float my) {
    for(int i = 0; i < map.size(); i++) {
        // Checking all 4 corners:
        if( map[i]->contains(mx+speed, my) ||
            map[i]->contains(mx+mouse->getW(), my) ||
            map[i]->contains(mx+mouse->getW(), my-mouse->getH()+speed ) ||
            map[i]->contains(mx+speed, my-mouse->getH()) ) {
            return true;
        }
    }
    return false;
}

bool App::touchCheese(float mx, float my) {
    for(int i = 0; i < cheeses.size(); i++) {
        if( cheeses[i]->contains(mx+speed, my) ||
            cheeses[i]->contains(mx+mouse->getW(), my) ||
            cheeses[i]->contains(mx+mouse->getW(), my-mouse->getH()+speed ) ||
            cheeses[i]->contains(mx+speed, my-mouse->getH()) ) {
            if(!eaten.at(i)) {
                eaten.at(i) = true;
                score++;
                total_score++;
                return true;
            }
        }
    }
    return false;
}

bool App::withinBounds(float mx, float my) {
    return (mx >= -mapHalfWidth && mx+mouse->getW() <= mapHalfWidth && my-mouse->getH()+speed >= -mapHalfHeight && my <= mapHalfHeight);
}

void App::draw() {
    // Scoreboard
    string temp = "Level " + to_string(current_level) + "/" + to_string(levels) + " Score " + to_string(score) + "/" + to_string(num_Cheese);
    DisplayScore = new TextBox(temp.c_str(), -2.0, -0.9, GLUT_BITMAP_HELVETICA_18, 1.0, 1.0, 1.0, 500);
    DisplayScore->draw();
    if(alive) {
        mouse->draw(dir);
        mushroom->draw(0.1);
        // Drawing the map itself and obstacles
        for(int i = 0; i < map.size(); i++) {
            map[i]->draw(-0.1f);
        }
        for(int i = 0; i < guards.size(); i++) {
            guards[i]->draw(guards[i]->getDir());
        }
        for(int i = 0; i < obstacle.size(); i++) {
            obstacle[i]->draw(-0.5f);
        }
        for(int i = 0; i < cheeses.size(); i++) {
            if(!eaten.at(i)) {
                cheeses.at(i)->draw(-0.5f);
            }
        }
    } else {
        death->draw(1.0);
        lose->draw(1.0);
    }
}

void App::keyUp(unsigned char key, float x, float y) {
    if(key == 'w') {
        up = false;
        mouse->setMoving(false);
    }
    if(key == 'a') {
        left = false;
        mouse->setMoving(false);
    }
    if(key == 's') {
        down = false;
        mouse->setMoving(false);
    }
    if(key == 'd') {
        right = false;
        mouse->setMoving(false);
    }
    if(key == 'r' && !alive) {
        reset();
    }
}

void App::keyDown(unsigned char key, float x, float y) {
    if (key == 27){ // ESC key
        exit(0);
    }
    if(key == 'w') {
        dir = 1;
        up = true;
        mouse->setMoving(true);
    }
    if(key == 'a') {
        dir = 0;
        left = true;
        mouse->setMoving(true);
    }
    if(key == 's') {
        dir = 3;
        down = true;
        mouse->setMoving(true);
    }
    if(key == 'd') {
        dir = 2;
        right = true;
        mouse->setMoving(true);
    }
    if(key == ' '){
      start = false;
    }
}

void App::specialKeyUp(int key, float x, float y) {
    if(key == 101) {
        up = false;
        mouse->setMoving(false);
    }
    if(key == 100) {
        left = false;
        mouse->setMoving(false);
    }
    if(key == 103) {
        down = false;
        mouse->setMoving(false);
    }
    if(key == 102) {
        right = false;
        mouse->setMoving(false);
    }
}

void App::specialKeyDown(int key, float x, float y) {
    if(key == 101) {
        dir = 1;
        up = true;
        mouse->setMoving(true);
    }
    if(key == 100) {
        dir = 0;
        left = true;
        mouse->setMoving(true);
    }
    if(key == 103) {
        dir = 3;
        down = true;
        mouse->setMoving(true);
    }
    if(key == 102) {
        dir = 2;
        right = true;
        mouse->setMoving(true);
    }
}

App::~App(){
    // Clearing all objects used!
    delete mushroom;
    delete lose;
    delete DisplayScore;
    delete mouse;
    delete death;

    //Clearing all the vectors used!
    map.clear();
    obstacle.clear();
    guards.clear();
    cheeses.clear();
    eaten.clear();

    std::cout << "Exiting..." << std::endl;
}
