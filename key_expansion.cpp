#include<iostream>
#include<time.h>
#include "S_Box.cpp"
using namespace std;
/*
 * NESSARY FUNCTION FOR KEY EXPANTION
*/
vector<vector<int>> rcon=
{
  {1,2,4,8,16,32,64,128,27,54},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0}
};
vector<vector<int>> givekey(string S)
{
  vector<vector<int>> vec(4,vector<int>(4,(int)'\0'));
  for(int j=0;j<16 && j<S.size();j++)
  {
    vec[j%4][j/4]=S[j];
  }
  return vec;
}
void rotword(vector<vector<int>> &vec,int j)
{
  int last=vec[0][j];
  for(int i=0;i<3;i++)
  vec[i][j]=vec[i+1][j];
  vec[3][j]=last;
}
void revrotword(vector<vector<int>> &vec,int j)
{
  int first=vec[3][j];
  for(int i=3;i>0;i--)
  vec[i][j]=vec[i-1][j];
  vec[0][j]=first;
}
void AddRoundKey(vector<vector<int>> &A,vector<vector<int>> &key)
{
  for(int i=0;i<A.size();i++)
  {
    for(int j=0;j<A[i].size();j++)
    {
      A[i][j]^=key[i][j];
    }
  }
}
vector<int> givesubkey(vector<vector<int>> &vec)
{
  vector<int> ans(4,0);
  for(int i=0;i<4;i++)
  {
    ans[i]=lookup[vec[i][3]/16][vec[i][3]%16];
  }
  return ans;
}
void keyrev1(vector<vector<int>> &key)
{
  for(int i=0;i<4;i++)
  for(int j=1;j<4;j++)
  key[i][j]^=key[i][0];
}
vector<int> giveinvsubkey(vector<vector<int>> &vec)
{
  vector<int> ans(4,0);
  for(int i=0;i<4;i++)
  {
    ans[i]=invlookup[vec[i][3]/16][vec[i][3]%16];
  }
  return ans;
}
void xorrcon(vector<int> &vec,int round)
{
  for(int i=0;i<4;i++)
  {
    vec[i]=vec[i]^rcon[i][round];
  }
}
void xorfirstcol(vector<vector<int>> &key,vector<int> &subkey)
{
  for(int j=0;j<4;j++)
  subkey[j]=subkey[j]^key[j][0];
}
void setkey(vector<vector<int>> &key,vector<int> &subkey)
{
  for(int i=0;i<4;i++)
  key[i][0]=subkey[i];
  // showarr2d(key);
  for(int i=0;i<4;i++)
  {
    for(int j=1;j<4;j++)
    {
      key[i][j]=key[i][j]^key[i][0];
    }
  }
}
void setkeyrev(vector<vector<int>> &key,vector<int> &subkey)
{
  for(int i=0;i<4;i++)
  {
    key[i][0]=key[i][0]^subkey[i];
  }
}
vector<vector<int>> nextkey(vector<vector<int>> &key,int round)
{
  rotword(key,3);
  vector<int> subkey=givesubkey(key);
  revrotword(key,3);
  xorrcon(subkey,round);
  xorfirstcol(key,subkey);
  setkey(key,subkey);
  return key;
}

vector<vector<int>> befkey(vector<vector<int>> &key,int round)
{
  keyrev1(key);
  rotword(key,3);
  vector<int> subkey=givesubkey(key);
  revrotword(key,3);
  xorrcon(subkey,round);
  setkeyrev(key,subkey);
  return key;
}
