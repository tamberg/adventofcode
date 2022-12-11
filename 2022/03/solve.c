#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/3

// vJrwpWtwJgWrhcsFMMfFFhFp => vJrwpWtwJgWr|hcsFMMfFFhFp => p
// jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL => jqHRNqRjqzjGDLGL|rsFMfFZSrLrFZsSL => L
// PmmdzqPrVvPwwTWBwg => PmmdzqPrV|vPwwTWBwg => P

int items[2 * 26]; // a - z, A - Z

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
       
}
