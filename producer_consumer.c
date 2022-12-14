#include <stdio.h>
#include <stdlib.h>

int mutex = 1; // Initialize a mutex to 1

int full = 0; // Number of full slots as 0

int empty = 10, x = 0; // Number of empty slots as size of buffer

// Function to produce an item and add it to the buffer
void producer()
{
    --mutex; // Decrease mutex value by 1
    ++full;  // Increase the number of full slots by 1
    --empty; // Decrease the number of empty slots by 1

    x++; // Item produced
    printf("\nProducer produces item %d", x);

    ++mutex; // Increase mutex value by 1
}

// Function to consume an item and remove it from buffer
void consumer()
{
    --mutex; // Decrease mutex value by 1
    --full;  // Decrease the number of full slots by 1
    ++empty; // Increase the number of empty slots by 1

    printf("\nProducer produces item %d", x);
    x--; // Item consumed

    ++mutex; // Increase mutex value by 1
}

// Driver Code
int main()
{
    int n, i;
    printf("\n1. Producer"
           "\n2. Consumer"
           "\n3. Exit");

    for (i = 1; i > 0; i++)
    {
        printf("\n\nEnter your choice: ");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            // If mutex is 1 and empty is non-zero, then it is possible to produce
            if ((mutex == 1) && (empty != 0))
                producer();

            // Otherwise, print buffer is full
            else
                printf("\nBuffer is full!");
            break;

        case 2:
            // If mutex is 1 and full is non-zero, then it is possible to consume
            if ((mutex == 1) && (full != 0))
                consumer();

            // Otherwise, print Buffer is empty
            else
                printf("\nBuffer is empty!");
            break;

        // Exit Condition
        case 3:
            exit(0);
            break;
        }
    }
}
