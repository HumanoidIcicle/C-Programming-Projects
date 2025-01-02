#include <stdio.h>

int main(void) {
    double expo = 1, x, term = 1;
    int count = 1;
    printf("Enter value for x:\n");
    scanf("%lf", &x);
    printf("Terms\tValues\n%d\t%.7lf\n", count, expo);

    while ((0.0000001 < term) || (-0.0000001 > term)) {
        term *= (x / count);
        expo += term;
        count++;
        printf("%d\t%.7lf\n", count, expo);
    }
    return 0;
}
