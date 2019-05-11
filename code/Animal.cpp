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
#include "Animal.h"

using namespace std;

Animal::Animal(string fileLoc,float x, float y, float z, float w, float h, float r, float g, float b): z(z) {
    for(int i = 0; i < 4; i++) {
        // string filename = "images/mouse/" + to_string(i) + ".png";
        string filename = fileLoc + to_string(i) + ".png";
        cout << "filename:\t" << filename << endl;
        animation.push_back(new AnimatedRect(filename.c_str(), 2, 2, 100, true, true, x, y, w, h));
        animation[i]->setR(r);
        animation[i]->setG(g);
        animation[i]->setB(b);
    }
}

Animal::Animal(string fileLoc, float x, float y, float w, float h): z(0.5f) {
    for(int i = 0; i < 4; i++) {
        // string filename = "sprites/" + to_string(i) + ".png";
        string filename = fileLoc + to_string(i) + ".png";
        cout << "filename:\t" << filename << endl;
        animation.push_back(new AnimatedRect(filename.c_str(), 2, 2, 100, true, true, x, y, w, h));
        animation[i]->setR(1.0f);
        animation[i]->setG(1.0f);
        animation[i]->setB(1.0f);
    }
}

Animal::~Animal() {
    for(int i = 0; i < animation.size(); i++) {
        delete animation[i];
    }
}

float Animal::getX() const {
    return animation[0]->getX();
}

float Animal::getY() const {
    return animation[0]->getY();
}

float Animal::getZ() const {
    return z;
}

float Animal::getW() const {
    return animation[0]->getW();
}

float Animal::getH() const {
    return animation[0]->getH();
}

float Animal::getR() const {
    return animation[0]->getR();
}

float Animal::getG() const {
    return animation[0]->getG();
}

float Animal::getB() const {
    return animation[0]->getB();
}

void Animal::setX(float x) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setX(x);
    }
}

void Animal::setY(float y) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setY(y);
    }
}

void Animal::setZ(float z) {
    this->z = z;
}

void Animal::setW(float w) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setW(w);
    }
}

void Animal::setH(float h) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setH(h);
    }
}

void Animal::setR(float r) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setR(r);
    }
}

void Animal::setG(float g) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setG(g);
    }
}

void Animal::setB(float b) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setB(b);
    }
}

bool Animal::contains(float px, float py) const {
    return animation[0]->contains(px, py);
}

void Animal::draw(int dir) {
    animation[dir]->draw(z);
}

// void Animal::draw(Direction dir) {
//     animation[translate(dir)]->draw(z);
// }

// int Animal::translate(Direction dir) {
//     switch (dir) {
//         case Left:
//             return 0;
//         case Up:
//             return 1;
//         case Right:
//             return 2;
//         case Down:
//             return 3;
//         default:
//             cout << "ERROR WRONG DIRECTION TYPE!" << endl;
//             return -1;
//     }
// }

void Animal::redrawScene(){
    glutPostRedisplay();
}