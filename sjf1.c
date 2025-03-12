#include <stdio.h>
#include <limits.h>


void findWaitingTime(int n, int at[], int bt[], int wt[], int tat[]) {
    int remaining_bt[n];
    int complete = 0, t = 0, min_index;
    int shortest = INT_MAX, finish_time;
    int check = 0;


    for (int i = 0; i < n; i++)
        remaining_bt[i] = bt[i];

    while (complete != n) {
        shortest = INT_MAX;
        min_index = -1;


        for (int i = 0; i < n; i++) {
            if (at[i] <= t && remaining_bt[i] > 0 && remaining_bt[i] < shortest) {
                shortest = remaining_bt[i];
                min_index = i;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }


        remaining_bt[min_index]--;


        if (remaining_bt[min_index] == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;
            tat[min_index] = finish_time - at[min_index];
            wt[min_index] = tat[min_index] - bt[min_index];

            if (wt[min_index] < 0)
                wt[min_index] = 0;
        }

        t++;
    }
}


void displayResults(int processes[], int n, int at[], int bt[], int wt[], int tat[]) {
    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f ms", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f ms\n", total_tat / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], at[n], bt[n], wt[n], tat[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }


    findWaitingTime(n, at, bt, wt, tat);


    displayResults(processes, n, at, bt, wt, tat);

    return 0;
}
Enter the number of processes: 4
Enter Arrival Time and Burst Time for each process:
Process 1 - Arrival Time: 0
Process 1 - Burst Time: 5
Process 2 - Arrival Time: 2
Process 2 - Burst Time: 7
Process 3 - Arrival Time: 8
Process 3 - Burst Time: 2
Process 4 - Arrival Time: 9
Process 4 - Burst Time: 7

Process Arrival Time    Burst Time      Waiting Time    Turnaround Time
1       0               5               0               5
2       2               7               5               12
3       8               2               0               2
4       9               7               5               12

Average Waiting Time: 2.50 ms
Average Turnaround Time: 7.75 ms

