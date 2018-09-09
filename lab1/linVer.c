#include <stdio.h>
#include <fcntl.h>

void viewfile (int fd, ssize_t ret, char ch )
{
    while ((ret = read (fd, &ch, 1)) > 0)
    {
        putchar (ch);
    }
    close (fd);
}

int main ()
{
    int fd;
    ssize_t ret;
    char ch;

    printf("\n\n");
    fd = open ("/etc/release", O_RDONLY);
    viewfile(fd, ret, ch); 
    fd = open ("/etc/issue", O_RDONLY);
    printf("Название системы и версия ядра\n");
    viewfile(fd, ret, ch);   
    fd = open ("/etc/motd", O_RDONLY); 
    viewfile(fd, ret, ch);
    fd = open ("/etc/lsb-release", O_RDONLY);
    viewfile(fd, ret, ch);
}