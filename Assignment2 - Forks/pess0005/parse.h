void parseArguments(int argc, char *argv[], short *range, short *timeout);
char *getParam(char *argEntry, char separator);
void parseNumericParam(short *dest, char *argEntry, char *strCommand,
                       char separator);
char getGNUFirstChar(char *gnu);
void parseGNUCommand(char **gnu);
void printHelpAndExit(char *strCommand, int exitCode);
