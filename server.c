#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define ADDRESS     "socketFile"  /* addr to connect */


int main()
{
    char c;
    FILE *filePointer;
    int fromlen;
    int i, s, ns, len;
    struct sockaddr_un saun, fsaun;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("server: socket");
        exit(1);
    }

    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);

    unlink(ADDRESS);
    len = sizeof(saun.sun_family) + strlen(saun.sun_path);

    if (bind(s, &saun, len) < 0) {
        perror("server: bind");
        exit(1);
    }

    while(1){

	if (listen(s, 5) < 0) {			// 5-> # of connections
		perror("server: listen");
		exit(1);
	}

	if ((ns = accept(s, &fsaun, &fromlen)) < 0) {
		perror("server: accept");
		exit(1);
	}

	filePointer = fdopen(ns, "r");


        while ((c = fgetc(filePointer)) != EOF) {
            putchar(c);

            if (c == '\n')
                break;
        }
    }

    close(s);

    exit(0);
}
