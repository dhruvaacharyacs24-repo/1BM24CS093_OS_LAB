#include<stdio.h>
#include<conio.h>

void main(){
    float at[20],bt[20],ct[20],tat[20],wt[20],avgTAT=0,avgWT=0;
    int n,id[20],time=0,completed=0,visited[20];

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    printf("Enter arrival time and burst time:\n");
    for(int i=0;i<n;i++){
        printf("Process: %d\n",i);
        id[i]=i;
        printf("Arrival time: ");
        scanf("%f",&at[i]);
        printf("Burst time: ");
        scanf("%f",&bt[i]);
        visited[i]=0;
    }

    while(completed < n){

        int index = -1;
        float minbt = 1000;

        for(int i=0;i<n;i++){
            if(at[i] <= time && visited[i] == 0 && bt[i] < minbt){
                minbt = bt[i];
                index = i;
            }
        }

        if(index == -1){
            time++;
            continue;
        }

        ct[index] = time + bt[index];
        tat[index] = ct[index] - at[index];
        wt[index] = tat[index] - bt[index];
        time = ct[index];
        visited[index] = 1;
        completed++;
    }


    for(int p=0;p<n;p++){
        avgTAT += tat[p];
        avgWT += wt[p];
    }
    avgTAT /= n;
    avgWT /= n;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
               id[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage waiting time: %f", avgWT);
    printf("\nAverage TAT: %f", avgTAT);
}
