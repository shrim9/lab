#include<stdio.h>
#include<stdlib.h>
void fcfs(int arr[], int head, int size) {
int distance = 0;
int order[size];
for (int i = 0; i < size; i++) {
order[i] = arr[i];
distance += abs(arr[i] - head);
head = arr[i];
}
printf("FCFS Algorithm\n");
printf("Order of requests: ");
for (int i = 0; i < size; i++) {
printf("%d ", order[i]);
}
printf("\nTotal no of tracks to be traversed: %d\n", distance);
}
int main() {
int size, head;
printf("Enter the number of requests: ");
scanf("%d", &size);
int arr[size];
printf("Enter the requests:\n");
for (int i = 0; i < size; i++) {
scanf("%d", &arr[i]);
}
printf("Enter the initial head position: ");
scanf("%d", &head);
fcfs(arr, head, size);
return 0;
}

/*Enter the number of requests: 8
Enter the requests:
176 79 34 60 92 11 41 114
Enter the initial head position: 50
FCFS Algorithm
Order of requests: 176 79 34 60 92 11 41 114 
Total no of tracks to be traversed: 510*/