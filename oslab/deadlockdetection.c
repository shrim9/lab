#include<stdio.h>
int i,j,np,nr;
int main()
{
static int mark[20];
int alloc[10][10],request[10][10],avail[10],r[10],w[10];
printf("\nEnter the no of process: ");
scanf("%d",&np);
printf("\nEnter the no of instances: ");
scanf("%d",&nr);
for(i=0;i<nr;i++)
{
printf("\nValue of the Instances A%d: ",i+1);
scanf("%d",&r[i]);
}
printf("\nEnter the allocation matrix:");
for(i=0;i<np;i++)
for(j=0;j<nr;j++)
scanf("%d",&alloc[i][j]);
printf("\nEnter the request matrix:");
for(i=0;i<np;i++)
for(j=0;j<nr;j++)
scanf("%d",&request[i][j]);
//Available Resource calculation
for(j=0;j<nr;j++)
{
avail[j]=r[j];
for(i=0;i<np;i++)
{
avail[j]-= alloc[i][j];
}
}
//marking processes with zero allocation
for(i=0;i<np;i++)
{
int count=0;
for(j=0;j<nr;j++)
{
if(alloc[i][j]==0)
count++;
else
break;
}
if(count==nr)
mark[i]=1;
}
// initialize W with avail
for(j=0;j<nr;j++)
w[j]=avail[j];
//mark processes where request <= avai
for(i=0;i<np;i++)
{
int canbeprocessed=0;
if(mark[i]!=1)
{
for(j=0;j<nr;j++)
{
if(request[i][j]<=w[j])
canbeprocessed=1;
else
{
canbeprocessed=0;
break;
}
}
if(canbeprocessed)
{
mark[i]=1;
for(j=0;j<nr;j++)
w[j]+=alloc[i][j];
}
}
}
//checking unmarked processes
int deadlock=0;
for(i=0;i<np;i++)
if(mark[i]!=1)
deadlock=1;
if(deadlock==1)
printf("\n Deadlock detected");
else
printf("\n No Deadlock detected");
return 0;
}

/*Enter the no of process: 4

Enter the no of instances: 3

Value of the Instances A1: 10

Value of the Instances A2: 5

Value of the Instances A3: 7

Enter the allocation matrix:
1 1 0
2 0 1
3 0 3
0 2 1

Enter the request matrix:
1 0 1
3 0 0
0 0 2
2 0 0

 No Deadlock detected*/