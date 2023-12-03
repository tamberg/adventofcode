#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2023/day/1

// $ ./solve < test.txt
// 142

// $ ./solve < input.txt
// 55090

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
    int sum = 0;
    char ch = read_char();
    while (ch != 0) {
        int n;
        int a = -1;
        while (ch != '\n') {
            if (('0' <= ch) && (ch <= '9')) {
                n = ch - '0';
                if (a == -1) {
                    a = 10 * n;
                }
            }
            ch = read_char();
        }
        sum += a;
        sum += n;
        ch = read_char();
    }
    printf("%d\n", sum);
}
