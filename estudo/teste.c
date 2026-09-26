#include <stdio.h>

int main()
{
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *p = &v[0], *q = &v[10 - 1], temp;
    while (p < q)
    {
        temp = *p;
        *p++ = *q;
        *q-- = temp;
    }
}