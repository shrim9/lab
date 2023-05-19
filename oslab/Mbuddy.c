#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 1024

typedef struct Block {
    int size;
    int is_free;
} Block;

Block memory[MAX_MEMORY_SIZE];

void initialize_memory() {
    memory[0].size = MAX_MEMORY_SIZE;
    memory[0].is_free = 1;
}

void* myAlloc(int size) {
    int i = 0;

    // Find the first block that is large enough and free
    while (i < MAX_MEMORY_SIZE) {
        if (memory[i].size >= size && memory[i].is_free) {
            break;
        }
        i++;
    }

    if (i >= MAX_MEMORY_SIZE) {
        printf("Unable to allocate memory.\n");
        return NULL;
    }

    // Split the block until it reaches the desired size
    while (memory[i].size >= size * 2) {
        memory[i * 2 + 1].size = memory[i].size / 2;
        memory[i * 2 + 1].is_free = 1;

        memory[i * 2 + 2].size = memory[i].size / 2;
        memory[i * 2 + 2].is_free = 1;

        memory[i].is_free = 0;
        i = i * 2 + 1; // Move to the left child
    }

    memory[i].is_free = 0;
    return (void*)&memory[i];
}

void myFree(void* ptr) {
    Block* block = (Block*)ptr;
    block->is_free = 1;

    // Merge free blocks whenever possible
    int i = ((int)block - (int)memory) / sizeof(Block);

    while (i > 0 && memory[i].is_free && memory[i ^ 1].is_free) {
        i = (i - 1) / 2;
        memory[i].is_free = 1;
    }
}

void print_memory() {
    printf("Memory Blocks:\n");
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        printf("[%d] Size: %d, Free: %d\n", i, memory[i].size, memory[i].is_free);
    }
    printf("\n");
}

int main() {
    initialize_memory();

    int size;

    printf("Enter the size of process 1: ");
    scanf("%d", &size);
    void* p1 = myAlloc(size);
    if (p1 == NULL) {
        printf("Process 1 could not allocate memory due to insufficient free memory\n");
    } else {
        printf("Process 1 allocated memory at address: %p\n", p1);
    }

    // Repeat the same process for the other processes

    print_memory();

    // Free the allocated memory
    myFree(p1);

    print_memory();

    return 0;
}
