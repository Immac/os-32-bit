#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H
#include "lib/string-util/string-util.h"
#include "lib/array-util/array-clear.h"
#include "syscall-interface.h"
#include "lib/map-util/map.h"

/**
*   This is the constructor for the Shell, should only be called once.
*   \param dataSegmentAddress This parameter is used to offset anything in the .data
*   that does not get offset because of how the program is loaded into memory
*/
int Shell_Construct(char *DataSegmentAddress);
int Shell_MainLoop();

#endif // SHELL_SHELL_H
