#include <chrono>
#include <type_traits>

int main() {
    return(std::is_same<std::chrono::system_clock::duration,
                        std::chrono::steady_clock::duration>::value ? 0 : 1);
}
