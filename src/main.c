#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib.h"

enum { DN = (int)1e3 };
char buf[MAX_N];

int main(int argc, char** argv) {
    fprintf(
        stderr,
        "\
Input the string to find its longest palindrome in 3 algorithms.\n\
To generate a random long string, input a number to specify\n\
the length of the random string, at most 2e7:\n"
    );
    scanf("%s", buf);
    if (isdigit(buf[0])) {
        srand(time(0));
        int len = 0;
        sscanf(buf, "%d", &len);
        // 先随机一个较长的区间生成回文串
        int expected_l = rand() % len;
        int expected_r = expected_l + rand() % (len - expected_l);
        int l = expected_l, r = expected_r;
        while (l <= r) {
            char put = rand() % 26 + 'a';
            buf[l++] = buf[r--] = put;
        }
        // 剩下的部分大概率为 'a'，极小概率为 'b'，用来卡普通算法的时间
        for (int i = 0; i < len; i++) {
            if (i < expected_l || i > expected_r) {
                buf[i] = rand() % len <= 2 ? 'b' : 'a';
            }
        }
        buf[len] = '\0';
    }
    struct Res (*func[])(char*, int) = { longest_palindrome1, longest_palindrome2, manacher };
    const char names[][50] = { "longest_palindrome1", "longest_palindrome2", "manacher" };
    if (strlen(buf) > DN) {
        freopen("output.txt", "w", stdout);
        fprintf(
            stderr,
            "The inputted string is too long so the output is redirected into output.txt.\n"
        );
    }
    printf("Inputted string:\n%s\n", buf);
    for (int i = 2; i < 3; i++) {
        // 比较三个算法的时间
        clock_t start = clock();
        struct Res res = func[i](buf, strlen(buf));
        clock_t end = clock();
        fprintf(stderr, "---\n%s(): ", names[i]);
        fprintf(stderr, "%lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
        display(res.begin, res.end);
    }
    return 0;
}
