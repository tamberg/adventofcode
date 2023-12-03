#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://adventofcode.com/2023/day/1

// $ ./solve < test.txt
// ?

// $ ./solve < input.txt
// ?

#define INIT 0
#define O 1
#define ON 2
//#define ONE 3
#define T 4
#define TW 5
//#define TWO 6
#define TH 7
#define THR 8
#define THRE 9
//#define THREE 10
#define F 11
#define FO 12
#define FOU 13
//#define FOUR 14
#define FI 15
#define FIV 16
//#define FIVE 17
#define S 18
#define SI 19
//#define SIX 20
#define SE 21
#define SEV 22
#define SEVE 23
//#define SEVEN 24
#define E 25
#define EI 26
#define EIG 27
#define EIGH 28
//#define EIGHT 29
#define N 30
#define NI 31
#define NIN 32
//#define NINE 33

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
    int sum = 0;
    char ch = read_char();
    while (ch != 0) {
        int n = -1;
        int a = -1;
        int state = INIT;
        while (ch != '\n') {
            if (('0' <= ch) && (ch <= '9')) {
                n = ch - '0';
            } else if (('a' <= ch) && (ch <= 'z')) {
                if (state == INIT) {
                    if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } // else { state = INIT; }
                } else if (state == E) {
                    if (ch == 'i') { state = EI;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == EI) {
                    if (ch == 'g') { state = EIG;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == EIG) {
                    if (ch == 'h') { state = EIGH;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == EIGH) {
                    if (ch == 't') { n = 8; state = T;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else { state = INIT; }
                } else if (state == F) {
                    if (ch == 'o') { state = FO;
                    } else if (ch == 'i') { state = FI;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == FO) {
                    if (ch == 'u') { state = FOU;
                    } else if (ch == 'n') { state = ON;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == FOU) {
                    if (ch == 'r') { n = 4; state = INIT;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == FI) {
                    if (ch == 'v') { state = FIV;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == FIV) {
                    if (ch == 'e') { n = 5; state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == N) {
                    if (ch == 'i') { state = NI;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == NI) {
                    if (ch == 'n') { state = NIN;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == NIN) {
                    if (ch == 'e') { n = 9; state = E;
                    } else if (ch == 'i') { state = NI;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == O) {
                    if (ch == 'n') { state = ON;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == ON) {
                    if (ch == 'e') { n = 1; state = E;
                    } else if (ch == 'i') { state = NI;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == S) {
                    if (ch == 'e') { state = SE;
                    } else if (ch == 'i') { state = SI;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == SE) {
                    if (ch == 'v') { state = SEV;
                    } else if (ch == 'i') { state = EI;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == SEV) {
                    if (ch == 'e') { state = SEVE;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == SEVE) {
                    if (ch == 'n') { n = 7; state = N;
                    } else if (ch == 'i') { state = EI;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == SI) {
                    if (ch == 'x') { n = 6; state = INIT;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == T) {
                    if (ch == 'h') { state = TH;
                    } else if (ch == 'w') { state = TW;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == TH) {
                    if (ch == 'r') { state = THR;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == THR) {
                    if (ch == 'e') { state = THRE;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == THRE) {
                    if (ch == 'e') { n = 3; state = E;
                    } else if (ch == 'i') { state = EI;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 'o') { state = O;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                } else if (state == TW) {
                    if (ch == 'o') { n = 2; state = O;
                    } else if (ch == 'e') { state = E;
                    } else if (ch == 'f') { state = F;
                    } else if (ch == 'n') { state = N;
                    } else if (ch == 's') { state = S;
                    } else if (ch == 't') { state = T;
                    } else { state = INIT; }
                }
            }
            if ((a == -1) && (n != -1)) {
                a = 10 * n;
            }
            ch = read_char();
        }
        printf("%d\n", a + n);
        sum += a;
        sum += n;
        ch = read_char();
    }
    printf("%d\n", sum);
}
