#include<stdio.h>
#include<stdlib.h>

struct Process {
    int id, bt, at, ct, tat, wt;
};

// Function to take input arrival and burst times for all processes
void input(struct Process *p, int n) {
	int i;
    for ( i = 0; i < n; i++) {
        printf("\nEnter arrival time for process %d:\n", i + 1);
        scanf("%d", &p[i].at);
        printf("\nEnter burst time for process %d:\n", i + 1);
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
    }
}

// Function to calculate waiting, turn-around and completion time
void calc(struct Process *p, int n) {
    int sum = 0;
    sum = sum + p[0].at;
    int i;
    for ( i = 0; i < n; i++) {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if (sum < p[i + 1].at) {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        }
    }
}

// Function to sort processes with respect to arrival times 
void sort(struct Process *p, int n) {
	int i;
    for ( i = 0; i < n - 1; i++) {
    	int j;
        for ( j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                int temp;
                // Sorting burst times
                temp = p[j].bt;
                p[j].bt = p[j + 1].bt;
                p[j + 1].bt = temp;
                // Sorting arrival times
                temp = p[j].at;
                p[j].at = p[j + 1].at;
                p[j + 1].at = temp;
                // Sorting their respective IDs
                temp = p[j].id;
                p[j].id = p[j + 1].id;
                p[j + 1].id = temp;
            }
        }
    }
}

// Function to display the process details
void show(struct Process *p, int n) {
    printf("Process\tArrival\tBurst\tWaiting\tTurn Around\tCompletion\n");
    int i,wt=0,tat=0;
    for ( i = 0; i < n; i++) {
    	wt+=p[i].wt;
    	tat+=p[i].tat;
        printf(" P[%d]\t %d\t%d\t%d\t %d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
    }
    printf("Average waiting time is %0.2f\n",(float)wt/n);
    printf("Average turn around time is %0.2f",(float)tat/n);
    
}

// Main function
int main() {
    int n;
    printf("\nEnter the number of processes in your system:\n");
    scanf("%d", &n);
	    struct Process *p = (struct Process*)malloc(n * sizeof(struct Process));
	    input(p, n);
    sort(p, n);
    calc(p, n);
    show(p, n);
    free(p);
    return 0;
}

