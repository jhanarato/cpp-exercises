#include <cstdio>

int main() {
    int original = 100;
    int& original_ref = original;
    printf("Original: %d\n", original);
    printf("Reference: %d\n", original_ref);

    int new_value = 200;

    // original's value is changed to 200.
    original_ref = new_value;

    printf("Original: %d\n", original); // Now 200
    printf("New Value: %d\n", new_value); // Still 200
    printf("Reference %d\n", original_ref); // Also 200
}