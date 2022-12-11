#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/4

// $ ./solve2 < test.txt
// 4

// $ ./solve2 < input.txt
// 881

char read_char() {
    char buf[1];
    int r = read(STDIN_FILENO, buf, 1);
    if (r == 1) {
        printf("%c", buf[0]);
        return buf[0];
    } else if (r == 0) {
        return 0;
    } else {
        perror("read");
        exit(-1);
    }
}

char read_value(int *value) {
    char ch = read_char();
    int num = 0;
    while ('0' <= ch && ch <= '9') {
        int d = ch - '0'; // ASCII
        num = (num * 10) + d;
        ch = read_char();
    }
    *value = num;
    return ch;
}

int main() {
    int count = 0;
    int values[4];
    char ch = read_value(&values[0]);
    while (ch != 0) {
        assert(ch == '-');
        ch = read_value(&values[1]);
        assert(ch == ',');
        ch = read_value(&values[2]);
        assert(ch == '-');
        ch = read_value(&values[3]);
        assert(ch == '\n' || ch == 0);
        if (values[0] <= values[3] && values[1] >= values[2] ||
            values[2] <= values[1] && values[3] >= values[0]) {
             printf("^\n");
             count++;
        }
        ch = read_value(&values[0]);
    }
    printf("%d\n", count);
}
