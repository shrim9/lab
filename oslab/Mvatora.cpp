#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;
// Page table entry structure
struct PageTableEntry {
bool valid;
int frame;
};
// Function to convert binary string to integer
int binaryStringToInt(const string& binaryString) {
bitset<32> bits(binaryString);
return bits.to_ulong();
}
int main() {
int num_pages, page_size, num_frames;
cout << "Enter the number of pages: ";
cin >> num_pages;
cout << "Enter the page size (in bytes): ";
cin >> page_size;
cout << "Enter the number of frames: ";
cin >> num_frames;
// Calculate the number of bits required for page offset and frame
int number;
int offset_bits = log2(page_size);
int frame_bits = log2(num_frames);
// Create and populate the page table
PageTableEntry page_table[num_pages];
for (int i = 0; i < num_pages; i++) {
page_table[i].valid = true;
page_table[i].frame = i % num_frames;
}
string virtual_address;
cout << "Enter the virtual address (in binary): ";
cin >> virtual_address;
// Extract page number and offset from virtual address
string page_number_binary = virtual_address.substr(0,
virtual_address.length() - offset_bits);
int page_number = binaryStringToInt(page_number_binary);
string offset_binary = virtual_address.substr(virtual_address.length() -
offset_bits);
int offset = binaryStringToInt(offset_binary);
// Perform address translation
if (page_table[page_number].valid) {
int frame_number = page_table[page_number].frame;
int physical_address = (frame_number << offset_bits) + offset;
cout << "Physical address (in decimal): " << physical_address <<
endl;
cout << "Physical address (in binary): " <<
bitset<32>(physical_address) << endl;
} else {
cout << "Page fault: Invalid page number!" << endl;
}
return 0;
}
/*Enter the number of pages: 4
Enter the page size (in bytes): 1024
Enter the number of frames: 8
Enter the virtual address (in binary): 0101101010110010
Physical address (in decimal): 3762
Physical address (in binary): 00000000000000000000111010110010*/
