#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H
#include "lib/string-util/string-util.h"
#include "lib/array-util/array-clear.h"
#include "syscall-interface.h"
#include "lib/map-util/map.h"

int Shell_Construct(char *DataSegmentAddress);
int Shell_MainLoop();

#endif // SHELL_SHELL_H
