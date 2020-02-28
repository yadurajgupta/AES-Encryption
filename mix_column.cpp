#include<iostream>
#include<time.h>
#include "finite_field.cpp"
using namespace std;
// vector<vector<int>> ms={ {2,3,1,1},
//                          {1,2,3,1},
//                          {1,1,2,3},
//                          {3,1,1,2}
//                        };
// vector<vector<int>> ims={ {14,11,13,9 },
//                           {9 ,14,11,13},
//                           {13,9 ,14,11},
//                           {11,13,9 ,14}
//                        };
void mixwordenc(vector<vector<int>> &A,int j)
{
  vector<int> s1=vector<int>(4,0);
  s1[0]= mult(A[0][j],2) ^ mult(A[1][j],3) ^ mult(A[2][j],1) ^ mult(A[3][j],1);
  s1[1]= mult(A[0][j],1) ^ mult(A[1][j],2) ^ mult(A[2][j],3) ^ mult(A[3][j],1);
  s1[2]= mult(A[0][j],1) ^ mult(A[1][j],1) ^ mult(A[2][j],2) ^ mult(A[3][j],3);
  s1[3]= mult(A[0][j],3) ^ mult(A[1][j],1) ^ mult(A[2][j],1) ^ mult(A[3][j],2);
  for(int i=0;i<4;i++)
  A[i][j]=s1[i];
}
void mixworddec(vector<vector<int>> &A,int j)
{
  vector<int> s1=vector<int>(4,0);
  s1[0]= mult(A[0][j],14)  ^ mult(A[1][j],11) ^ mult(A[2][j],13) ^ mult(A[3][j],9);
  s1[1]= mult(A[0][j],9)   ^ mult(A[1][j],14) ^ mult(A[2][j],11) ^ mult(A[3][j],13);
  s1[2]= mult(A[0][j],13)  ^ mult(A[1][j],9)  ^ mult(A[2][j],14) ^ mult(A[3][j],11);
  s1[3]= mult(A[0][j],11)  ^ mult(A[1][j],13) ^ mult(A[2][j],9)  ^ mult(A[3][j],14);
  for(int i=0;i<4;i++)
  A[i][j]=s1[i];
}

void mix_columnenc(vector<vector<int>> &A)
{
  for(int i=0;i<4;i++)
  mixwordenc(A,i);
}
void mix_columndec(vector<vector<int>> &A)
{
  for(int i=0;i<4;i++)
  mixworddec(A,i);
}
