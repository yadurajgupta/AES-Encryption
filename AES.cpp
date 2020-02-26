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
void aes_dec(vector<vector<int>> &pt,vector<vector<int>> key)
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
void enc(vector<vector<vector<int>>> &pt,vector<vector<int>> &key)
{
  vector<vector<int>> tempkey(key);
  for(int i=0;i<pt.size();i++)
  {
    tempkey=vector<vector<int>>(key);
    aes_enc(pt[i],tempkey);
  }
  key=tempkey;
}
void dec(vector<vector<vector<int>>> &ct,vector<vector<int>> &key)
{
  for(int i=0;i<ct.size();i++)
  {
    aes_dec(ct[i],key);
  }
}
int main()
{
  string S1="abcdefghijklmnopqwertyuiopasdfghjklzxcvbnm";
  string ky="128BitKEYATLEAST";
  assert(ky.size()==16) ;
  vector<vector<vector<int>>> pt=make_arr(S1);
  vector<vector<int>> key=strvec(ky,0);
  showstr(pt);
  enc(pt,key);
  showstr(pt);
  dec(pt,key);
  showstr(pt);
}
