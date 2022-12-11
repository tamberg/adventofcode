#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

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

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    char ch = read_char();
    while (ch != 0) {
        int pos = 0;
        for (int i = 0; i < 2 * 26; i++) {
            items_min_pos[i] = INT_MAX;
            items_max_pos[i] = -1;
        }
        while (ch != '\n') {
            int i;
            if ('a' <= ch && ch <= 'z') {
                i = ch - 'a';
            } else {
                assert('A' <= ch && ch <= 'Z');
                i = ch - 'A' + 26;
            }
            assert(0 <= i && i < 2 * 26);
            items_min_pos[i] = min(pos, items_min_pos[i]);
            items_max_pos[i] = max(pos, items_max_pos[i]);
            ch = read_char();
            pos++;
        }
        for (int i = 0; i < 2 * 26; i++) {
            int cut = pos / 2;
            if (items_max_pos[i] != -1 &&
                items_min_pos[i] < cut &&
                items_max_pos[i] >= cut) {
                printf("%c\n", i < 26 ? 'a' + i : 'A' + i);
            }
        }
        ch = read_char();
    }
}
