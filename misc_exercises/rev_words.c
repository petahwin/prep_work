#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DIE(str) {fprintf(stderr, "Error: %s\n", (str)); return EXIT_FAILURE;}

// Returns array index
size_t findNextSpace(char * buf, size_t start)
{
    size_t pos = start;

    while(!(buf[pos] == '\0' || buf[pos] == ' ')) ++pos;

    return pos;
}

// Start and length(aka num of chars to be included in the reversal)
// leave it to the caller to not fuck up the pos or len
void reverse(char * buf, size_t start_pos, size_t len)
{
    if (len == 0) return;
    size_t end_pos = start_pos + len - 1;
    assert(start_pos <= end_pos);

    while(start_pos < end_pos)
    {
        char tmp = buf[start_pos];
        buf[start_pos++] = buf[end_pos];
        buf[end_pos--] = tmp;
    }
}

void rev_words(char * buf, size_t len)
{
    if (len == 0 || len == 1) return;
    reverse(buf, 0, len);
    size_t start_pos = 0;
    size_t space_pos = 0;

    while(buf[space_pos] != '\0')
    {
        space_pos = findNextSpace(buf, start_pos);
        reverse(buf, start_pos, space_pos - start_pos);
        start_pos = space_pos + 1;
    }
    // Hit '\0' char
}

void testReverse()
{
    printf("Testing 'reverse' function\n");

    char str1[] = "foobar";
    char * str2 = "raboof";
    reverse(str1, 0, 6);
    assert(!strcmp(str1, str2));

    char str3[] = "three";
    char * str4 = "eerht";
    reverse(str3, 0, 5);
    assert(!strcmp(str3,str4));

    char str5[] = "hell";
    char * str6 = "hlel";
    reverse(str5, 1, 2);
    assert(!strcmp(str5, str6));

    char str7[] = "";
    char * str8 = "";
    reverse(str7, 0, 1);
    assert(!strcmp(str7, str8));
    
    printf("End test\n");
}

void testReverseWords()
{    
    printf("Testing 'rev_words' function\n");
    
    char str1[] = "";
    char * str2 = "";
    rev_words(str1, 1);
    assert(!strcmp(str1, str2));

    char str3[] = "foo";
    char * str4 = "foo";
    rev_words(str3, 3);
    assert(!strcmp(str3, str4));

    char str5[] = "foo bar";
    char * str6 = "bar foo";
    rev_words(str5, 7);
    assert(!strcmp(str5, str6));

    char str7[] = "alice bob charlie";
    char * str8 = "charlie bob alice";
    rev_words(str7, 17);
    assert(!strcmp(str7, str8));

    char str9[] = "a b c";
    char * str10 = "c b a";
    rev_words(str9, 5);
    assert(!strcmp(str9, str10));
    
    printf("End test\n");
}

void test1()
{
    char * str = "hello world";

}

int main(int argc, char ** argv) 
{
    void (*testArr[])(void) = {
                                testReverse,
                                testReverseWords
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();
    return EXIT_SUCCESS;
}

