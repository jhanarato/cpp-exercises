// From page 68
#include <cstdio>

int main() {
    int gettysburg{};
    printf("gettysburg: %d\n", gettysburg);
    // Get a pointer to the integer gettysburg
    int * gettysburg_address = &gettysburg;
    // Print the pointer address
    printf("&gettysburg: %p\n", gettysburg_address);
}