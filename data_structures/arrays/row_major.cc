#include <iostream>

using namespace std;

char idx(char arr[], int i, int j, int m, int n)
{
  return arr[i*n + j];
}

void testFake2Darray()
{
  char arr[] = 
  {
    'a','b','c',
    'd','1','e',
    'f','g','h',
    '2','i','j',
    'k','l','3',
    'm','n','o',
    'p','4','7',
    '8','9','0'
  };
  
  int m = 8;
  int n = 3;
#define IDX(arr, i, j) idx(arr, i, j, m, n)
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      cout << IDX(arr, i, j) << ' ';
    }
    cout << '\n';
  }
#undef IDX
  return;
}

int main()
{
  testFake2Darray();
  return 0;
}
