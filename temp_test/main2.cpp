#include <iostream>
using namespace std;

// Task 2
int exponent_search(int a_size, int *a, int element) {
    int buff = a_size;
    int j = 1;
    while(j <=a_size) {
        if(element <= a[j-1]) {
            buff = j-1;
            break;
        }
        j = j << 1;
        if(j >a_size) {
            if(a[a_size-1] >= element) {
                buff = a_size-1;
                break;
            }
            else {
                buff = a_size;
                break;
            }
        }
    }
    return buff;
}

int * find_min_ind_for_element(int a_size, int b_size, int *a, int *b) {
    int *buff = new int[b_size];
    int left = 0;
    int right = 0;
    int mid = 0;

    for(int i = 0; i < b_size; ++i) {
        mid = 0;
        left = 0;
        right = exponent_search(a_size, a, b[i]);
        while(left < right) {
            mid = (left + right) / 2;
            if(a[mid] >= b[i]) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        if(a[right] >= b[i]) {
            buff[i] = right;
        }
        else {
            buff[i] = a_size;
        }
    }

    return buff;
}

int main() {
    int n = 0;
    int m = 0;
    int tmp = 0;
    cin >> n >> m;
    int *a = new int[n * sizeof(int)];
    int *b = new int[m * sizeof(int)];

    for(int i = 0; i < n; ++i) {
        cin >> tmp;
        a[i] = tmp;
    }
    for(int i = 0; i < m; ++i) {
        cin >> tmp;
        b[i] = tmp;
    }
    
    int *buff;
    buff = find_min_ind_for_element(n, m, a, b);

    for(int i = 0; i < m; ++i) {
        cout << buff[i] << ' ';
    }
    
    delete[] a;
    delete[] b;
    delete[] buff;
    return 0;
}
