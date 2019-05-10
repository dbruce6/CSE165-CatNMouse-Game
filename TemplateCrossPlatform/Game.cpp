#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	const char* shroomFileName;
	const char* fireballFileName;

	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	shroomFileName = "../mushroom.png";
	fireballFileName = "../fireball.bmp";
	#else
	shroomFileName = "mushroom.png";
	fireballFileName = "fireball.bmp";
	#endif

    mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    explosion = new AnimatedRect(fireballFileName, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);
    
    up = false;
    left = true;
    projectileVisible = true;
    mushroomVisible = true;
    theta = 0;
    deg = 0;
    hit = false;
    
    setRate(1);
    start();
}

void Game::action(){
    float mx = 0.5;
    float my = 0;
    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    
//    if (left)
//        mx -= 0.0005;
//    else
//        mx += 0.0005;
//
//    if (mx < -1.6f){
//        left = false;
//    }
//    if (mx > 1.6 - mushroom->getW()){
//        left = true;
//    }
    
    
    mushroom->setX(mx - mushroom->getW()/2);
    mushroom->setY(my + mushroom->getH()/2);
    
    theta += 0.001;
    deg += 0.1;
    

    if (!hit && up){
        float ypos = projectile->getY();
        ypos +=0.005;
        projectile->setY(ypos);

        if (mushroom->contains(0, ypos-0.005)){
            up = false;
            hit = true;
            projectileVisible = false;
            mushroomVisible = false;
            explosion->setX(mushroom->getX());
            explosion->setY(mushroom->getY());
            explosion->playOnce();
        }
    }
    
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
    }
}

void Game::draw() const {
    
    if (projectileVisible){
        projectile->draw();
    }
    if (mushroomVisible){
        mushroom->draw(0.0);
    }
    explosion->draw(0.1);
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    // if (key == ' '){
    //     up = true;
    // }
    if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
    else if(key == 'w') {
        // std::cout << "Going up!" << std::endl;
        up = true;
    }
    else if(key == 'a') {
        // std::cout << "Going left!" << std::endl;
        left = true;
    }
    else if(key == 's') {
        // std::cout << "Going down!" << std::endl;
        down = true;
    }
    else if(key == 'd') {
        // std::cout << "Going right!" << std::endl;
        right = true;
    }
}

void Game::handleKeyUp(unsigned char key, float x, float y){
    if(key == 'w') {
        // std::cout << "Going up!" << std::endl;
        up = false;
    }
    else if(key == 'a') {
        // std::cout << "Going left!" << std::endl;
        left = false;
    }
    else if(key == 's') {
        // std::cout << "Going down!" << std::endl;
        down = false;
    }
    else if(key == 'd') {
        // std::cout << "Going right!" << std::endl;
        right = false;
    }
}

void Game::specialKeyDown(int key, float x, float y){
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

void Game::specialKeyUp(int key, float x, float y){
    // std::cout <<"Special Down called" << std::endl;
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

Game::~Game(){
    stop();
    delete mushroom;
    delete explosion;
    delete projectile;
}
