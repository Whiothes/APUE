#include <shadow.h>
#include <stdio.h>

int main() {
    struct spwd *ptr;

    ptr = getspent();

    printf("password: %s\n", ptr->sp_pwdp);
}
