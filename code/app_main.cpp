#include "App.h"
using namespace std;

int main(int argc, char** argv) {

    GlutApp* app = new App(argc, argv, 1000, 500, "Cat N' Mouse");

    app->run();
}
