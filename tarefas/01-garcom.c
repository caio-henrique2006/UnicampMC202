#include <stdio.h>

int main() {
    int N;
    int L;
    int C;
    int QCoposQuebrados = 0;
    scanf("%d", &N);
    while (N > 0) {
        scanf("%d %d", &L, &C);
        if (L > C) {
            QCoposQuebrados += C;
        }
        N -= 1;
    }
    printf("%d\n", QCoposQuebrados);
    return 0;
}