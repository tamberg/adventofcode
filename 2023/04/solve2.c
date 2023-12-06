#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/4

// $ ./solve2 < test.txt
// ? (30)

// $ ./solve2 < input.txt
// ?

struct number {
    int val;
    struct number *prev;
    struct number *next;
};

struct card {
    int nof_instances;
    struct number *wins;
    struct number *mine;
    struct card *next;
};

struct input {
    struct card *cards;
};

char read_char() {
    char buf[1];
    int r = read(STDIN_FILENO, buf, 1);
    if (r == 1) {
        //printf("%c", buf[0]);
        return buf[0];
    } else if (r == 0) {
        //printf("\n");
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
        int d = ch - '0'; // ASCII
        num = (num * 10) + d;
        ch = read_char();
    }
    *value = num;
    return ch;
}

struct card *card_at(struct card *list, int i) {
    struct card *c = list;
    while (c != NULL && i != 0) {
        i--;
        c = c->next;
    }
    return c;
}

int eval2(struct input *i) {
    int result;
    struct card *c = i->cards;
    while(c != NULL) {
        int score = 0;
        struct number *m = c->mine;
        while (m != NULL) {
            struct number *n = c->wins;
            while (n != NULL) {
                if (m->val == n->val) {
                    //printf("%d ", m->val);
                    if (score == 0) {
                        score = 1;
                    } else {
                        score *= 2;
                    }
                }
                n = n->next;
            }
            m = m->next;
        }
        //printf("\n");
        result += score;
        c = c->next;
    }
    return result;
}

int main() {
    struct input *i = malloc(sizeof(struct input));
    char ch = read_char();
    while (ch != '\n' && ch != 0) {
        struct card *c = malloc(sizeof(struct card));
        c->wins = NULL;
        c->mine = NULL;
        while (ch != ':') {
            ch = read_char();
        }
        ch = read_char();
        assert(ch == ' ');
        while (ch != '|') {
            struct number *n = malloc(sizeof(struct number));
            ch = read_value(&n->val);
            n->next = c->wins;
            c->wins = n;
            assert(ch == ' ' || ch == '|');
        }
        while (ch != '\n' && ch != 0) {
            struct number *n = malloc(sizeof(struct number));
            ch = read_value(&n->val);
            n->next = c->mine;
            c->mine = n;
            assert(ch == ' ' || ch == '\n' || ch == 0);
        }
        c->next = i->cards;
        i->cards = c;
        ch = read_char();
    }
    int result = eval2(i);
    printf("%d\n", result);
}
