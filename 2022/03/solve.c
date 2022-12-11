#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/3

// $ ./solve vJrwpWtwJgWrhcsFMMfFFhFp => vJrwpWtwJgWr|hcsFMMfFFhFp => p
// $ ./solve jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL => jqHRNqRjqzjGDLGL|rsFMfFZSrLrFZsSL => L
// $ ./solve PmmdzqPrVvPwwTWBwg => PmmdzqPrV|vPwwTWBwg => P

// $ ./solve `cat input.txt`

int items[2 * 26][2 * 26]; // index: a - z, A - Z; elements: min, max position

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
            
        }
    }
}
