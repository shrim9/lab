#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
void sstf(int arr[], int head, int size) {
int distance = 0;
int visited[size], order[size];
for (int i = 0; i < size; i++) {
visited[i] = 0;
}
for (int i = 0; i < size; i++) {
int min_distance = INT_MAX;
int min_index = -1;
for (int j = 0; j < size; j++) {
if (!visited[j] && abs(arr[j] - head) < min_distance) {
min_distance = abs(arr[j] - head);
min_index = j;
}
}
visited[min_index] = 1;
order[i] = arr[min_index];
distance += min_distance;
head = arr[min_index];
}
printf("SSTF Algorithm\n");
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
sstf(arr, head, size);
return 0;
}
/*Enter the number of requests: 8
Enter the requests:
176 79 34 60 92 11 41 114
Enter the initial head position: 50
SSTF Algorithm
Order of requests: 41 34 11 60 79 92 114 176 
Total no of tracks to be traversed: 204*/