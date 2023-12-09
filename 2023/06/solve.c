#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/6

// $ ./solve < test.txt
// ? (288)

// $ ./solve < input.txt
// ?

char read_char() {
    char buf[1];
    int r = read(STDIN_FILENO, buf, 1);
    if (r == 1) {
        return buf[0];
    } else if (r == 0) {
        return 0;
    } else {
        perror("read");
        exit(-1);
    }
}

int main() {
    char ch = read_char();
    while (ch != 0) {
        while (ch != '\n') {
            ch = read_char();
        }
        ch = read_char();
    }
    int result = 0;
    printf("%d\n", result);
}
