#ifndef MS2401_FUN_H
#define MS2401_FUN_H

#include "MS2401_param.h"
typedef struct {
    int buffer;  
    int busy;     
} Port;
extern Port LAN[MAX_HOSTS][2];

void connector();
void LAN_func();
void LLL();
void test_program();
void scheduler();

#endif

