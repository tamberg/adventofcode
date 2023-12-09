#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/4

// $ ./solve2 < test.txt
// 30

// $ ./solve2 < input.txt
// 5921508

struct number {
    int val;
    struct number *next;
};

struct card {
    int id;
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

void append_card(struct input *i, struct card *x) {
    assert(x->next == NULL);
    if (i->cards == NULL) {
        i->cards = x;
    } else {
        struct card *c = i->cards;
        struct card *d = NULL;
        while (c != NULL) {
            d = c;
            c = c->next;
        }
        d->next = x;
    }
}

struct card *get_card(struct input *i, int id) {
    struct card *c = i->cards;
    while (c != NULL && c->id != id) {
        c = c->next;
    }
    return c;
}

int eval2(struct input *i) {
    int result;
    struct card *c = i->cards;
    while(c != NULL) {
        //printf("card %d\n", c->id);
        int offset = 1;
        int score = 0;
        struct number *m = c->mine;
        while (m != NULL) {
            struct number *n = c->wins;
            while (n != NULL) {
                if (m->val == n->val) {
                    struct card *x = get_card(i, c->id + offset);
                    x->nof_instances += c->nof_instances;
                    offset++;
                }
                n = n->next;
            }
            m = m->next;
        }
        result += c->nof_instances;
        c = c->next;
    }
    return result;
}

int main(void) {
    struct input *i = malloc(sizeof(struct input));
    char ch = read_char();
    while (ch != '\n' && ch != 0) {
        struct card *c = malloc(sizeof(struct card));
        c->nof_instances = 1;
        c->wins = NULL;
        c->mine = NULL;
        c->next = NULL;
        assert(ch == 'C');
        ch = skip_string("ard");
        ch = read_value(&c->id);
        assert(ch == ':');
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
        append_card(i, c);
        ch = read_char();
    }
    int result = eval2(i);
    printf("%d\n", result);
    return 0;
}
