#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// https://adventofcode.com/2022/day/7

// $ cd / => cd = root;
// $ ls => skip
// dir a => mkdir(cd, "a")
// 14848514 b.txt => creat(cd, 14848514, "b.txt")
// 8504156 c.dat => creat(cd, 14848514, "b.txt")
// dir d => mkdir(cd, "d")
// $ cd a => cd = find(cd, "a")
// $ ls => skip
// dir e => mkdir(cd, "e")
// 29116 f => creat(cd, 29116, "f")
// 2557 g => creat(cd, 2557, "g")
// 62596 h.lst => creat(cd, 62596, "h.lst")
// $ cd e => cd = find(cd, "e")
// $ ls => skip
// 584 i => creat(cd, 584, "i")
// $ cd .. => cd = find(cd, "..") 
// $ cd .. => cd = find(cd, "..")
// $ cd d => cd = find(cd, "d")
// $ ls => skip
// 4060174 j => creat(cd, 4060174, "j")
// 8033020 d.log => creat(cd, 8033020, "d.log")
// 5626152 d.ext => creat(cd, 5626152, "d.ext")
// 7214296 k => creat(cd, 7214296, "k")

//- / (dir)
//  - a (dir)
//    - e (dir)
//      - i (file, size=584)
//    - f (file, size=29116)
//    - g (file, size=2557)
//    - h.lst (file, size=62596)
//  - b.txt (file, size=14848514)
//  - c.dat (file, size=8504156)
//  - d (dir)
//    - j (file, size=4060174)
//    - d.log (file, size=8033020)
//    - d.ext (file, size=5626152)
//    - k (file, size=7214296)

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
    struct node *up;
    struct node *nodes[N];
};

struct node *root;

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
    printf("find(%s, %s)\n", dir->name, name);
    assert(dir != NULL);
    // TODO: handle '/' and '..'
    struct node *n;
    int found = 0;
    int i = 0;
    while (!found && i < N) {
        n = dir->nodes[i];
        found = n != NULL && strcmp(n->name, name);
        i++;
    }
    if (!found) {
        n = NULL;
    }
    return n;
}

void insert(struct node *dir, char type, char *name, int size) {
    if (find(dir, name) == NULL) {
        struct node *n = malloc(sizeof(struct node));
        n->type = type;
        n->imax = 0;
        n->size = size;
        strcpy(n->name, name);
        assert(dir->imax < N);
        dir->nodes[dir->imax] = n;
        dir->imax++;
    }
}

void mkdir(struct node *dir, char *name) {
    printf("mkdir(%s, %s)\n", dir->name, name);
    insert(dir, 'd', name, 0);
}

void creat(struct node *dir, char *name, int size) {
    printf("creat(%s, %s, %d)\n", dir->name, name, size);
    insert(dir, 'f', name, size);
}

int main() {
    printf("main()\n");
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
                ch = read_value(&size);
                assert(ch == ' ');
                char name[N];
                ch = read_name(name, N);
                creat(cd, name, size);
            }
            assert(ch == '\n' || ch == 0);
        }
    }   
}
