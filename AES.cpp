#include<iostream>
#include<time.h>
#include"bits/stdc++.h"
// #include "S_Box.cpp"
#include "mix_column.cpp"
#include "Shift_Rows.cpp"
#include "key_expansion.cpp"
using namespace std;
vector<vector<int>> strvec(string &S,int i)
{
  vector<vector<int>> vec(4,vector<int>(4,(int)'\0'));
  for(int j=0;j<16 && j+i<S.size();j++)
  {
    vec[j%4][j/4]=S[i+j];
  }
  return vec;
}
vector<vector<vector<int>>> make_arr(string &S)
{
  vector<vector<vector<int>>> arr;
  for(int i=0;i<S.size();i+=16)
  {
    arr.push_back(strvec(S,i));
  }
  return arr;
}
void showarrstr(vector<vector<int>> &c)
{
  for(int i=0;i<16;i++)
  cout<<(char)c[i%4][i/4];
  cout<<endl;
}
void showstr(vector<vector<vector<int>>> &vec)
{
  for(int i=0;i<vec.size();i++)
  {
    showarrstr(vec[i]);
  }
  cout<<endl;
}
void aes_enc(vector<vector<int>> &pt,vector<vector<int>> &key)
{
  AddRoundKey(pt,key);
  for(int i=0;i<10;i++)
  {
    sbox(pt,lookup);
    shift_rows(pt);
    mix_columnenc(pt);
    key=nextkey(key,i);
    AddRoundKey(pt,key);
  }
}
void aes_dec(vector<vector<int>> &pt,vector<vector<int>> &key)
{
  AddRoundKey(pt,key);
  for(int i=9;i>=0;i--)
  {
    mix_columndec(pt);
    inv_shift_rows(pt);
    sbox(pt,invlookup);
    key=befkey(key,i);
    AddRoundKey(pt,key);
  }
}
int main()
{
  string S1="abcdefghijklmnop";
  string ky="128BitKEYATLEAST";
  vector<vector<int>> pt=strvec(S1,0);
  vector<vector<int>> key=strvec(ky,0);
  cout<<endl;

  showarrstr(pt);
  aes_enc(pt,key);
  showarrstr(pt);
  aes_dec(pt,key);
  showarrstr(pt);
  cout<<endl;
}
