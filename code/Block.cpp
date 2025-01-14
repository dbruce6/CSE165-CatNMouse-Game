#include "Block.h"

Block::Block(float x, float y, float w, float h, float r, float g, float b): x(x), y(y), w(w), h(h), r(r), g(g), b(b){
                                                
}

Block::~Block(){
    
}

void Block::getCoord(float& _x, float& _y) {
    _x = x;
    _y = y;
}
    
void Block::getDimension(float& _w, float& _h) { 
    _w = w;
    _h = h;
}

void Block::getColor(float& _r, float& _g, float& _b) { 
    _r = r;
    _g = g;
    _b = b;
}

void Block::setCoord(float _x, float _y) {
    x = _x;
    y = _y;
}

void Block::setDimension(float _w, float _h) {
    w = _w;
    h = _h;
}

void Block::setColor(float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
}

void Block::draw() {
    std::cout << "(x, y) after: (" << x << ", " << y << ")" << std::endl;
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    
    //Clockwise
    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y-h);
    glVertex2f(x, y-h);
    
    glEnd();
}

bool Block::moveLeft() {
    if(x > -2) {
        x -= w;
        return true;
    }
    return false;
}

bool Block::moveUp() {
    if(y < 1) {
        y += h;
        return true;
    }
    return false;
} 

bool Block::moveRight() {
    if(x < 2-w) {
        x += w;
        return true;
    }
    return false;
}

bool Block::moveDown() {
    if(y > -1+h) {
        y -= h;
        return true;
    }
    return false;
}
