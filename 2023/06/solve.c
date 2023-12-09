#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/6

// $ ./solve < test.txt
// ? (288)

// $ ./solve < input.txt
// ?

struct boat {
    int time;
    int dist;
    struct boat *next;
};

struct input {
    struct boat *boats;
};

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
    while (ch == ' ') {
        ch = read_char();
    }
    int num = 0;
    while ('0' <= ch && ch <= '9') {
        long d = ch - '0'; // ASCII
        num = (num * 10) + d;
        ch = read_char();
    }
    *value = num;
    return ch;
}

char skip_string(char *s) {
    assert(s != NULL);
    char ch = read_char();
    while (*s != '\0') {
        assert(ch == *s);
        ch = read_char();
        s++;
    }
    return ch;
}

void append_boat(struct input *i, struct boat *x) {
    assert(x->next == NULL);
    if (i->boats == NULL) {
        i->boats = x;
    } else {
        struct boat *b = i->boats;
        struct boat *c = NULL;
        while (b != NULL) {
            c = b;
            b = b->next;
        }
        c->next = x;
    }
}

int eval(struct input *i) {
    struct boat *b = i->boats;
    while (b != NULL) {
        printf("boat %d, %d\n", b->time, b->dist);
        b = b->next;
    }
}

int main(void) {
    struct input *i = malloc(sizeof(struct input));
    i->boats = NULL;
    char ch = skip_string("Time:");
    while (ch != '\n') {
        struct boat *b = malloc(sizeof(struct boat));
        ch = read_value(&b->time);
        append_boat(i, b);
    }
    ch = skip_string("Distance:");
    struct boat *b = i->boats;
    while (ch != '\n') {
        assert(b != NULL);
        ch = read_value(&b->dist);
        b = b->next;
    }
    int result = eval(i);
    printf("%d\n", result);
    return 0;
}
