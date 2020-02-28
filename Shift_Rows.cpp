#include<iostream>
#include<time.h>
// #include"bits/stdc++.h"
#include <vector>
using namespace std;
//SHIFTS ROWS BY R
void shift_rows(vector<vector<int>> &A,int r)
{
  int i=abs(r);
  if(i==0)
  return;
  int N=A[i].size();
  vector<int> B(A[i].size(),0);
  for(int j=0;j<A[i].size();j++)
  B[((j+r)%N+N)%N]=A[i][j];
  for(int j=0;j<A[i].size();j++)
  A[i][j]=B[j];
}
void shift_rows(vector<vector<int>> &A)
{
  shift_rows(A,0);
  shift_rows(A,1);
  shift_rows(A,2);
  shift_rows(A,3);
}
void inv_shift_rows(vector<vector<int>> &A)
{
  shift_rows(A,0);
  shift_rows(A,-1);
  shift_rows(A,-2);
  shift_rows(A,-3);
}
