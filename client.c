#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>

#define ADDRESS "socketFile"

int main(int argc, char *argv[])
{
    FILE *filePointer;
    char myArr[255] = {0};
    int s, len;
    struct sockaddr_un saun;		// 14+ karakter unix domain socket


    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {	// AF_UNIX: aynı makine processler arası
        perror("client: socket acilamadi");
        exit(1);
    }

    saun.sun_family = AF_UNIX;			// set address family
    strcpy(saun.sun_path, ADDRESS);		// set socket path

    len = sizeof(saun.sun_family) + strlen(saun.sun_path);

    if (connect(s, (const struct sockaddr*) &saun, len) < 0) {
        perror("client: baglanti saglanamadi");
        exit(1);
    }

    filePointer = fdopen(s, "r");

    snprintf(myArr, sizeof(myArr), "%s\n", argv[1]);
  
    printf("%s:%d %s\n", __FILE__, __LINE__, myArr); 

    send(s, (const void *) myArr, strlen(myArr), 0);

    // send(s, (const void *) str, strlen(str), 0);

    close(s);

    exit(0);
}
