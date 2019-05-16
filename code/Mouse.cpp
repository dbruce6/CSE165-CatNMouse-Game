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

Mouse::Mouse(float x, float y, float z, float w, float h, float r, float g, float b): Animal("images/mouse/", x, y, 1.0f, 0.1f, 0.1f) {
    for(int i = 0; i < 4; i++) {
        // TODO
    }
}