
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// https://adventofcode.com/2022/day/3

// $ ./solve2 < test.txt
// 70

// $ ./solve2 < input.txt
// 2881

int items_count[3][2 * 26]; // a - z, A - Z

int char_to_index(char ch) {
    int i;
    if ('a' <= ch && ch <= 'z') {
        i = ch - 'a';
    } else {
        assert('A' <= ch && ch <= 'Z');
        i = ch - 'A' + 26;
    }
    return i;
}

char index_to_char(int i) {
    assert(0 <= i && i < 2 * 26);
    return i < 26 ? 'a' + i : 'A' + i - 26;
}

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
    int total = 0;
    char ch = read_char();
    while (ch != 0) {
        int n = 0;
        while (n < 3) {
            for (int i = 0; i < 2 * 26; i++) {
                items_count[n][i] = 0;
            }
            while (ch != '\n') {
                int i = char_to_index(ch);
                items_count[n][i]++;
                ch = read_char();
            }
            ch = read_char();
            n++;
        }
        int found = 0;
        for (int i = 0; !found && i < 2 * 26; i++) {
            if (items_count[0][i] > 0 &&
                items_count[1][i] > 0 &&
                items_count[2][i] > 0)
            {
                int prio = i + 1;
                total += prio;
                found = 1;
                printf("%d (%c)\n", prio, index_to_char(i));
            }
        }
        assert(found);
    }
    printf("%d\n", total);
}
