#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// https://adventofcode.com/2022/day/7

// $ ./solve < test.txt
// ?

// $ ./solve < input.txt
// ?

#define N 32

struct node {
    char type; // 'd'ir, 'f'ile
    char name[32];
    int imax;
    int size;
    int total;
    struct node *up;
    struct node *nodes[N];
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

char read_value2(char ch, int *value) {
    int num = 0;
    while ('0' <= ch && ch <= '9') {
        int d = ch - '0'; // ASCII
        num = (num * 10) + d;
        ch = read_char();
    }
    *value = num;
    return ch;
}

char read_name(char *name, int n) {
   int i = 0;
   char ch = read_char();
   while (i < (n - 1) && ch != 0 && ch != '\n' && ch != ' ') {
       name[i] = ch;
       ch = read_char();
       i++;
   }
   name[i] = '\0';
   return ch;
}

struct node *find(struct node *dir, char *name) { // TODO: add type?
    struct node *n;
    if (strcmp(name, "/") == 0) {
        while(dir->up != NULL) {
            dir = dir->up;
        }
        n = dir;
    } else if (strcmp(name, "..") == 0) {
        n = dir->up;
    } else {
        int found = 0;
        int i = 0;
        while (!found && i < N) {
            n = dir->nodes[i];
            found = n != NULL && (strcmp(n->name, name) == 0);
            i++;
        }
        if (!found) {
            n = NULL;
        }
    }
    return n;
}

struct node *create_root() {
    struct node *n = malloc(sizeof(struct node));
    n->type = 'd';
    n->size = 0;
    n->total = 0;
    n->imax = 0;
    n->up = NULL;
    memset(n->nodes, 0, sizeof(n->nodes));
    strcpy(n->name, "/");
    return n;
}

void insert(struct node *dir, char type, char *name, int size) {
    if (find(dir, name) == NULL) {
        struct node *n = malloc(sizeof(struct node));
        n->type = type;
        n->size = size;
        n->total = 0;
        n->imax = 0;
        n->up = dir;
        memset(n->nodes, 0, sizeof(n->nodes));
        strcpy(n->name, name);
        assert(dir->imax < N);
        dir->nodes[dir->imax] = n;
        dir->imax = dir->imax + 1;
        while (dir != NULL) {
            dir->total += size;
            dir = dir->up;
        }
    }
}

void mkdir(struct node *dir, char *name) {
    //printf("mkdir(%s, %s)\n", dir->name, name);
    insert(dir, 'd', name, 0);
}

void creat(struct node *dir, char *name, int size) {
    //printf("creat(%s, %s, %d)\n", dir->name, name, size);
    insert(dir, 'f', name, size);
}

void print_tree(struct node *n, int level) {
    if (n != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        if (n->type == 'd') {
            printf("- %s (dir, total=%d)\n", n->name, n->total);
        } else {
            assert(n->type == 'f');
            printf("- %s (file, size=%d)\n", n->name, n->size);
        }
        int i = 0;
        while (i < N && n->nodes[i] != NULL) {
            print_tree(n->nodes[i], level + 1);
            i++;
        }
    }
}

int main() {
    struct node *root = create_root();
    struct node *cd = root;
    char ch = read_char();
    while (ch != 0) {
        while (ch != '\n') {
            if (ch == '$') {
                ch = read_char();
                assert(ch == ' ');
                ch = read_char();
                if (ch == 'c') {
                    ch = read_char();
                    assert(ch == 'd');
                    ch = read_char();
                    assert(ch == ' ');
                    char name[N];
                    ch = read_name(name, N);
                    cd = find(cd, name);
                } else {
                    assert(ch == 'l');
                    ch = read_char();
                    assert(ch == 's');
                    ch = read_char();
                }
            } else if (ch == 'd') {
                ch = read_char();
                assert(ch == 'i');
                ch = read_char();
                assert(ch == 'r');
                ch = read_char();
                assert(ch == ' ');
                char name[N];
                ch = read_name(name, N);
                mkdir(cd, name);
            } else { // number
                int size;
                ch = read_value2(ch, &size);
                assert(ch == ' ');
                char name[N];
                ch = read_name(name, N);
                creat(cd, name, size);
            }
            assert(ch == '\n' || ch == 0);
        }
        if (ch != 0) {
            ch = read_char();
        }
    }
    print_tree(root, 0);
}
