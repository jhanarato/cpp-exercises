#include <map>
#include <cstdio>

int main() {
    auto colour_of_magic = "Colour of Magic";
    auto the_light_fantastic = "The Light Fantastic";
    auto equal_rites = "Equal Rites";
    auto mort = "Mort";

    std::map<const char*, int> pub_year{
        { colour_of_magic, 1983 },
        { the_light_fantastic, 1986 },
    };
    
    {
        pub_year[equal_rites] = 1987;
    }

    bool equal_rites_at_1987 = pub_year.at(equal_rites);

    printf("equal_rites_at_1987 is: %d\n", equal_rites_at_1987);

    return 0;
}