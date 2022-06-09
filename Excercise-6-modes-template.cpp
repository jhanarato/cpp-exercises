#include <cstdio>

template <typename T>
T mode(const T* values, size_t length) {
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
        
        // Find existing tally for next input value. 
        for(auto tally_idx = 0; tally_idx < number_of_tallies; tally_idx++) {
            if(input_value == tally_values[tally_idx]) {
                tally_counts[tally_idx]++;
                found = true;
            } 
        }
        
        // If the next input value is not found, start a new tally.
        if(!found) {
            tally_values[number_of_tallies] = input_value;
            tally_counts[number_of_tallies] = 1;
            number_of_tallies++;
        }
    }

    // Find the largest tally
    auto largest = 0;
    auto mode_found = 0;
    for(auto i = 0; i < number_of_tallies; i++) {
        if(tally_counts[i] > largest) {
            largest = tally_counts[i];
            mode_found = tally_values[i];
        }
    }
 
    // Check whether more than one input value 
    // share the highest tally. 
    auto largest_appears = 0;
    for(auto i = 0; i < number_of_tallies; i++) {
        if(tally_counts[i] == largest) {
            largest_appears++;
        }
    }

    // We're multi-modal. This is an error.
    if(largest_appears > 1) return 0;

    // Found a single mode. Return it.
    return mode_found;
}

int main() {
    long values[] = { 1, 2, 2, 1, 4, 3, 4, 4 };
    auto result = mode(values, 8);
    if(result) {
        printf("Mode found: %ld\n", result);
    } else {
        printf("No mode found\n");
    }

    return 0;
}