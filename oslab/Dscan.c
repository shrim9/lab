#include <stdio.h>
#include <stdlib.h>
void scan(int n, int RQ[], int initial, int size)
{
int move, TotalHeadMoment = 0, i, j;
printf("Enter the head movement direction for high 1 and for low 0\n");
scanf("%d", &move);
// logic for Scan disk scheduling
/*logic for sort the request array */
for (i = 0; i < n; i++)
{
for (j = 0; j < n - i - 1; j++)
{
if (RQ[j] > RQ[j + 1])
{
int temp;
temp = RQ[j];
RQ[j] = RQ[j + 1];
RQ[j + 1] = temp;
}
}
}
int index;
for (i = 0; i < n; i++)
{
if (initial < RQ[i])
{
index = i;
break;
}
}
// if movement is towards high value
if (move == 1)
{
for (i = index; i < n; i++)
{
TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
initial = RQ[i];
}
// last movement for max size
TotalHeadMoment = TotalHeadMoment + abs(size - RQ[i - 1] - 1);
initial = size - 1;
for (i = index - 1; i >= 0; i--)
{
TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
initial = RQ[i];
}
}
// if movement is towards low value
else
{
for (i = index - 1; i >= 0; i--)
{
TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
initial = RQ[i];
}
// last movement for min size
TotalHeadMoment = TotalHeadMoment + abs(RQ[i + 1] - 0);
initial = 0;
for (i = index; i < n; i++)
{
TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
initial = RQ[i];
}
}
printf("Total tracks traversed by SCAN are: %d", TotalHeadMoment);
}
int main()
{
int RQ[100], n, initial, size;
printf("Enter the number of Requests\n");
scanf("%d", &n);
printf("Enter the Requests sequence\n");
for (int i = 0; i < n; i++)
{
scanf("%d", &RQ[i]);
}
printf("Enter initial head position\n");
scanf("%d", &initial);
printf("Enter total disk size\n");
scanf("%d", &size);
scan(n, RQ, initial, size);
return 0;
}
/*Enter the number of Requests
8
Enter the Requests sequence
176 79 34 60 92 11 41 114
Enter initial head position
50
Enter total disk size
200
Enter the head movement direction for high 1 and for low 0
0
Total tracks traversed by SCAN are: 226*/