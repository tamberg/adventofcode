#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/3

// $ ./solve < test.txt
// 4361

// $ ./solve < input.txt
// 522726

// 0    pos
//      v
// 467..114.. <- prev
// ...*...... <- curr
// ..35..633. <- next
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..

// sliding window, bounding box, collision check

struct number {
    int pos;
    int len;
    int val;
    int is_part;
    struct number *next;
};

struct symbol {
    int pos;
    char ch;
    struct symbol *next;
};

struct line {
    struct number *numbers;
    struct symbol *symbols;
};

struct input {
    struct line *prev;
    struct line *curr;
    struct line *next;
};

void free_line(struct line *l) {
    printf("free_line()\n");
    if (l != NULL) {
        // TODO: free in reverse order
        struct number *n = l->numbers;
        while (n != NULL) {
            struct number *x = n;
            n = n->next;
            free(x);
        }
        struct symbol *s = l->symbols;
        while (s != NULL) {
            struct symbol *x = s;
            s = s->next;
            free(x);
        }
        free(l);
    }
}

void add_number(struct line *l, struct number *n) {
    printf("add_number(), pos = %d, val = %d, len = %d\n", n->pos, n->val, n->len);
    assert(l != NULL);
    assert(n != NULL);
    n->next = l->numbers;
    l->numbers = n;
}

void add_symbol(struct line *l, struct symbol *s) {
    printf("add_symbol(), pos = %d\n", s->pos);
    assert(l != NULL);
    assert(s != NULL);
    s->next = l->symbols;
    l->symbols = s;
}

void add_line(struct input *i, struct line *l) {
    printf("add_line()\n");
    assert(i != NULL);
    //assert(l != NULL);
    free_line(i->prev);
    i->prev = i->curr;
    i->curr = i->next;
    i->next = l;
}

int is_adjacent(struct number *n, struct symbol *s) {
    printf("is_adjacent()");
    // sssss
    //  nnn
    //  ^
    printf(" %d ? [%d, %d] ", s->pos, n->pos - 1, n->pos + n->len);
    int result =
        s->pos >= (n->pos - 1) &&
        s->pos <= (n->pos + n->len);
    printf("=> %d\n", result);
    return result;
}

int result = 0;

void update(struct input *i) {
    printf("update()\n");
    assert(i != NULL);
    if (i->curr != NULL) {
        struct number *n = i->curr->numbers;
        while (n != NULL) {
            // prev
            if (i->prev != NULL) {
                struct symbol *s = i->prev->symbols;
                while (s != NULL) {
                    n->is_part = n->is_part || is_adjacent(n, s);
                    s = s->next;
                }
            }
            // curr
            struct symbol *s = i->curr->symbols;
            while (s != NULL) {
                n->is_part = n->is_part || is_adjacent(n, s);
                s = s->next;
            }
            // next
            if (i->next != NULL) {
                struct symbol *s = i->next->symbols;
                while (s != NULL) {
                    n->is_part = n->is_part || is_adjacent(n, s);
                    s = s->next;
                }
            }
            if (n->is_part) {
                result += n->val;
                printf("=> result = %d\n", result);
            }
            n = n->next;
        }
    }
}

char read_char() {
    printf("read_char() => ");
    char buf[1];
    int r = read(STDIN_FILENO, buf, 1);
    if (r == 1) {
        printf("%c\n", buf[0]);
        return buf[0];
    } else if (r == 0) {
        printf("\n");
        return 0;
    } else {
        perror("read");
        exit(-1);
    }
}

int main(void) {
    printf("main()\n");
    struct input *i = malloc(sizeof(struct input));
    i->prev = NULL;
    i->curr = NULL;
    i->next = NULL;
    char ch = read_char();
    while (ch != 0) {
        struct line *l = malloc(sizeof(struct line));
        l->numbers = NULL;
        l->symbols = NULL;
        struct number *n = NULL;
        int pos = 0;
        while (ch != '\n') {
            if (ch >= '0' && ch <= '9') {
                if (n == NULL) {
                    n = malloc(sizeof(struct number));
                    n->pos = pos;
                    n->val = 0;
                    n->len = 0;
                    n->is_part = 0;
                }
                n->val = n->val * 10 + (ch - '0');
                n->len = n->len + 1;
            } else { // not a digit
                if (n != NULL) {
                    add_number(l, n);
                    n = NULL;
                }
                if (ch == '.') {
                    // skip
                } else { // symbol
                    struct symbol *s = malloc(sizeof(struct symbol));
                    s->pos = pos;
                    add_symbol(l, s);
                }
            }
            ch = read_char();
            pos++;
        }
        if (n != NULL) {
            add_number(l, n);
            n = NULL;
        }
        add_line(i, l);
        update(i);
        ch = read_char();
    }
    add_line(i, NULL); // flush
    update(i);
    printf("%d\n", result);
    return 0;
}
