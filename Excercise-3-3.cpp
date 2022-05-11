#include <cstdio>

// Element is a modified version of listing 3-9.
// TODO: Make list doubly linked.
struct Element {
    // Pointer to next element in list.
    Element* next{};
    Element* previous{};
    
    // Insert a new element into the list.
    void insert_after(Element* new_element) {
        new_element->next = next;
        new_element->previous = this;
        next = new_element;
    }

    // Element data.
    char prefix[2];
    short operating_number;
};

// Construct a list as per listing 3-10
int main() {
    // Construct three elements.
    Element trooper1, trooper2, trooper3;

    // Set code for each "trooper" and assemble the list.
    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 421;

    trooper1.insert_after(&trooper2);

    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 2187;

    trooper2.insert_after(&trooper3);

    trooper3.prefix[0] = 'L';
    trooper3.prefix[1] = 'S';
    trooper3.operating_number = 005;

    // Iterate over linked list.
    for(Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("Stormtrooper %c%c-%d\n",
            cursor->prefix[0],
            cursor->prefix[1],
            cursor->operating_number
        );
    }

    // TODO: Iterate backwards.
    for(Element *cursor = &trooper3; cursor; cursor = cursor->previous) {
        printf("Stormtrooper %c%c-%d\n",
            cursor->prefix[0],
            cursor->prefix[1],
            cursor->operating_number
        );
    }
}