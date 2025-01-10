/***** ****
 * Sum of Numbers
 * ******/

#include <iostream>
using namespace std;

void sumOfNumbers(int **, int **, int **);

int main() {
    int range = 5;
    int *ptr1 = &range;

    int i = 1;
    int *ptr2 = &i;

    int j = 0;
    int *ptr3 = &j;
    sumOfNumbers(&ptr2, &ptr1, &ptr3);
    return 0;
}

void sumOfNumbers(int **i, int **range, int **sum) {
    int temp_i = **i;
    int temp_range = **range;
    int temp_sum = **sum;

    if (temp_i == temp_range) {
        temp_sum = temp_sum + temp_i;
        cout << "Sum of numbers: " << temp_sum << endl;
        return;
    }
    temp_sum = temp_sum + temp_i;
    int x = (**i) + 1;
    int *ptr_x = &x;

    int *ptr_temp_range = &temp_range;
    int *ptr_temp_sum = &temp_sum;
    sumOfNumbers(&ptr_x, &ptr_temp_range, &ptr_temp_sum);
}