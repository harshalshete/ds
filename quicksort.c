#include <stdio.h>
int qcnt;
void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/*
 * Function which generates median of three pivot.
 */
int median_pivot(int a[], int s, int e) {
    int pivot = 0;
    int med = (s + e) / 2;
    int tmp;

    if (a[s] > a[med]) {
        swap(a, s, med);
    }
    if (a[med] > a[e]) {
        swap(a, e, med);
    }
    if (a[s] > a[med]) {
        swap(a, s, med);
    }

    swap(a, e, med);

    pivot = a[e];
    return (pivot);
}

int partition(int a[], int s, int e) {
    int i, pi, pivot;

    i = pi = s;
    pivot = median_pivot(a, s, e);

    for (i = s; i < e; i++) {
        if (a[i] <= pivot) {
            swap(a, i, pi);
            pi++;
        }
    }
    swap(a, pi, e);

    printf("%d\n", pi);
    return (pi);
}

void qsort(int a[], int s, int e) {
    int pi;
    qcnt++;
    if (s < e) {
        pi = partition(a, s, e);
        qsort(a, s, pi-1);
        qsort(a, pi+1, e);
    }
}

int main() {
    //int a[] = {23, 45, 56, 930, 8, 2, 5};
    int a[] = {23, 45, 56, 930, 988, 1002, 5};
    int cnt = (sizeof(a) / sizeof(int));
    int i;

    for (i = 0; i < cnt; i++) {
        printf(" %d | ", a[i]);
    }
    printf("\n");

    qsort(a, 0, (cnt - 1));

    for (i = 0; i < cnt; i++) {
        printf(" %d | ", a[i]);
    }
    printf("\n");
    printf("\nqcnt = %d", qcnt);
}

