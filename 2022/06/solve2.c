#include <stdio.h>
#include <stdlib.h>

// https://adventofcode.com/2022/day/6

// $ ./solve2 4 bvwbjplbgvbhsrlpgdmjqwftvncz => 5
// $ ./solve2 4 nppdvjthqldpwncqszvftbrmjlhg => 6
// $ ./solve2 4 nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg => 10
// $ ./solve2 4 zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw => 11

// $ ./solve2 14 mjqjpqmgbljsphdztnvjfqwrcgsmlb => 19
// $ ./solve2 14 bvwbjplbgvbhsrlpgdmjqwftvncz => 23
// $ ./solve2 14 nppdvjthqldpwncqszvftbrmjlhg => 23
// $ ./solve2 14 nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg => 29
// $ ./solve2 14 zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw => 26

// $ ./solve2 14 `cat input.txt`
// 3256

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    char past[n];
    int found = 0;
    int i = 0;
    int j = 0;
    int ch = argv[2][i];
    while (!found && ch != '\0') {
        past[j] = ch;
        found = i > 2;
        for (int k = 0; found && k < n; k++) {
            for (int r = k + 1; found && r < n; r++) {
                found = found && past[k] != past[r];
            }
        }
        i = i + 1;
        j = (j + 1) % n;
        ch = argv[2][i];
    }
    printf("%d\n", found ? i : -1);
    return 0;
}
