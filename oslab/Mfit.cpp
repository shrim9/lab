#include <iostream>
#include <vector>

struct Block {
    int size;
    bool allocated;
};

struct Process {
    int size;
    bool allocated;
};

void firstFit(std::vector<Block>& blocks, std::vector<Process>& processes) {
    for (auto& process : processes) {
        for (auto& block : blocks) {
            if (!block.allocated && block.size >= process.size) {
                block.allocated = true;
                process.allocated = true;
                break;
            }
        }
    }
}

void nextFit(std::vector<Block>& blocks, std::vector<Process>& processes) {
    int j = 0;
    for (auto& process : processes) {
        while (j < blocks.size()) {
            if (!blocks[j].allocated && blocks[j].size >= process.size) {
                blocks[j].allocated = true;
                process.allocated = true;
                j++;
                break;
            }
            j++;
        }
    }
}

void bestFit(std::vector<Block>& blocks, std::vector<Process>& processes) {
    for (auto& process : processes) {
           int INT_MAX;
        int bestBlockIndex = -1;
        int minSizeDiff = INT_MAX;
        for (int j = 0; j < blocks.size(); j++) {
            if (!blocks[j].allocated && blocks[j].size >= process.size &&
                blocks[j].size - process.size < minSizeDiff) {
                bestBlockIndex = j;
                minSizeDiff = blocks[j].size - process.size;
            }
        }
        if (bestBlockIndex != -1) {
            blocks[bestBlockIndex].allocated = true;
            process.allocated = true;
        }
    }
}

void worstFit(std::vector<Block>& blocks, std::vector<Process>& processes) {
    for (auto& process : processes) {
        int INT_MIN; 
        int worstBlockIndex = -1;
        int maxSizeDiff = INT_MIN;
        for (int j = 0; j < blocks.size(); j++) {
            if (!blocks[j].allocated && blocks[j].size >= process.size &&
                blocks[j].size - process.size > maxSizeDiff) {
                worstBlockIndex = j;
                maxSizeDiff = blocks[j].size - process.size;
            }
        }
        if (worstBlockIndex != -1) {
            blocks[worstBlockIndex].allocated = true;
            process.allocated = true;
        }
    }
}

int main() {
    int num_blocks, num_processes;
    std::cout << "Enter the number of blocks: ";
    std::cin >> num_blocks;
    std::cout << "Enter the number of processes: ";
    std::cin >> num_processes;
    
    std::vector<Block> blocks(num_blocks);
    std::vector<Process> processes(num_processes);
    
    for (auto& block : blocks) {
        std::cout << "Enter the size of a block: ";
        std::cin >> block.size;
        block.allocated = false;
    }
    
    for (auto& process : processes) {
        std::cout << "Enter the size of a process: ";
        std::cin >> process.size;
        process.allocated = false;
    }
    
    int choice;
    std::cout << "Select the placement algorithm:\n";
    std::cout << "1. First Fit\n";
    std::cout << "2. Next Fit\n";
    std::cout << "3. Best Fit\n";
    std::cout << "4. Worst Fit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    
    switch (choice) {
        case 1:
            firstFit(blocks, processes);
            break;
        case 2:
            nextFit(blocks, processes);
            break;
        case 3:
            bestFit(blocks, processes);
            break;
        case 4:
            worstFit(blocks, processes);
            break;
        default:
            std::cout << "Invalid choice!\n";
            return 0;
    }
    
    std::cout << "Allocation Results:\n";
    for (const auto& process : processes) {
        if (process.allocated) {
            std::cout << "Process of size " << process.size << " is allocated.\n";
        } else {
            std::cout << "Process of size " << process.size << " is not allocated.\n";
        }
    }
    
    return 0;
}
