#include <stdio.h>

unsigned long fakultet(int tall) {
    if (tall < 2) return 1;
    return tall * fakultet(tall-1);
}

int main() {
    for (int tall = 0; tall < 10; ++tall)
        printf("%d!: %lu\n", tall, fakultet(tall));
}