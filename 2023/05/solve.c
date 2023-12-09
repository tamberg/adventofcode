#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>

// https://adventofcode.com/2023/day/5

// $ ./solve < test.txt
// 35

// $ ./solve < input.txt
// 389056265

struct seed {
    long val;
    struct seed *next;
};

struct range {
    long src;
    long dst;
    long len;
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

char read_value2(long *value, char ch) {
    long num = 0;
    while ('0' <= ch && ch <= '9') {
        long d = ch - '0'; // ASCII
        num = (num * 10) + d;
        ch = read_char();
    }
    *value = num;
    return ch;
}

char read_value(long *value) {
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

long lookup(struct table *t, long x) {
    struct range *r = t->ranges;
    while (r != NULL && (x < r->src || (r->src + r->len) <= x)) {
        r = r->next;
    }
    long result;
    if (r != NULL) {
        result = x + (r->dst - r->src);
    } else {
        result = x;
    }
    return result;
}

long min(long a, long b) {
    return a < b ? a : b;
}

long eval(struct input *i) {
    long result = LONG_MAX;
    struct seed *s = i->seeds;
    while (s != NULL) {
        struct table *t = i->tables;
        long val = s->val;
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
    //printf("seeds\n");
    assert(ch == ' ');
    while (ch != '\n') {
        struct seed *s = malloc(sizeof(struct seed));
        ch = read_value(&s->val);
        assert(ch == ' ' || ch == '\n');
        //printf("%ld\n", s->val);
        s->next = i->seeds;
        i->seeds = s;
    }
    ch = read_char();
    assert(ch == '\n');
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
            //printf("dst = %ld, src = %ld, len = %ld\n", r->dst, r->src, r->len);
            r->next = t->ranges;
            t->ranges = r;
        }
        append_table(i, t);
    }
    long result = eval(i);
    printf("%ld\n", result);
}
