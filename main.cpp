/*
 * main.cpp
 *
 *  Created on: Jun 11, 2021
 *      Author: d-w-h
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

typedef struct table_element {
    bool is_set = false;
    bool sum_possible;
    std::vector <int> array;
} t_elem;

typedef struct result_element {
    bool sum_possible;
    std::vector <int> array;
} r_elem;

int num_calls = 0;

r_elem can_sum(int n, int A[], int target_sum, int sum, t_elem** m_table, std::vector <int> array_elems) {

    bool sum_possible = false;
    r_elem r_element = {sum_possible, array_elems};

    num_calls++;

    if(m_table[sum]->is_set == true) {
        return r_element = {m_table[sum]->sum_possible, m_table[sum]->array};
    }
    else {
        for(int i = 0; i < n; ++i) {
        	int sum_o = sum + A[i];
            if(sum_o != sum) {
                if(r_element.array.size() == 0) {
                    r_element.array = array_elems;
                    r_element.array.push_back(A[i]);
                }
                else {
                    r_element.array.push_back(A[i]);
                }
                if(target_sum == sum_o) {
                    sum_possible = true;
                    return r_element = {sum_possible, r_element.array};
                }
                else if(sum_o < target_sum) {
                    r_element = can_sum(n, A, target_sum, sum_o, m_table, r_element.array);
                    if(r_element.sum_possible == true) {
                        sum_possible = true;
                        return r_element = {sum_possible, r_element.array};
                    }
                }
                else if(sum_o > target_sum) {
                    r_element.array = {};
                    r_element = {sum_possible, r_element.array};
                }
            }
        }

        m_table[sum]->is_set = true;
        m_table[sum]->sum_possible = sum_possible;
        m_table[sum]->array = r_element.array ;
        r_element = {sum_possible, r_element.array};
    }

    return r_element;
}

r_elem how_sum(int n, int A[], int target_sum) {

    t_elem** m_table = new t_elem*[target_sum+1];

    for(int i = 0; i < target_sum + 1; ++i) {
        m_table[i] = new t_elem;
        m_table[i]->is_set = false;
        m_table[i]->sum_possible = false;
    }

    r_elem r_element = {};

    r_element = can_sum(n, A, target_sum, 0, m_table, r_element.array);

    if(r_element.sum_possible == false) {
        r_element = {0};
    }
    else {}

    return r_element;
}

bool is_sum_valid(r_elem r_element, int target_sum) {

    int sum = 0;

    for(unsigned int i = 0; i < r_element.array.size(); ++i) {
        sum += r_element.array[i];
    }

    bool sum_valid = (sum == target_sum);

    return sum_valid;
}

int main(int argc, char* argv[]) {

    int N = 20; //Number of elements in array
    int target_sum = 100; //Target sum

    int* A = new int[N]; //Array containing elements for target sum

    //Seed random number generator
    srand (time(NULL));

    //Initialize array with random numbers
    for(int i = 0; i < N; ++i) {
        A[i] = rand() % 100 + (5*i)/2;
    }

    //Check if target sum can be obtained from elements in A and return array solution
    r_elem r_element = how_sum(N, A, target_sum);
    bool sum_possible = r_element.sum_possible;
    std::vector <int> array = r_element.array;

    //Print results
    for(int i = 0; i < N; ++i) {
        printf("A[%i]: %i\n", i, A[i]);
    }

    printf("num_calls: %i\n", num_calls);
    if(sum_possible) {
        printf("it is possible to form the target sum out of elements of array A\n");
        printf("Solution array: \n");
        for(unsigned int i = 0; i < array.size(); ++i) {
            printf("array[%i]: %i\n", i, array[i]);
        }
    }
    else {
        printf("it is not possible to form the target sum out of elements of array A\n");
    }

    bool is_valid = is_sum_valid(r_element, target_sum);
    printf("is_sum_valid: %i\n", is_valid);
    printf("done\n");

    return 0;
}
