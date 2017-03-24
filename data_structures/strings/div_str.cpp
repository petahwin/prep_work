#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)

/*
Things I missed/didn't get to in 30 min:
- Overflow
- Int quotient of 0
- Using while loop as opposed to nested if statement within for loop
- atoi takes char *, not char
- cast malloc
- adding null char
*/

char * div_str(char * in, int divisor);

bool is_digit(char c) 
{
    return '0' <= c && c <= '9';
}

bool is_int(char * in)
{
    if (NULL == in) return false;
    if ('+' == in[0] || '-' == in[0]) ++in;
    int len = strlen(in); 
    if (len == 0) return false;
    for (int i = 0; i != len; ++i)
    {
        if (!is_digit(in[i])) return false;
    }

    return true;
}

char * div_str(char * in, int divisor)
{
    const int MAX_DIGITS = 256;
    if (!is_int(in)) return NULL;
    if (divisor == 0) return NULL;

    bool isNeg = false;
    if (!is_digit(in[0]))
    {
        isNeg = '-' == in[0];
        ++in;
    }

    char * q = (char*)malloc(MAX_DIGITS + 1);
    char * tmp = q;
    if ((isNeg && divisor > 0) || (!isNeg && divisor < 0))
    {
        tmp[0] = '-';
        ++tmp;
    }

    int len = strlen(in);
    divisor = divisor < 0 ? -1 * divisor : divisor;

    // This is where things got weird with the leading zeros
    bool start_writing = false;

    int remainder = 0;
    int j = 0;

    // Try the while loop approach as well
    /*
    while (remainder < divisor)
    {
        remainder = remainder * 10 + *(in++);
    }
    */
    for (int i = 0; i != len; ++i)
    {
        remainder = remainder * 10 + (in[i] - '0');
        if (remainder >= divisor) start_writing = true; // added; should flip the first time we can divide
        
        if (start_writing) 
        {
            tmp[j++] = '0' + (remainder / divisor);
        }

        remainder = remainder % divisor;
    }
    tmp[j] = '\0';

    return q;
}

void test_1()
{
    assert(0 == strcmp(div_str("12", 4), "3"));
    return;
}

void test_2()
{
    assert(0 == strcmp(div_str("-12", 4), "-3"));
    return;
}

void test_3()
{
    assert(0 == strcmp(div_str("-113", -45), "2"));
    return;
}

// Register tests here
void (*tests[])() = {
    test_1,
    test_2,
    test_3
};

int main(int argc, char ** argv) 
{
    const size_t n_tests = sizeof(tests)/sizeof(tests[0]);

    if (argc != 2)
    {
        DIE("Usage: exe <test_number>");
    }

    const size_t test_no = atoi(argv[1]);
    if (!(0 <= test_no && test_no <= n_tests))
    {
        DIE("Invalid or out of bounds test number");
    }

    if (test_no == 0)
    {
        printf("Running all tests\n");
        for (size_t i = 0; i != n_tests; ++i)
        {
            tests[i]();
            printf("Test %lu passed\n", i+1);
        }
        printf("All tests passed\n");
    }
    else
    {
        tests[test_no-1]();
        printf("Test %lu passed\n", test_no);
    }

    
    return EXIT_SUCCESS;
}

