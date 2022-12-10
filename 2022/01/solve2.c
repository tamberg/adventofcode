#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/1

// $ ./solve2 < test.txt
// 45000

// $ ./solve2 < input.txt
// ?

// input = { items '\n' } items '\EOF'
// items = { value '\n' }
// value = digit { digit }
// digit = '0'..'9'

struct elve {
    int sum;
    struct elve *next;
};

struct elve *elves = NULL;

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

void insert_sorted(int sum) {
    struct elve *p = elves;
    struct elve *e = elves;
    while (e != NULL && e->sum > sum) {
        p = e;
        e = e->next;
    }
    assert(e == NULL || e->sum <= sum);
    struct elve *n = malloc(sizeof(struct elve));
    n->sum = sum;
    n->next = e;
    if (p != NULL && p != e) {
        p->next = n;
    } else {
        elves = n;
    }
}

void read_input() {
    char ch;
    int sum;
    do {
        ch = read_items(&sum);
        insert_sorted(sum);
    } while (ch == '\n');
    assert(ch == 0);
}

int main() {
//    int n = 3;
    read_input();
    struct elve *e = elves;
    while (e != NULL) {
        printf("%d\n", e->sum);
        e = e->next;
    }
//    char *th[4] = { "st", "nd", "rd", "th" };
//    printf("%d (%d%s, )\n", top[i], pos[i] + 1, th[pos[i] > 2 ? 3 : pos[i]]);
//    printf("=> %d\n", sum);
    return 0;
}
