#include <gtest/gtest.h>
// #include "vector.hpp"
// #include "matrix.hpp"
#include "matrix.hpp"

TEST(ALG_Task1, count1) {
    EXPECT_EQ(even_count(25), 2);
}

TEST(ALG_Task1, count2) {
    EXPECT_EQ(even_count(29), 3);
}

TEST(ALG_Task2, test1) {
    int n = 2;
    int m = 1;
    int *a = new int[n];
    a[0] = 1; a[1] = 2;
    int *b = new int[m];
    b[0] = 2;
    int *buff1 = new int[m];
    buff1[0] = 1;
    int *buff2 = new int[m];
    buff2 = find_min_ind_for_element(n, m, a, b);
    EXPECT_EQ(buff2[0], buff1[0]);
    delete[] a;
    delete[] b;
    delete[] buff1;
    delete[] buff2;
}

TEST(ALG_Task2, test2) {
    int n = 4;
    int m = 3;
    int *a = new int[n];
    a[0] = 2; a[1] = 4; a[2] = 5; a[3] = 7;
    int *b = new int[m];
    b[0] = 4; b[1] = 6; b[2] = 1;
    int *buff1 = new int[m];
    buff1[0] = 1; buff1[1] = 3; buff1[2] = 0;
    int *buff2 = new int[m];
    buff2 = find_min_ind_for_element(n, m, a, b);
    EXPECT_EQ(buff2[0], buff1[0]);
    EXPECT_EQ(buff2[1], buff1[1]);
    EXPECT_EQ(buff2[2], buff1[2]);
    delete[] a;
    delete[] b;
    delete[] buff1;
    delete[] buff2;    
}
