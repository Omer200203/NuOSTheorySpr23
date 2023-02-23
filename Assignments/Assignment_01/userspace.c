#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
    long int i = syscall(335);
    printf("System call sys_hello returned %ld\n", i);
    return 0;
}
