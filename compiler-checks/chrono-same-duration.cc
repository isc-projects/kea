#include <chrono>
#include <type_traits>

int main() {
    static_assert(std::is_same<std::chrono::system_clock::duration,
                               std::chrono::steady_clock::duration>::value,
                  "");
}
