#include <stdio.h>
#include <math.h>

void aggregateMethod(float n) {
    float tot = 0;
    int arr[4] = {0};
    printf("Counter:0, Cost:0 \n");
    for (int j = 0; j < n; j++) {
        int i = 0;
        while (arr[i] == 1 && i < 4) {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4) {
            tot++;
            arr[i] = 1;
        }
        printf("Counter:%d, Cost:%f \n", j + 1, tot);
    }
    float avgcost = tot / n;
    printf("Avg Cost:%f \n", avgcost);
}

void accountingMethod() {
    int size[16];
    printf("\n");
    int tot[10];
    int credit[11] = {0};
    int arr[4] = {0};
    for (int j = 0; j < 10; j++) {
        int total = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4) {
            arr[i] = 0;
            total++;
            i++;
        }
        if (i < 4) {
            total++;
            arr[i] = 1;
        }
        credit[j + 1] = 2 - total + credit[j];
        printf("Counter:%d, ", j + 1);
        printf("Cost:%d \n", credit[j]);
    }
}

void potentialMethod(float n) {
    float tot = 0;
    int arr[4] = {0};
    printf("Counter:0, Cost:0\n");
    float prev_potential = 0;
    float prevones = 0;
    for (int j = 0; j < n; j++) {
        float currentones = 0;
        float potential = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4) {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4) {
            tot++;
            arr[i] = 1;
        }
        for (int k = 0; k < 4; k++)
            if (arr[k] == 1)
                currentones++; //Calculates the number of ones in the counter array.
        float current_cost = tot;
        potential = current_cost + potential - prev_potential;
        prev_potential = current_cost;
        float amort = potential + (currentones - prevones);
        prevones = currentones;
        printf("Counter:%d, Cost:%f, Current Cost:%f, amort Cost:%f\n", j + 1, current_cost, potential, amort);
    }
    float avg_cost = tot / n;
    printf("Avg Cost:%f\n", avg_cost);
}

int main() {
    int choice;
    printf("Choose a method (1: Aggregate, 2: Accounting, 3: Potential): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter value between 0 to %f\n", pow(2, 4));
            float n_aggregate;
            scanf("%f", &n_aggregate);
            aggregateMethod(n_aggregate);
            break;
        case 2:
            accountingMethod();
            break;
        case 3:
            printf("Enter value between 0 to %f\n", pow(2, 4));
            float n_potential;
            scanf("%f", &n_potential);
            potentialMethod(n_potential);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

// Enter value between 0 to 16.000000
// 15