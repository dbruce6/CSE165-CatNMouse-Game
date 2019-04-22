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

Mouse::Mouse(float x, float y, float z, float w, float h, float r, float g, float b): z(z) {
    for(int i = 0; i < 4; i++) {
        string filename = "images/mouse/" + to_string(i) + ".png";
        cout << "filename:\t" << filename << endl;
        animation.push_back(new AnimatedRect(filename.c_str(), 2, 2, 100, true, true, x, y, w, h));
        animation[i]->setR(r);
        animation[i]->setG(g);
        animation[i]->setB(b);
    }
}

Mouse::Mouse(float x, float y, float w, float h): z(0.5f) {
    for(int i = 0; i < 4; i++) {
        string filename = "sprites/" + to_string(i) + ".png";
        cout << "filename:\t" << filename << endl;
        animation.push_back(new AnimatedRect(filename.c_str(), 2, 2, 100, true, true, x, y, w, h));
        animation[i]->setR(1.0f);
        animation[i]->setG(1.0f);
        animation[i]->setB(1.0f);
    }
}

Mouse::~Mouse() {
    for(int i = 0; i < animation.size(); i++) {
        delete animation[i];
    }
}

float Mouse::getX() const {
    return animation[0]->getX();
}

float Mouse::getY() const {
    return animation[0]->getY();
}

float Mouse::getZ() const {
    return z;
}

float Mouse::getW() const {
    return animation[0]->getW();
}

float Mouse::getH() const {
    return animation[0]->getH();
}

float Mouse::getR() const {
    return animation[0]->getR();
}

float Mouse::getG() const {
    return animation[0]->getG();
}

float Mouse::getB() const {
    return animation[0]->getB();
}

void Mouse::setX(float x) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setX(x);
    }
}

void Mouse::setY(float y) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setY(y);
    }
}

void Mouse::setZ(float z) {
    this->z = z;
}

void Mouse::setW(float w) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setW(w);
    }
}

void Mouse::setH(float h) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setH(h);
    }
}

void Mouse::setR(float r) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setR(r);
    }
}

void Mouse::setG(float g) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setG(g);
    }
}

void Mouse::setB(float b) {
    for(int i = 0; i < animation.size(); i++) {
        animation[i]->setB(b);
    }
}

bool Mouse::contains(float px, float py) const {
    return animation[0]->contains(px, py);
}

void Mouse::draw(int dir) {
    animation[dir]->draw(z);
}

// void Mouse::draw(Direction dir) {
//     animation[translate(dir)]->draw(z);
// }

// int Mouse::translate(Direction dir) {
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

void Mouse::redrawScene(){
    glutPostRedisplay();
}