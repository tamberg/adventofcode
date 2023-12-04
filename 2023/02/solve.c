#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/2

// $ ./solve < test.txt
// 8

// $ ./solve < input.txt
// 2256

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

// INPUT = GAME { GAME } EOF
// GAME = "Game" ID ':' SET { ';' SET } '\n'
// ID = NUMBER
// SET = TUPLE { ',' TUPLE }
// TUPLE = ' ' NUMBER ' ' COLOR
// NUMBER = DIGIT { DIGIT }
// COLOR = "red" | "green" | "blue"
// DIGIT = '0' - '9'

// only 12 red cubes, 13 green cubes, and 14 blue cubes?
// => count color per game
// => compare to get (im)possible

// add up the IDs of the games that would have been possible

struct tuple {
    int count;
    char color; // 'r', 'g', 'b'
    struct tuple *next;
};

struct set {
    struct tuple *tuples;
    struct set *next;
};

struct game {
    int id;
    struct set *sets;
    struct game *next;
};

struct input {
    struct game *games;
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

char read_tuple(struct set *s) {
    struct tuple *t = malloc(sizeof(struct tuple));
    char ch = read_char();
    assert(ch == ' ');
    ch = read_value(&t->count);
    assert(ch == ' ');
    ch = read_char();
    t->color = ch;
    if (ch == 'r') { ch = skip_string("ed");
    } else if (ch == 'g') { ch = skip_string("reen");
    } else { assert(ch == 'b'); ch = skip_string("lue"); }
    assert(ch == ',' || ch == ';' || ch == '\n');
    t->next = s->tuples;
    s->tuples = t;
    return ch;
}

char read_tuples(struct set *s) {
    s->tuples = NULL;
    char ch = read_tuple(s);
    while (ch == ',') {
        ch = read_tuple(s);
    }
    return ch;
}

char read_set(struct game *g) {
    struct set *s = malloc(sizeof(struct set));
    char ch = read_tuples(s);
    assert(ch == ';' || ch == '\n');
    s->next = g->sets;
    g->sets = s;
    return ch;
}

char read_sets(struct game *g) {
    g->sets = NULL;
    char ch = read_set(g);
    while (ch == ';') {
        ch = read_set(g);
    }
    return ch;
}

char read_game(struct input *i) {
    char ch = read_char();
    if (ch == 'G') {
        struct game *g = malloc(sizeof(struct game));
        ch = skip_string("ame");
        assert(ch == ' ');
        ch = read_value(&g->id);
        assert(ch == ':');
        ch = read_sets(g);
        assert(ch == '\n');
        g->next = i->games;
        i->games = g;
    } else {
        assert(ch == 0); // EOF
    }
    return ch;
}

char read_games(struct input *i) {
    i->games = NULL;
    char ch = read_game(i);
    while (ch == '\n') {
        ch = read_game(i);
    }
    assert(ch == 0); // EOF
    return ch;
}

int eval(struct input *i, int r_max, int g_max, int b_max) {
    printf("input\n");
    int result = 0;
    struct game *g = i->games;
    while (g != NULL) {
        printf("\tgame %d\n", g->id);
        //int r_count = 0;
        //int g_count = 0;
        //int b_count = 0;
        int possible = 1;
        struct set *s = g->sets;
        while (s != NULL) {
            printf("\t\tset\n");
            int r_count = 0;
            int b_count = 0;
            int g_count = 0;
            struct tuple *t = s->tuples;
            while (t != NULL) {
                printf("\t\t\ttuple %d %c\n", t->count, t->color);
                if (t->color == 'r') {
                    r_count += t->count;
                } else if (t->color == 'g') {
                    g_count += t->count;
                } else {
                    assert(t->color == 'b');
                    b_count += t->count;
                }
                t = t->next;
            }
            possible = possible && (r_count <= r_max && g_count <= g_max && b_count <= b_max);
            s = s->next;
        }
        //if (r_count <= r_max && g_count <= g_max && b_count <= b_max) {
        if (possible) {
            printf("\t=> possible\n");
            result += g->id;
        }
        g = g->next;
    }
    return result;
}

int main() {
    struct input *i = malloc(sizeof(struct input));
    char ch = read_games(i);
    assert(ch == 0);
    int r_max = 12;
    int g_max = 13;
    int b_max = 14;
    int result = eval(i, r_max, g_max, b_max);
    printf("%d\n", result);
}
