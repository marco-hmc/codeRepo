#include <bits/stdc++.h>
using namespace std;

void swap(int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n){
    int minVal;
    for (int i = 0; i < n - 1; i++){
        minVal = i;
        for (int j = i + 1; j < n; j++){
            if(arr[j] < arr[minVal]){
                minVal = j;
            }
        }
        swap(&arr[minVal], &arr[i]);
    }
}

void display(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
	int arr[] = {84, 55, 19, 72, 41};
	int n = sizeof(arr)/sizeof(arr[0]);
	selectionSort(arr, n);
	cout << "***Sorted array***\n";
	display(arr, n);
	return 0;
}