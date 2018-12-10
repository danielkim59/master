// protection_flim.cpp : This file contains the 'main' function. Program execution begins and ends there. 
// 
  
#include "pch.h" 
#include <iostream> 
using namespace std; 
  
const int DSIZE = 13; 
const int WSIZE = 20; 
int D, W, K; 
  
  
int film[DSIZE][WSIZE]; 
int minChemicalCnt; 
int chemical[DSIZE]; 
  
void solve(int curD, int chemicalCnt, int prevContinuum[WSIZE], int prevMaxContinuum[WSIZE]) 
{ 
    if (chemicalCnt >= minChemicalCnt) return; 
  
    if (curD == D) 
    { 
        bool isSatisfied = true; 
        for (int i = 0; i < W; i++) 
        { 
            if (prevMaxContinuum[i] < K) 
            { 
                isSatisfied = false; 
                break; 
            } 
        } 
  
        if (isSatisfied && chemicalCnt < minChemicalCnt) 
        { 
            minChemicalCnt = chemicalCnt; 
        } 
  
        return; 
    } 
  
    int continuum[WSIZE], maxContinuum[WSIZE]; 
    int prev, cur; 
  
    for (int i = 2; i >= 0; i--) 
    { 
        chemical[curD] = i; 
        for (int j = 0; j < W; j++) 
        { 
            cur = chemical[curD] == 2 ? film[curD][j] : chemical[curD]; 
            prev = chemical[curD - 1] == 2 ? film[curD - 1][j] : chemical[curD - 1]; 
            continuum[j] = cur == prev ? prevContinuum[j] + 1 : 1; 
            if (continuum[j] > prevMaxContinuum[j]) 
                maxContinuum[j] = continuum[j]; 
            else 
                maxContinuum[j] = prevMaxContinuum[j]; 
        } 
  
        solve(curD + 1, chemicalCnt + (i == 2 ? 0 : 1), continuum, maxContinuum); 
    } 
  
} 
int main() 
{ 
    FILE* file; 
    freopen_s(&file, "input.txt", "r", stdin); 
  
    int test_case; 
    cin >> test_case; 
  
    for (int tc = 1; tc <= test_case; tc++) 
    { 
        cin >> D >> W >> K; 
        for (int i = 0; i < D; i++) 
        { 
            for (int j = 0; j < W; j++) 
            { 
                cin >> film[i][j]; 
            } 
        } 
  
        minChemicalCnt = K; 
  
        int continuum[WSIZE], maxContinuum[WSIZE]; 
  
        for (int i = 0; i < W; i++) 
        { 
            continuum[i] = maxContinuum[i] = 1; 
        } 
  
        chemical[0] = 2; 
        solve(1, 0, continuum, maxContinuum); 
  
        chemical[0] = 0; 
        solve(1, 1, continuum, maxContinuum); 
  
        chemical[0] = 1; 
        solve(1, 1, continuum, maxContinuum); 
  
        cout << "#" << tc << " " << minChemicalCnt << endl; 
    } 
  
    fclose(file); 
  
    return 0; 
} 
  

 
