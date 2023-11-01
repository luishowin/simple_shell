#include <stdio.h>

int main() {
    char name[] = "Stewie"; 

    printf("Name: %s\n", name);
    printf("Memory address: %p\n", (void *)name);

    return 0;
}
