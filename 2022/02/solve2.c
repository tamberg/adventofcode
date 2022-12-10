#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2022/day/2

// $ ./solve < test.txt
// 12

// $ ./solve < input.txt
// ?

// In the first round, your opponent will choose Rock (A), and you need the round to end in a draw (Y), so you also choose Rock. This gives you a score of 1 + 3 = 4.
// In the second round, your opponent will choose Paper (B), and you choose Rock so you lose (X) with a score of 1 + 0 = 1.
// In the third round, you will defeat your opponent's Scissors with Rock for a score of 1 + 6 = 7.
// total score of 12

int score[3][3] = {
    { 1 + 3, 2 + 6, 3 + 0 }, // AX, AY, AZ
    { 1 + 0, 2 + 3, 3 + 6 }, // BX, BY, BZ
    { 1 + 6, 2 + 0, 3 + 3 }  // CX, CY, CZ
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

int main() {
    int res = 0;
    char ch;
    do {
        char opp = read_char();
        char spc = read_char();
        char you = read_char();
        ch = read_char();
        if (ch == '\n') {
            int s = score[opp - 'A'][you - 'X'];
            printf("%c %c => %d\n", opp, you, s);
            res = res + s;
        }
    } while (ch == '\n');
    printf("%d\n", res);
}
