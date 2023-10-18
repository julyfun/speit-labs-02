#include "lib.h"

#include <stdio.h>
#include <string.h>

void display(char* begin, char* end) {
    for (char* i = begin; i != end; i++) {
        putchar(*i);
    }
    puts("");
}

// private
static int is_palindromic(char* arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (arr[i] != arr[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

struct Res longest_palindrome1(char* arr, int len) {
    int long_start_i = 0;
    int long_len = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            const int cur_len = j - i + 1;
            if (is_palindromic(arr + i, cur_len)) {
                if (cur_len > long_len) {
                    long_len = cur_len;
                    long_start_i = i;
                }
            }
        }
    }
    return (struct Res) { .begin = arr + long_start_i, .end = arr + long_start_i + long_len };
}

static int expand_around_center(char* arr, int len, int left, int right) {
    int l = left, r = right;
    // l, r not included
    while (l >= 0 && r < len && arr[l] == arr[r]) {
        l--, r++;
    }
    return r - l - 1;
}

struct Res longest_palindrome2(char* arr, int len) {
    int long_s = 0, long_len = 0;
    for (int i = 0; i < len; i++) {
        int len1 = expand_around_center(arr, len, i, i);
        int len2 = expand_around_center(arr, len, i, i + 1);
        int max_len = len1 > len2 ? len1 : len2;
        if (max_len > long_len) {
            long_len = max_len;
            // len == 2: i & i + 1
            // len == 3: i-1, i, i+1
            long_s = i - (long_len - 1) / 2;
        }
    }
    return (struct Res) { .begin = arr + long_s, .end = arr + long_s + long_len };
}

static int min(int x, int y) {
    return x < y ? x : y;
}

struct Res manacher(char* arr, int len) {
    // about 256MB space
    static int rl[MAX_N * 2];
    static char c[MAX_N * 2];
    // c[0] 可以防止马拉车拉到这里。
    c[0] = '$';
    // 均匀插入 '#'，解决奇偶长度问题。
    c[1] = '#';
    int p = 1;
    for (int i = 0; i < len; i++) {
        c[++p] = arr[i];
        c[++p] = '#';
    }
    int maxr = 0, mid = 0, long_len = 0, long_mid = 0;
    for (int i = 1; i <= p; i++) {
        if (i < maxr) {
            rl[i] = min(rl[mid * 2 - i], maxr - i);
            // rl[i] 表示以 i 点为对称轴的回文子串的最大长度
        } else {
            rl[i] = 1;
        }
        int f = 0;
        while (c[i - rl[i]] == c[i + rl[i]]) {
            rl[i]++;
            f = 1;
        }
        if (f) {
            maxr = i + rl[i];
            mid = i;
        }
        if (rl[i] > long_len) {
            long_len = rl[i];
            long_mid = i;
        }
    }
    return (struct Res) {
        .begin = arr + (long_mid - long_len) / 2,
        .end = arr + (long_mid + long_len) / 2 - 2 + 1,
    };
}
