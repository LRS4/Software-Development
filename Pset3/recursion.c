#include <stdio.h>
#include <stdlib.h>

// function declaration
long long int fact(int n);

int main(int argc, char *argv[])
{
    // a program to compute the factorial of a given number (n)

    int n;

    // get an int from the user
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    // get result
    printf("Factorial of %d is %lld \n", n, fact(n));

}

// use recursive function to find factorial of the number - fact(n) = n * fact(n-1)
long long int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact(n-1);
}