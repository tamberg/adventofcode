#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

// https://adventofcode.com/2023/day/2

// $ ./solve < test.txt
// ?

// $ ./solve < input.txt
// ?

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green

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

char read_value(/* out */ int *value) {
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
    
    assert(ch == ',' || ch == ';' || ch == '\n');
    t->next = s->tuples;
    s->tuples = t;
    return ch;
}

char read_tuples(struct set *s) {
    i->tuples = NULL;
    char ch = read_tuple(s);
    while (ch == ',') {
        ch = read_tuple(s);
    }
    return ch;
}

char read_set(struct game *g) {
    struct set *s = malloc(sizeof(struct set));
    ch = read_tuples(s);
    assert(ch == ';' || ch == '\n');
    s->next = g->sets;
    g->sets = s;
    return ch;
}

char read_sets(struct game *g) {
    i->sets = NULL;
    char ch = read_set(g);
    while (ch == ';') {
        ch = read_set(g);
    }
    return ch;
}

char read_game(struct input *i) {
    struct game *g = malloc(sizeof(struct game));
    char ch = skip_string("Game");
    assert(ch == ' ');
    ch = read_value(&g->id);
    assert(ch == ':');
    ch = read_sets(g);
    assert(ch == '\n');
    g->next = i->games;
    i->games = g;
    return ch;
}

char read_games(struct input *i) {
    i->games = NULL;
    char ch = read_game(i);
    while (ch == '\n') {
        ch = read_game(i);
    }
    return ch;
}

void eval(struct input *i) {
    printf("input\n");
    struct game *g = i->games;
    while (g != NULL) {
        printf("\tgame %d\n", g->id);
        struct set *s = g->sets;
        while (s != NULL) {
            printf("\t\tset\n");
            struct tuple *t = s->tuples;
            while (t != NULL) {
                printf("\t\t\ttuple %d %c\n", t->count, t->color);
                t = t->next;
            }
            s = s->next;
        }
        g = g->next;
    }
}

int main() {
    struct input *i = malloc(sizeof(struct input));
    char ch = read_games(i);
    assert(ch == 0);
    eval(i);
}
