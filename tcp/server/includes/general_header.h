#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#ifndef _GENERAL_HEADER_H    /* Guard against multiple inclusion */
#define _GENERAL_HEADER_H

extern pthread_t thread[10];
extern int iret[10];
extern int thread_counter;

#endif
