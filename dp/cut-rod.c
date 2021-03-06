/*
Given a price table for rod with different length and the lengh of a rod, return 
the max value that can be get from cutting the rod in pieces or no cutting at 
all if the price as a whole is the max. The cutting is free. Optionally print 
the actuall solution.

Source: Introduction to Algorithms, 3e, Chapter 15.1
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/common-numeric.h"

// Default Recursive Solution Without DP
int cut_rod (int* p, int size_p, int rod_length);
// Top-down with menoization DP
int memoized_cut_rod(int *p, int size_p, int rod_length);
int memoized_cut_rod_aux(int *p, int size_p, int rod_length, int *result);
//TODO: Implement this as solution for Exercise 15.1-4
int memoized_cut_rod_solution(int *p, int size_p, int rod_length, int *maxPrice, int *solution);
// Bottom-up DP
int bottom_up_cut_rod(int *p, int size_p, int rod_length);
int bottom_up_cut_rod_with_solution(int *p, int size_p, int rod_length, int *maxPrice, int *solution);
void print_cut_rod_solution (int rod_length, int *solution); 

int main() {
    
    int p[] = {1,5,8,9,10,17,17,20,24,30}; 
    
    
    for (int i = 1; i<11; i++){
        
        int *value = malloc ((i+1)*sizeof(int));
        int *solution = malloc ((i+1)*sizeof(int));
    
        printf("The result of %d is recursive: %d, memoized: %d, bottom up dp: %d and %d\n", 
         i, cut_rod(p, 10, i), memoized_cut_rod(p, 10, i),bottom_up_cut_rod(p,10,i), 
         bottom_up_cut_rod_with_solution(p, 10, i, value, solution));
        
        print_cut_rod_solution(i, solution);
        
        free (value);
        free (solution);
    }
   
    
}

int cut_rod (int* p, int size_p, int rod_length){
    
    if (rod_length == 0){
        return 0;
    }
    int maxP = -1;
    for (int i = 1; i<rod_length+1; i++){
        maxP = max(p[i-1] + cut_rod(p, size_p, rod_length-i), maxP);
    }
    return maxP;
}

int memoized_cut_rod(int *p, int size_p, int rod_length){
    
    int *result = malloc ((rod_length+1)*sizeof(int));
    result[0] = 0;
    for (int i = 1; i < rod_length+1; i++) {
        result[i] = -1;
    }
    int maxP = memoized_cut_rod_aux(p, size_p, rod_length, result);
    free (result);
    return maxP;
}

int memoized_cut_rod_aux(int *p, int size_p, int rod_length, int *result){
    
    if (rod_length == 0){
        return 0;
    }
    if (result[rod_length] != -1){
        
        return result[rod_length];
    }
    int maxP = -1;
    for (int i = 1; i < rod_length+1; i++) {
        
        maxP = max (maxP, p[i-1]+memoized_cut_rod_aux(p, size_p, rod_length-i, result));
    }
    result[rod_length] = maxP;
    
    return maxP;   
}

int bottom_up_cut_rod(int *p, int size_p, int rod_length){
    
    int *result = malloc ((rod_length+1) * sizeof (int));
    result[0] = 0;
    
    for (int i = 1; i < rod_length+1; i++) {
        
        int maxP = -1;    
        for (int j = 1; j <= i; j++){
            maxP = max(maxP,p[j-1]+result[i-j]);    
        }
        result[i] = maxP;
    }
    int r = result[rod_length];
    free (result);
    return r;
}
int bottom_up_cut_rod_with_solution(int *p, int size_p, int rod_length, int *maxPrice, int *solution){
    
    maxPrice[0] = 0;
    for (int i = 1; i < rod_length + 1; i++) {
        
        int maxP = 0;
        for (int j = 1; j <= i; j++) {
            int currentP = p[j-1] + maxPrice[i-j];
            if (currentP > maxP){
                maxP = currentP;
                maxPrice[i] = maxP;
                solution[i] = j;    
            }
        }
    }
    
    return maxPrice[rod_length];
}

void print_cut_rod_solution (int rod_length, int *solution){
    
    int j = 1;
    for (int i = rod_length; i >0; ) {
        
        printf("The %dth cut is of length %d\n", j++, solution[i]);
        i -= solution[i];
    }    
}
int memoized_cut_rod_solution(int *p, int size_p, int rod_length, int *maxPrice, int *solution){
    
    //TODO: Excercise 15.1-4
    return 0;
}

