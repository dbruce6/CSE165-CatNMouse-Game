#include <iostream>
//#include <vector>
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
        for(double offset = 0; offset <= 4.0; offset += 0.25) {
                backs.push_back(new TexRect("bg.png", -2 - offset, 1, 4, 2));
                backs.push_back(new TexRect("bg.png",  2 - offset, 1, 4, 2));
                //The -0.01 b/c there was a small gap in between the pictures w/o it.
        }
}

void App::draw() {
        if(counter >= backs.size()) counter = 0;
        //std::cout <<"Drawing" <<std::endl;
        /*for (int i = 0; i < back.size(); i++) {
                back[i]->draw(0.0);
        }  */ 
        //back[0]->draw(0.0);   //Segmentation fault error
        /*background = new TexRect("bg.png", -2 - offset, 1, 4, 2);
        background->draw(0.0);
        
        background2 = new TexRect("bg.png", 2 - offset - 0.01, 1, 4, 2);
        //The -0.01 b/c there was a small gap in between the pictures w/o it.
        background2->draw(0.0);*/
        
        backs[counter++]->draw(0.0);
        backs[counter++]->draw(0.0);
        
        kittie->draw(1.0);
        //kittie->playLoop();   //ERROR: frozen on last cat-animation
        //offset += 0.25;
        
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
}
