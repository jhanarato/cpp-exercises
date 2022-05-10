#include <cstdio>
#include <utility>
#include <sys/time.h>

struct TimerClass {
    // Constructor sets the start time.
    TimerClass() 
        : _name { nullptr } {
        struct timeval current_time;
        gettimeofday(&current_time, nullptr);
        _start_time = current_time.tv_sec;
    }

    // Constructor with name that is optional for the class
    TimerClass(const char* name) 
        : _name(name) {
        struct timeval current_time;
        gettimeofday(&current_time, nullptr);
        _start_time = current_time.tv_sec;
    }

    // Destructor prints the time elapsed since instance creation.
    ~TimerClass() {
        struct timeval current_time;
        gettimeofday(&current_time, nullptr);
        auto end_time = current_time.tv_sec;
        auto age = end_time - _start_time;
        if(_name) {
            printf("Timer %s age: %ld\n", _name, age);
        } else {
            printf("Unnamed timer age: %ld\n", age);
        }
        
    }

    // Copy constructor
    TimerClass(const TimerClass& other)
        : _start_time { other._start_time }
        , _name { other._name }
        {}

    // Copy assignment operator
    TimerClass& operator=(TimerClass& other) {
        if(this == &other)
            return *this;
        _start_time = other._start_time;
        _name = other._name;
    }

    // Move constructor
    TimerClass(TimerClass&& other) noexcept
        : _start_time(other._start_time) 
        , _name(other._name)
        {
            other._start_time = 0;
            other._name = 0;
        }

    // Move assignment operator
    TimerClass& operator=(TimerClass&& other) noexcept {
        if(this == &other) return *this;
        _start_time = other._start_time;
        _name = other._name;
        other._start_time = 0;
        other._name = nullptr;
    }

    private:
        int _start_time;
        const char* _name;
};

void take_a_while() {
    for(int i{}; i < 125; i++) {
        for(int j{}; j < 10000000; j++) {
            int x = i * 5;
        }
    }
}

void copy_constructor() {
    TimerClass t1;
    TimerClass t2 { t1 };
    take_a_while(); 
}

void copy_assignment() {
    TimerClass t1;
    TimerClass t2 = t1;
    take_a_while();
}

void move_constructor() {
    TimerClass t1 { "T1" };
    TimerClass t2 { std::move(t1) };
    take_a_while();
}

void move_assignment() {
    TimerClass t1;
    TimerClass t2 = std::move(t1);
    take_a_while();
}

void use_after_move_assignment() {
    TimerClass t1 { "T1" };
    TimerClass t2 = std::move(t1);
    printf("Moved\n");
    TimerClass t3 { t1 };
    take_a_while();
}

void examine_rvalues() {
    
}

void name_a_timer() {
    TimerClass t1 { "one" };
    TimerClass t2 {};
    take_a_while();
}

int main() {
    // copy_constructor();
    // copy_assignment();
    // move_constructor();
    // move_assignment();
    use_after_move_assignment();
    // name_a_timer();
    return 0;
}