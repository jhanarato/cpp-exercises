#include <cstdio>

int mode(const int* values, size_t length) {
    for(auto value_idx = 0; value_idx < length; value_idx++) {
        if(values[value_idx] == 0) return 0; // Error: no zero value allowed.
    }

    // For each index tally_value appears tally_count times.
    int tally_values[length] = { 0 };
    int tally_counts[length] = { 0 };
    int number_of_tallies = 0;

    // Tally each input value.
    for(auto value_idx = 0; value_idx < length; value_idx++) {
        auto input_value = values[value_idx];
        bool found = false;
        
        for(auto tally_idx = 0; tally_idx < number_of_tallies; tally_idx++) {
            if(input_value == tally_values[tally_idx]) {
                tally_counts[tally_idx]++;
                found = true;
            } 
        }
        
        if(!found) {
            tally_values[number_of_tallies] = input_value;
            tally_counts[number_of_tallies] = 1;
            number_of_tallies++;
        }
    }

    // Testing: print the values and their tallies.
    for(auto i = 0; i < length; i++) {
        printf("Value: %d, Tally: %d\n", tally_values[i], tally_counts[i]);
    }

    
    return 0;
}

int main() {
    int values[] = { 1, 2, 2, 4, 3, 4, 4 };
    mode(values, 7);
}