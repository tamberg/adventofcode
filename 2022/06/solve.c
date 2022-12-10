#include <stdio.h>

// https://adventofcode.com/2022/day/6

// $ ./solve bvwbjplbgvbhsrlpgdmjqwftvncz => 5
// $ ./solve nppdvjthqldpwncqszvftbrmjlhg => 6
// $ ./solve nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg => 10
// $ ./solve zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw => 11

int main(int argc, char *argv[]) {
    char past[4];
    int found = 0;
    int i = 0;
    int j = 0;
    int ch = argv[1][i];
    while (!found && ch != '\0') {
        past[j] = ch;
        found = i > 2 &&
            past[0] != past[1] &&
            past[0] != past[2] &&
            past[0] != past[3] &&
            past[1] != past[2] &&
            past[1] != past[3] &&
            past[2] != past[3];
        i = i + 1;
        j = (j + 1) % 4;
        ch = argv[1][i];
    }
    printf("%d\n", found ? i : -1);
    return 0;
}
