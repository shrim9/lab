#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 4;
    vector<int> id = {1, 2, 3, 4};
    vector<int> priority = {2, 4, 1, 0};
    vector<int> bt = {9, 2, 5, 7};
    int ts = 2;
    vector<int> ct(n+1);
    ct[0] = 0;
    vector<int> rem_bt = bt;
    int counter = 0, k = 0;
    while(counter<n){
        for(int i=0; i<n; ++i){
            if(rem_bt[i] == 0) continue; // Process over
            if(rem_bt[i] <= ts){ // Process time less than equal time slice
                k += rem_bt[i];
                rem_bt[i] = 0;
                counter++;
                ct[i+1] = k;
            }
            else{
                k += ts;
                rem_bt[i] -= ts;
            }
        }
    }
    vector<int> wt(n);
    for(int i=0; i<n; ++i){
        wt[i] = ct[i+1] - bt[i];
    }
    cout<<"Gantt Chart for Round Robin :"<<endl;
    cout<<"ID\tBT\tCT\tWT"<<endl;
    for(int i=0; i<n; ++i){
        cout<<id[i]<<"\t"<<bt[i]<<"\t"<<ct[i+1]<<"\t"<<wt[i]<<endl;
    }
    return 0;
}
/*#include<stdio.h>  
void main()  
{  
    int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];  
    float avg_wt, avg_tat;  
    printf("Total number of process in the system: ");  
    scanf("%d", &NOP);  
    y = NOP; 
   
for(i=0; i<NOP; i++)  
{  
printf("\nEnter the Arrival and Burst time of the Process[%d]\n", i+1);  
printf("Arrival time is: ");  
scanf("%d", &at[i]);  
printf("Burst time is: ");  
scanf("%d", &bt[i]);  
temp[i] = bt[i]; 
}  
 
printf("\nEnter the Time Quantum for the process: ");  
scanf("%d", &quant);  
printf("\nProcess No     FT    TAT    WT");  
for(sum=0, i = 0; y!=0; )  
{  
if(temp[i] <= quant && temp[i] > 0)   
{  
    sum = sum + temp[i];  
    temp[i] = 0;  
    count=1;  
    }     
    else if(temp[i] > 0)  
    {  
        temp[i] = temp[i] - quant;  
        sum = sum + quant;    
    }  
    if(temp[i]==0 && count==1)  
    {  
        y--; 
        printf("\nProcess%d       %d     %d     %d", i+1, bt[i], sum-at[i], sum-at[i]-bt[i]);  
        wt = wt+sum-at[i]-bt[i];  
        tat = tat+sum-at[i];  
        count =0;     
    }  
    if(i==NOP-1)  
    {  
        i=0;  
    }  
    else if(at[i+1]<=sum)  
    {  
        i++;  
    }  
    else  
    {  
        i=0;  
    }  
}  
avg_wt = wt * 1.0/NOP;  
avg_tat = tat * 1.0/NOP;  
printf("\n Average Turn Around Time: \t%f", avg_wt);  
printf("\n Average Waiting Time: \t%f", avg_tat);  
}*/