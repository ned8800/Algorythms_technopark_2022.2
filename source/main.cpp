#include <iostream>
#include <matrix.hpp>
using namespace std;

int main() {
    
    std::cout << even_count(25) << std::endl;
    std::cout << "_________________________________________________" << std::endl;

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
    std::cout << "_________________________________________________" << std::endl;




    return 0;
}
