#include <stdio.h>

void sortProcesses(int n, int at[], int bt[], int index[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {

                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;


                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;


                temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
        }
    }
}

void calculateTimes(int n, int at[], int bt[], int index[]) {
    int ct[n], tat[n], wt[n], completed = 0, current_time = 0, is_completed[n];
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed < n) {
        int min_index = -1;


        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !is_completed[i]) {
                if (min_index == -1 || bt[i] < bt[min_index]) {
                    min_index = i;
                }
            }
        }

        if (min_index == -1) {
            current_time++;
            continue;
        }

        current_time += bt[min_index];
        ct[min_index] = current_time;
        tat[min_index] = ct[min_index] - at[min_index];
        wt[min_index] = tat[min_index] - bt[min_index];
        is_completed[min_index] = 1;

        total_wt += wt[min_index];
        total_tat += tat[min_index];
        completed++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        int original_index = index[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", original_index + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], index[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        index[i] = i;
    }


    sortProcesses(n, at, bt, index);

    calculateTimes(n, at, bt, index);
    return 0;
}
Enter the number of processes: 4
Enter arrival time and burst time for process 1: 0
5
Enter arrival time and burst time for process 2: 2
7
Enter arrival time and burst time for process 3: 8
2
Enter arrival time and burst time for process 4: 9
7

Process AT      BT      CT      TAT     WT
1       0       5       5       5       0
2       2       7       12      10      3
3       8       2       14      6       4
4       9       7       21      12      5

Average Waiting Time: 3.00
Average Turnaround Time: 8.25
