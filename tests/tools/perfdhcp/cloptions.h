/*
#ifdef __cplusplus
extern "C" {
#endif 
*/

#include <stdint.h>

extern int v6;
extern int initialOnly;
extern const char *localName;
extern unsigned rate;
extern unsigned numRequest;
extern const char *server;
extern const char *diagSelector;

int procArgs(int argc, char **argv);

// Functions tested in cloptions unit test
int parse(int argc, char** argv);
const char* getAddress();
uint16_t getPort();
uint32_t getTimeout();
const char* getQname();

// Also need definitions of these values

namespace OptionInfo {
    const uint32_t QR = 0x0001;
    const uint32_t OP = 0x0002;
    const uint32_t AA = 0x0004;
    const uint32_t TC = 0x0008;
    const uint32_t Z  = 0x0010;
    const uint32_t AD = 0x0020;
    const uint32_t CD = 0x0040;
    const uint32_t RC = 0x0080;
    const uint32_t QC = 0x0100;
    const uint32_t AC = 0x0200;
    const uint32_t UC = 0x0400;
    const uint32_t DC = 0x0800;
    const uint32_t MS = 0x1000;
};


/*
#ifdef __cplusplus
}
#endif
*/
