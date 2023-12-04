#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2023/day/3

// $ ./solve < test.txt
// ?

// $ ./solve < input.txt
// ?

// 0-------->
// 467..114.. 0
// ...*...... |
// ..35..633. v
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..

// sliding window, hx = ..\n, hy = 3
// bounding box, collision check

/*

struct num {
    int row;
    int col;
    int val;
    int len;
}

int engine[n_rows][n_cols];

int is_part(struct num *x) {
    return
        is_symbol(engine[x->row - 1][x->col - 1 .. x->col + x->len]) ||
        is_symbol(engine[x->row][x->col - 1]) ||
        is_symbol(engine[x->row][x->col + x->len]) ||
        is_symbol(engine[x->row + 1][x->col - 1 .. x->col + x->len]);
}

*/

struct number {
    int pos;
    int len;
    int val;
    int is_part;
}

struct symbol {
    int pos;
    char ch;
}

struct line {
    struct number *numbers;
    struct symbol *symbols;
}

struct input {
    struct line *prev;
    struct line *curr;
    struct line *next;
}

void add_line(struct input *i, struct line *l) {
    free_line(i->prev);
    i->prev = i->curr;
    i->curr = i->l;
}

int is_adjacent(struct number *n, struct symbol *s) {
    // sssss
    //  nnn
    //  ^
    int result =
        s->pos >= (n->pos - 1) &&
        s->pos <= (n->pos + n->len);
}

int check_curr(struct input *i) {
    assert(i != NULL);
    assert(i->curr != NULL);
    for (n in i->curr->numbers) {
        if (i->prev != NULL) {
            struct symbol *s = i->prev->symbols;
            while (s != NULL) {
                n->is_part = n->is_part || is_adjacent(n, s);
                s = s->next;
            }
        }
        struct symbol *s = i->curr->symbols;
        while (s != NULL) {
            n->is_part = n->is_part || is_adjacent(n, s);
            s = s->next;
        }
    }
}

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

int main() {
    char ch = read_char();
    while (ch != 0) {
        while (ch != '\n') {
            ch = read_char();
        }
        ch = read_char();
    }
    int result = 0;
    printf("%d\n", result);
}
