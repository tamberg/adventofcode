#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>

// https://adventofcode.com/2023/day/5

// $ ./solve < test.txt
// 35

// $ ./solve < input.txt
// ?

struct seed {
    int val;
    struct seed *next;
};

struct range {
    int src;
    int dst;
    int len;
    struct range *next;
};

struct table {
    char name[32];
    struct range *ranges;
    struct table *next;
};

struct input {
    struct seed *seeds;
    struct table *tables;
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

char read_value2(int *value, char ch) {
    int num = 0;
    while ('0' <= ch && ch <= '9') {
        int d = ch - '0'; // ASCII
        num = (num * 10) + d;
        ch = read_char();
    }
    *value = num;
    return ch;
}

char read_value(int *value) {
    char ch = read_char();
    return read_value2(value, ch);
}

char read_string(char *s) {
    int i = 0;
    char ch = read_char();
    while (ch != ':') {
        s[i] = ch;
        i++;
        ch = read_char();
    }
    s[i] = '\0';
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

void append_table(struct input *i, struct table *x) {
    assert(x->next == NULL);
    if (i->tables == NULL) {
        i->tables = x;
    } else {
        struct table *t = i->tables;
        struct table *u = NULL;
        while (t != NULL) {
            u = t;
            t = t->next;
        }
        u->next = x;
    }
}

int lookup(struct table *t, int i) {
    struct range *r = t->ranges;
    while (r != NULL && (i < r->src || (r->src + r->len) <= i)) {
        r = r->next;
    }
    int result;
    if (r != NULL) {
        result = i + (r->dst - r->src);
    } else {
        result = i;
    }
    return result;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int eval(struct input *i) {
    int result = INT_MAX;
    struct seed *s = i->seeds;
    while (s != NULL) {
        struct table *t = i->tables;
        int val = s->val;
        while (t != NULL) {
            //printf("%d => ", val);
            val = lookup(t, val);
            t = t->next;
        }
        //printf("%d\n", val);
        result = min(result, val);
        s = s->next;
    }
    return result;
}

int main() {
    struct input *i = malloc(sizeof(struct input));
    i->seeds = NULL;
    char ch = skip_string("seeds:");
    assert(ch == ' ');
    while (ch != '\n') {
        struct seed *s = malloc(sizeof(struct seed));
        ch = read_value(&s->val);
        assert(ch == ' ' || ch == '\n');
        s->next = i->seeds;
        i->seeds = s;
    }
    i->tables = NULL;
    while (ch != 0) {
        struct table *t = malloc(sizeof(struct table));
        ch = read_string(t->name);
        //printf("%s\n", t->name);
        assert(ch == ':');
        ch = read_char();
        assert(ch == '\n');
        ch = read_char();
        while (ch != '\n' && ch != 0) {
            struct range *r = malloc(sizeof(struct range));
            ch = read_value2(&r->dst, ch);
            assert(ch == ' ');
            ch = read_value(&r->src);
            assert(ch == ' ');
            ch = read_value(&r->len);
            assert(ch == '\n');
            ch = read_char();
            //printf("dst = %d, src = %d, len = %d\n", r->dst, r->src, r->len);
            r->next = t->ranges;
            t->ranges = r;
        }
        append_table(i, t);
    }
    int result = eval(i);
    //printf("%d\n", result);
}
