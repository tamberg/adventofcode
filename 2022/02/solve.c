#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// A for Rock, B for Paper, and C for Scissors
// X for Rock, Y for Paper, and Z for Scissors
// 1 for Rock, 2 for Paper, and 3 for Scissors
// 0 if you lost, 3 if the round was a draw, and 6 if you won

// A Y // 2 because you chose Paper + 6 because you won
// B X // a loss for you with a score of 1 (1 + 0)
// C Z // both players choosing Scissors, giving you a score of 3 + 3 = 6
// total score of 15 (8 + 1 + 6)

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
