#include <stdio.h>

int main() {
    int N;
    int J;
    int Z;
    int contadorTeste = 1;
    while (1) {
        scanf("%d", &N);
        if (N == 0) {
            break;
        }
        printf("Teste %d\n", contadorTeste);
        int diff = 0;
        while (N > 0) {
            scanf("%d %d", &J, &Z);
            diff = diff + (J - Z);
            printf("%d\n", diff);
            N -= 1;
        }
        printf("\n");
        contadorTeste += 1;
    }
    return 0;
}