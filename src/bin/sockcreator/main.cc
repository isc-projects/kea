#include "sockcreator.h"

using namespace isc::socket_creator;

int main() {
    /*
     * TODO Maybe use some OS-specific caps interface and drop everything
     * but ability to bind ports? It would be nice.
     */
    return run(0, 1); // Read commands from stdin, output to stdout
}
