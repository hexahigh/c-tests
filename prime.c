#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int isPrime(long long int n){
    if(n <= 1) return 0;
    if(n == 2) return 1;
    if(n % 2 == 0) return 0;
    for(long long int i = 3; i <= sqrt(n); i+=2){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
    long long int num = 10000; // Default value
    long long int start = 0; // Default value

    // Parse command-line arguments
    for(int i = 1; i < argc; ++i){
        if(strcmp(argv[i], "-n") == 0 && i + 1 < argc){
            num = atoll(argv[++i]);
        } else if(strcmp(argv[i], "-s") == 0 && i + 1 < argc){
            start = atoll(argv[++i]);
        }
    }

    for(long long int i = start; i <= num; i++){
        if(isPrime(i)){
            printf("%lld\n", i);
        }
    }
    return 0;
}
