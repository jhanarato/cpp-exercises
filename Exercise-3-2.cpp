#include <cstdio>

// Original code listing 3-6
int main() {
  char lower[] = "abc?e";
  char upper[] = "ABC?E";
  char* upper_ptr = upper; // Equivalent: &upper[0]

  lower[3] = 'd'; // lower now contains a b c d e \0
  upper_ptr[3] = 'D'; // upper now contains A B C D E \0

  char letter_d = lower[3]; // letter_d equals 'd'
  char letter_D = upper_ptr[3]; // letter_D equals 'D'

  printf("lower: %s\nupper: %s", lower, upper);

  lower[7] = 'g'; // Super bad. You must never do this.
}

// Task:
// Add a read_from and write_to function to the above code. 
// These functions should read or write to upper or lower as appropriate.
// Perform bounds checking to prevent buffer overflows.

const char read_from(const char char_array [], int index) {
  // Calculate the number of characters
  // Nope! doesn't work as char[] devolves to char*. You'll
  // need to supply the known length to make this work.
  size_t n_elements = sizeof(char_array) / sizeof(char);

  // Return NUL character if array index out of bounds.
  if(index >= n_elements) return 0;

  // Otherwise all is good and we get the character at index.
  return char_array[index];
}

bool write_to(char char_array[], char to_write, int index) {
  // Calculate the number of characters
  size_t n_elements = sizeof(char_array) / sizeof(char);

  // Return false if array index out of bounds.
  if(index >= n_elements) return false;

  // All is well and we write to the character array.
  char_array[index] = to_write;
  return true;
}