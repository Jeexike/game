#include "engine/Engine.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Engine engine("My Game 1.0", 60);
    engine.run();
    return 0;
}