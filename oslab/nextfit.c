#include <stdio.h>

#define MEMORY_SIZE 100

typedef struct Node {
    int start;
    int end;
    struct Node* next;
} Node;

Node* head = NULL;
Node* lastAllocated = NULL;

void initialize() {
    head = (Node*)malloc(sizeof(Node));
    head->start = 0;
    head->end = MEMORY_SIZE - 1;
    head->next = NULL;
    lastAllocated = head;
}

void allocate(int size) {
    Node* curr = lastAllocated;
    while (curr != NULL) {
        int block_size = curr->end - curr->start + 1;
        if (block_size >= size) {
            printf("Allocated memory block: %d - %d\n", curr->start, curr->start + size - 1);
            curr->start += size;
            if (curr->start > curr->end) {
                // Remove the node if the entire block is allocated
                if (curr == head) {
                    head = curr->next;
                } else {
                    Node* prev = head;
                    while (prev->next != curr) {
                        prev = prev->next;
                    }
                    prev->next = curr->next;
                }
                free(curr);
            }
            lastAllocated = curr;
            return;
        }
        curr = curr->next;
        if (curr == NULL) {
            // Wrap around to the beginning of the list if reached the end
            curr = head;
        }
        if (curr == lastAllocated) {
            // Wrapped around the list, allocation failed
            printf("Memory allocation failed. Not enough space.\n");
            return;
        }
    }
}

void deallocate(int start, int end) {
    Node* curr = head;
    while (curr != NULL) {
        if (end < curr->start) {
            // Insert a new node before the current node
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->start = start;
            newNode->end = end;
            newNode->next = curr;
            if (curr == head) {
                head = newNode;
            } else {
                Node* prev = head;
                while (prev->next != curr) {
                    prev = prev->next;
                }
                prev->next = newNode;
            }
            return;
        } else if (start > curr->end) {
            // Move to the next node
            curr = curr->next;
        } else {
            // Overlapping memory blocks, deallocation failed
            printf("Memory deallocation failed. Overlapping memory blocks.\n");
            return;
        }
    }
    // Reached the end, insert the new node at the end
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->start = start;
    newNode->end = end;
    newNode->next = NULL;
    Node* prev = head;
    while (prev->next != NULL) {
        prev = prev->next;
    }
    prev->next = newNode;
}

void displayMemory() {
    Node* curr = head;
    while (curr != NULL) {
        printf("Memory block: %d - %d\n", curr->start, curr->end);
        curr = curr->next;
    }
}

int main() {
    initialize();

    // Allocate memory blocks
    allocate(20);
    allocate(30);
    allocate(10);

    // Display allocated memory blocks
    printf("Allocated memory blocks:\n");
    displayMemory();

    // Deallocate memory blocks
    deallocate(20, 49);
    deallocate(0, 19);

    // Display memory after deallocation
    printf("Memory blocks after deallocation:\n");
    displayMemory();

    return 0;
}
