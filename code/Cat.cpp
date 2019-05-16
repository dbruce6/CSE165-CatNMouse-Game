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
#include "Cat.h"

using namespace std;

Cat::Cat(float x, float y, float z, float w, float h): 
    Animal("images/cat/", x, y, z, w, h) {
        dir = 0;
    }

bool Cat::setDir(int direction) {
    if(direction >= 0 && direction <= 3) {
        dir = direction;
        return true;
    }
    return false;
}

bool Cat::TouchWalls(std::vector<TexRect*> map, std::vector<TexRect*>obstacle, float speed, float mx, float my) {
    // cout << "Checking if touching walls" << endl;
    for(int i = 0; i < map.size(); i++) {
        // cout << "Checking" << endl;
        // Checking all 4 corners:
        if( map[i]->contains(mx+speed, my) ||
            map[i]->contains(mx+getW(), my) ||
            map[i]->contains(mx+getW(), my-getH()+speed ) ||
            map[i]->contains(mx+speed, my-getH()) ) {
            return true;
        }
    }
    for(int i = 0; i < obstacle.size(); i++) {
        // Checking all 4 corners:
        if( obstacle[i]->contains(mx+speed, my) ||
            obstacle[i]->contains(mx+getW(), my) ||
            obstacle[i]->contains(mx+getW(), my-getH()+speed ) ||
            obstacle[i]->contains(mx+speed, my-getH()) ) {
            return true;
        }
    }
    return false;
}

Cat::~Cat() {
}

