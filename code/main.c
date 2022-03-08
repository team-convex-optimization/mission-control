#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "tco_libd.h"

int log_level = LOG_INFO | LOG_DEBUG | LOG_ERROR;

int main(int argc, const char *argv[]) {

    if (log_init("mission_control", "./log.txt") != 0)
    {
        printf("Failed to initialize the logger\n");
        return EXIT_FAILURE;
    }



}