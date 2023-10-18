
enum { MAX_N = (int)2e7 + 10 };

struct Res {
    char* begin;
    char* end;
};

void display(char* begin, char* end);

struct Res longest_palindrome1(char* arr, int len);

struct Res longest_palindrome2(char* arr, int len);

struct Res manacher(char* arr, int len);
