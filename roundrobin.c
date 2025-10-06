#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n];
    int wt[n], tat[n];
    int i, time = 0, done, totalTAT = 0, totalWT = 0;

    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n|");
    done = 0;
    int flag;

    while(done < n) {
        flag = 0;
        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && at[i] <= time) {
                flag = 1;
                if(rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    printf(" P%d |", i+1);
                    done++;
                } else {
                    time += tq;
                    rt[i] -= tq;
                    printf(" P%d |", i+1);
                }
            }
        }
        if(flag == 0) time++; // CPU idle
    }

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalTAT += tat[i];
        totalWT += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)totalTAT/n);
    printf("Average Waiting Time = %.2f\n", (float)totalWT/n);

    return 0;
}
