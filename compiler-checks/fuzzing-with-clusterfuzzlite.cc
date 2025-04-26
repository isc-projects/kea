#include <cstdlib>

int main() {
    if (getenv("CIFUZZ") && getenv("FUZZING_ENGINE") && getenv("FUZZING_LANGUAGE")) {
        return 0;
    } else {
        return 1;
    }
}
