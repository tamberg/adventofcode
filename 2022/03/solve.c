#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/3

// $ ./solve < test.txt
// vJrwpWtwJgWrhcsFMMfFFhFp => vJrwpWtwJgWr|hcsFMMfFFhFp => p => 16
// jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL => jqHRNqRjqzjGDLGL|rsFMfFZSrLrFZsSL => L => 38
// PmmdzqPrVvPwwTWBwg => PmmdzqPrV|vPwwTWBwg => P => 42
// ...
// 16 + 38 + 42 + ... => 157

// $ ./solve <= input.txt

int items_min_pos[2 * 26]; // a - z, A - Z
int items_max_pos[2 * 26];

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
        int pos = 0;
        while (ch != '\n') {
            int i = ch - 'a';
            items_min_pos[i] = pos < items_min_pos[i] ? pos : items_min_pos[i];
            items_max_pos[i] = pos > items_max_pos[i] ? pos : items_max_pos[i];
            pos++;
        }
        for (int j = 0; j < 2 * 26; j++) {
            int cut = pos / 2;
            if (items_min_pos[j] < cut &&
                items_max_pos[j] >= cut) {
                printf("%c\n", 'a' + j);
            }
        }
    }
}
