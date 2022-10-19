#include <iostream>
#include <thread>

// compile like: g++ vecAdd.cc -std=c++11 -pthread -o vecAdd
int isPrime(int num);
void myRun(int start, int stop, int index, int* count);

int main() {
    int low = 10;
    int high = 100;
    int range = high - low;

    int numThreads = 4;
    std::thread* ths[numThreads];

    int* count = (int*)malloc(numThreads * sizeof(int));

    for (int i = 0; i < numThreads; i++) {
        int start = low + (range / numThreads) * i; 
        int stop = low + (range / numThreads) * (i + 1);

        int index = i;

        if(i + 1 == 4)
            stop = high;

        std::thread* th = new std::thread(myRun, start, stop, index, count);
        ths[i] = th;
    }

    for (int i = 0; i < numThreads; i++) {
        ths[i]->join();
    }

    int total = 0;
    for(int i = 0; i < numThreads; i++) {
        total += count[i];
    }

    std::cout << "total: " << total << "\n";
    free(count);
}

void myRun(int start, int stop, int index, int* count) {
    //std::cout << "start: " << start << ", stop: " << stop << "\n";

    for (int i = start; i < stop; i++) {
        count[index] += isPrime(i);
    }
    //std::cout << "count: " << *count << "\n";
}

int isPrime(int num) {
    for (int i = 2; i < num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}