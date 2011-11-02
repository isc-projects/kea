#ifdef __cplusplus
extern "C" {
#endif 

extern int v6;
extern int initialOnly;
extern const char *localName;
extern unsigned rate;
extern unsigned numRequest;
extern const char *server;
extern const char *diagSelector;

int procArgs(int argc, char **argv);

#ifdef __cplusplus
}
#endif
