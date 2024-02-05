#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

void fillWithZeros(char* ptr, size_t size) {
    memset(ptr, 0, size);
}

long getCurrentMemoryUsage() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss;
}

int main() {
    size_t size = 1024 * 1024; // Initial size: 1MB
    char* buffer = malloc(size);
    if (!buffer) {
        perror("Initial allocation failed");
        return 1;
    }
    fillWithZeros(buffer, size);

    long startMemoryUsage = getCurrentMemoryUsage();
    printf("Starting memory usage: %ld bytes\n", startMemoryUsage);

    while (1) {
        sleep(1); // Wait for 1 second
        size_t newSize = size * 1.1; // Increase size by 110%
        char* newBuffer = realloc(buffer, newSize);
        if (!newBuffer) {
            perror("Realloc failed");
            break;
        }
        buffer = newBuffer;
        fillWithZeros(buffer + size, newSize - size); // Fill the newly allocated part with zeros
        size = newSize;

        long currentMemoryUsage = getCurrentMemoryUsage();
        printf("Total memory usage: %ld megabytes\n", currentMemoryUsage);
        startMemoryUsage = currentMemoryUsage;
    }

    free(buffer); // Free the memory before exiting
    return 0;
}

