#include <iostream>
#include <thread>

// compile like: g++ vecAdd.cc -std=c++11 -pthread -o vecAdd
int isPrime(int num);
void myRun(int start, int stop, int* count);

int main() {
    int count = 0;
    int low = 10;
    int high = 100;
    int range = high - low;

    int numThreads = 4;
    std::thread* ths[numThreads];
    for (int i = 0; i < numThreads; i++) {
        int start = low + (range / numThreads) * i; // what out for int division
        int stop = low + (range / numThreads) * (i + 1);
        if(i + 1 == 4)
            stop = high;

        std::thread* th = new std::thread(myRun, start, stop, &count);
        ths[i] = th;
    }

    for (int i = 0; i < numThreads; i++) {
        ths[i]->join();
    }
}

void myRun(int start, int stop, int* count) {
    std::cout << "start: " << start << ", stop: " << stop << "\n";

    for (int i = start; i < stop; i++) {
        *count += isPrime(i);
    }
    std::cout << "count: " << *count << "\n";
}

int isPrime(int num) {
    for (int i = 2; i < num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}