#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
// #include <stdio.h>      /* printf, scanf, puts, NULL */
// #include <stdlib.h>     /* srand, rand */
// #include <time.h>       /* time */
#include "Mouse.h"

using namespace std;

Mouse::Mouse(float x, float y, float z, float w, float h): Animal("images/mouse/", x, y, z, w, h) {
    moving = true;
    for(int i = 0; i < 4; i++) {
        string filename = "images/mousestills/" + to_string(i) + ".png";
        notMoving.push_back(new TexRect(filename.c_str(), x, y, w, h));
    }
}

void Mouse::setX(float x) {
    Animal::setX(x);
    for(int i = 0; i < notMoving.size(); i++) {
        notMoving[i]->setX(x);
    }
}

void Mouse::setY(float y) {
    Animal::setY(y);
    for(int i = 0; i < notMoving.size(); i++) {
        notMoving[i]->setY(y);
    }
}

bool Mouse::getMoving() {
    return moving;
}

void Mouse::setMoving(bool move) {
    moving = move;
}

void Mouse::draw(int dir) {
    if(moving) {
        Animal::draw(dir);
    } else {
        notMoving[dir]->draw(getZ());
    }
}