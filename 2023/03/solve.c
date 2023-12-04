#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2023/day/3

// $ ./solve < test.txt
// ?

// $ ./solve < input.txt
// ?

// 467..114..
// ...*......
// ..35..633.
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..

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
