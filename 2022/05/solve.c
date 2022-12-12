#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/5

// $ ./solve < test.txt
// ?

// $ ./solve < input.txt
// ?

struct crate { char type; struct crate *next; };
struct stack { struct crate *top; struct stack *next; };

struct stack *stacks;

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

void skip_chars(int n) {
    while (n > 0) {
        char ch = read_char();
        assert(ch != 0);
        n--;
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

void stack_create(int j) {
    // sorry :)
    struct stack *s = malloc(sizeof(struct stack));
    s->top = NULL;
    s->next = NULL;
    if (stacks == NULL) {
        assert(j == 0);
        stacks = s;
    } else {
        struct stack *p = stacks;
        while(p->next != NULL) {
            p = p->next;
            j--;
        }
        assert(j == 1);
        p->next = s;
    }
}

struct stack *stack_get(int j) {
    struct stack *s = stacks;
    while (j > 0) {
        assert(s != NULL);
        s = s->next;
        j--;
    }
    return s;
}

void stack_append_crate(int j, char type) {
    struct stack *s = stack_get(j);
    struct crate *c = malloc(sizeof(struct crate));
    c->type = type;
    c->next = NULL;
    if (s->top == NULL) {
        s->top = c;
    } else {
        struct crate *p = s->top;
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = c;
    }
}

void stack_print() {
    int i = 0;
    struct stack *s = stacks;
    while(s != NULL) {
        printf("%d: ", i + 1);
        struct crate *c = s->top;
        while (c != NULL) {
            printf("[%c]->", c->type);
            c = c->next;
        }
        printf("NULL\n");
        s = s->next;
        i++;
    }
}

void stack_print_top() {
    struct stack *s = stacks;
    while(s != NULL) {
        assert(s->top != NULL);
        printf("%c", s->top->type);
        s = s->next;
    }
    printf("\n");
}

void stack_move_crate(int from, int to) {
    assert(from != to);
    struct stack *fs = stack_get(from);
    struct stack *ts = stack_get(to);
    assert(fs->top != NULL);
    struct crate *p = fs->top;
    struct crate *c = fs->top->next;
    p->next = ts->top;
    ts->top = fs->top;
    fs->top = c;   
}

void stack_move_crates(int n, int from, int to) {
    while (n > 0) {
        stack_move_crate(from, to);
        n--;
    }
}

int main() {
    char ch = read_char();
    while (ch != 0) {
        int j = 0;
        while (ch != '\n') {
            if (stack_get(j) == NULL) {
                stack_create(j);
            }
            if (ch == '[') {
                ch = read_char();
                stack_append_crate(j, ch);
                ch = read_char();
                assert(ch == ']');
                ch = read_char();
                assert(ch == ' ' || ch == '\n');
                if (ch == ' ') {
                    ch = read_char();
                }
            } else if (ch == ' ') { // empty or index
                skip_chars(2);
                ch = read_char();
                assert(ch == ' ' || ch == '\n');
                if (ch == ' ') {
                    ch = read_char();
                }
            } else if (ch == 'm') {
                int n, from, to;
                skip_chars(4); // "ove "
                ch = read_value(&n);
                skip_chars(5); // "from "
                ch = read_value(&from);
                skip_chars(3); // "to "
                ch = read_value(&to);
                stack_move_crates(n, from - 1, to - 1);
                stack_print();
                assert(ch == '\n');
            } else {
                assert(ch == '\n');
            }
            j++;
        }
        ch = read_char();
    }
    stack_print_top();
}
