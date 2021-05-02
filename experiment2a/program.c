#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

void main()
{
    int FILE_DESCRIPTOR;
    char BUFFER[50];
    char MESSAGE[50] = "This is the content of the file";
    char FILE_PATH[20] = "file.txt";
    FILE_DESCRIPTOR = open(FILE_PATH, O_RDWR);
    if (FILE_DESCRIPTOR != -1)
    {
        printf("%s opened with RDWR permission\n", FILE_PATH);
        write(FILE_DESCRIPTOR, MESSAGE, sizeof(MESSAGE));
        lseek(FILE_DESCRIPTOR, 0, SEEK_SET);
        read(FILE_DESCRIPTOR, BUFFER, sizeof(MESSAGE));
        printf("\nFile contains --\n {%s} \n-- END\n", BUFFER);
    }
    close(FILE_DESCRIPTOR);
}