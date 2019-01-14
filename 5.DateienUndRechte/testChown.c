#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <error.h>

#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char **argv) {

    #ifdef _POSIX_CHOWN_RESTRICTED  // Wenn definiert darf nur root das machen
    #define TEST() getuid() == 0
    #else
    #define TEST() 1
    #endif
    if(TEST())
        {
            if( chown("testChown.c", 25, 25) == -1 ) {
                perror("chown");
            }  
            else {
                printf("alright");
            }
        }
    else {
        printf("You must be root mofo");
    }

    return EXIT_SUCCESS;
}

