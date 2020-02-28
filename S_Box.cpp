#include<iostream>
#include<time.h>
// #include"bits/stdc++.h"
using namespace std;

void showarr2d(vector<vector<int>> &A)
{
  for(int i=0,len=A.size();i<len;i++)
  {
    for(int j=0,lenj=A[i].size();j<lenj;j++)
    cout<<A[i][j]<<" ";
    cout<<endl;
  }
  cout<<endl;
}
vector<vector<int>> givestate()
{
  vector<vector<int>> s(16,vector<int>(16,0));
  set<int> st;
  int can=rand()%256;
  for(int i=0;i<s.size();i++)
  {
    for(int j=0;j<s[0].size();j++)
    {
      while(st.find(can)!=st.end())
      can=rand()%256;
      s[i][j]=can;
      st.insert(can);
    }
  }
  return s;
}
vector<vector<int>> invstatefunc(vector<vector<int>> &s)
{
  vector<vector<int>> is(16,vector<int>(16,0));
  for(int i=0;i<s.size();i++)
  {
    for(int j=0;j<s[0].size();j++)
    {
      is[(s[i][j]/16)][(s[i][j]%16)]=16*i+j;
    }
  }
  return is;
}
vector<vector<int>> lookup=givestate();
vector<vector<int>> invlookup=invstatefunc(lookup);
pair<int,int> giveindex(char c)
{
  int i,j;
  i=0;
  j=0;
  for(int k=0;k<4;k++)
  {
    if(c&1<<k)
    i+=i*2+1;
    else
    i*=2;
  }
  for(int k=4;k<8;k++)
  {
    if(c&1<<k)
    j+=j*2+1;
    else
    j*=2;
  }
  return {i,j};
}
void sbox(vector<vector<int>> &vec,vector<vector<int>> &state)
{
  for(int i=0;i<vec.size();i++)
  {
    for(int j=0;j<vec[0].size();j++)
    {
      vec[i][j]=state[(vec[i][j]/16)%16][(vec[i][j]%16)];
    }
  }
}
void setkey(vector<vector<int>> &vec,vector<vector<int>> &lookup)
{
  for(int i=0;i<vec.size();i++)
  {
    int j=vec.size()-1;
    vec[i][j]=lookup[vec[i][j]/16][vec[i][j]%16];
  }
}
