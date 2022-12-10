#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/1

// $ ./solve < test.txt
// 24000 (4th)

// $ ./solve < input.txt
// 69693 (10th)

// input = { items '\n' } items '\EOF'
// items = { value '\n' }
// value = digit { digit }
// digit = '0'..'9'

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

int read_items(int *sum) {
    char ch;
    int val;
    *sum = 0;
    do {
        ch = read_value(&val);
        *sum += val;
    } while (val != 0 && ch == '\n');
    return ch;
}

void read_input(int *max, int *pos) {
    char ch;
    int sum;
    int i = 0;
    *max = 0;
    *pos = 0;
    do {
        ch = read_items(&sum);
        if (*max < sum) {
            *max = sum;
            *pos = i;
        }
        i++;
    } while (ch == '\n');
    assert(ch == 0);
}

int main() {
    int max;
    int pos; // 0 = "1st"
    read_input(&max, &pos);
    char *th[4] = { "st", "nd", "rd", "th" };
    printf("%d (%d%s)\n", max, pos + 1, th[pos > 2 ? 3 : pos]);
    return 0;
}
