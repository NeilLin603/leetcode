#include <stdio.h>

//! Solving Concept (use example 1):
//!
//!        gas = [ 1, 2, 3, 4, 5]
//!       cost = [ 3, 4, 5, 1, 2]
//! gas - cost = [-2,-2,-2, 3, 3]
//!
//! Cumulative sum of gas - cost (forward):
//! start at 0 = [-2,-4,-6,-3, 0]
//! start at 3 = [ 4, 2, 0, 3, 6]
//!
//! ----------------------------------------------------------------
//! Start pos: 0  3 |   Forward sum         |   Backward sum
//! ----------------------------------------------------------------
//!            0  6 |                   *   |               *
//!           -1  5 |                       |
//!           -2  4 |   *                   |           *
//!           -3  3 |               *       |                   *
//!           -4  2 |       *               |       *
//!           -5  1 |                       |
//!           -6  0 |           *           |   *
//! ----------------------------------------------------------------
//! Target index    |               ^       |               ^
//! ----------------------------------------------------------------
//!
//! If the total sum of array 'gas - cost' < 0: return -1
//! else: return the \b next index to the position that the
//!       \b forward cumulative sum of 'gas - cost' has the \b minimum value
//!                                     or
//!       return the index to the position that the \b backward cumulative sum
//!       of 'gas - cost' has the \b maximum value
int canCompleteCircuit(int *gas, int gasSize, int *cost, int costSize) {
    int sum = 0, max = 0;
    costSize = 0; // Take this var as the return index since it's redundant
    while (gasSize--) {
        sum += gas[gasSize] - cost[gasSize];
        if (max < sum) {
            max = sum;
            costSize = gasSize;
        }
    }
    if (sum < 0) {
        return -1;
    }
    return costSize;
}

void printArray(int *nums, int numsSize, char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]");
}

int main() {
    struct {
        int gas[16], cost[16], gasSize;
    } tc[] = {
        {.gas = {1,2,3,4,5}, .cost = {3,4,5,1,2}, .gasSize = 5},
        {.gas = {2,3,4}, .cost = {3,4,3}, .gasSize = 3},
        {.gas = {3,1,1}, .cost = {1,2,2}, .gasSize = 3}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].gas, tc[i].gasSize, "Input: gas");
        printArray(tc[i].cost, tc[i].gasSize, ", cost");

        // Output
        printf("\nOutput: %d\n\n", canCompleteCircuit(tc[i].gas, tc[i].gasSize,
                                                      tc[i].cost, 0));
    }

    return 0;
}
