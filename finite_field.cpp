#include<iostream>
#include<time.h>
#include <vector>
// #include"bits/stdc++.h"
using namespace std;
//FOR MIS COLUMNS GF(256) MULTIPLICATION AND INVERSE
typedef struct polynomial
{
  int val;
  vector<int> coef;
}poly;
poly givepoly(int N)
{
  poly p;
  p.val=N;
  p.coef=vector<int>();
  int last=-1;
  for(int i=0;i<20;i++)
  {
    if(N&1<<i)
    {
      p.coef.push_back(1);
      last=i;
    }
    else
    p.coef.push_back(0);
  }
  p.coef.erase(p.coef.begin()+last+1,p.coef.end());
  return p;
}
//IRREDUSABLE POLYNOMIAL FOR AES x^8 + x^4 + x^3 + x + 1
poly ired=givepoly(283);
void fixpoly(poly *m)
{
  while(m->coef.size()>0 && m->coef[m->coef.size()-1]==0)
  m->coef.pop_back();
  int mu=1;
  m->val=0;
  for(int i=0;i<m->coef.size();i++,mu*=2)
  {
    m->val+=m->coef[i]*mu;
  }
}
poly copyof(poly *p)
{
  poly p1=givepoly(p->val);
  return p1;
}

//GIVES REMAINDER AFTER DIVISION
poly divrem(poly a,poly b)
{
  poly q;
  poly r=copyof(&a);
  q.coef=vector<int>(17,0);
  for(int i=r.coef.size()-1;i>=b.coef.size()-1;i--)
  {
    if(r.coef[i]==1)
    {
      q.coef[i-(b.coef.size()-1)]++;
      int index=0;
      for(int j=b.coef.size()-1;j>=0;j--)
      {
        index=i+j-(b.coef.size()-1);
        r.coef[index]=(r.coef[index]+b.coef[j])%2;
      }
    }
  }
  fixpoly(&r);
  fixpoly(&q);
  return r;
}
//MULTIPLIES POLYNOMIALS
poly mult(poly a,poly b)
{
  if(a.val==0 || b.val==0)
  return copyof(&a);
  else if(a.val==1)
  return copyof(&b);
  else if(b.val==1)
  return copyof(&a);
  poly m;
  m.coef=vector<int>(16,0);
  int mx=-1;
  for(int i=0;i<a.coef.size();i++)
  {
    for(int j=0;j<b.coef.size();j++)
    {
      if(a.coef[i]==b.coef[j] && a.coef[i]==1)
      {
        m.coef[i+j]=(m.coef[i+j]+1)%2;
      }
    }
  }
  fixpoly(&m);
  if(m.val>=256)
  return divrem(m,ired);
  else
  return m;
}
int mult(int i,int j)
{
  if(i==0 || j==0)
    return 0;
  else if(i==1)
  return j;
  else if(j==1)
  return i;
  poly a=givepoly(i);
  poly b=givepoly(j);
  poly c=mult(a,b);
  return c.val;
}
