#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<int,char>m{{97,'W'},{98,'O'},{99,'G'},{100,'R'},{101,'B'},{102,'Y'}};
ll solvedhash,unsolvedhash;
map<ll,string>checkdfs;
vector<string>ans;int anssize=15;
void solvedcube(vector<char>&v){
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            v[4*i+j]=i+'a';
        }
    }
}
vector<char>w(24),ww(24);
void printcube(vector<char>&v){
    int e=0;
    for(int i=0;i<3;i++){
        if(i==2)e=20;
        for(int j=0;j<2;j++){
          if(i%2&&j)e-=6;
          for(int k=0;k<4;k++){
            for(int l=0;l<2;l++){
              int x=e+k*2*(i%2);
              if(k==1||i%2){cout<<m[v[x]]<<" ";e++;}
              else cout<<"  ";
              
            }
          }cout<<endl;
        }
    }
}
void frotatecw(int j,vector<char>&v){
  char temp=v[j];
  v[j]=v[j+2],v[j+2]=v[j+3],v[j+3]=v[j+1],v[j+1]=temp;
}void frotateccw(int j,vector<char>&v){
  char temp=v[j];
  v[j]=v[j+1],v[j+1]=v[j+3],v[j+3]=v[j+2],v[j+2]=temp;
}
void u(vector<char>&v){
  frotatecw(0,v);char temp1=v[4],temp2=v[5];
  v[4]=v[8],v[5]=v[9],v[8]=v[12],v[9]=v[13];
  v[12]=v[16],v[13]=v[17],v[16]=temp1,v[17]=temp2;
}void l(vector<char>&v){
  frotatecw(4,v);char temp1=v[0],temp2=v[2];
  v[0]=v[19],v[2]=v[17],v[17]=v[22],v[19]=v[20];
  v[20]=v[8],v[22]=v[10],v[8]=temp1,v[10]=temp2;
}void f(vector<char>&v){
  frotatecw(8,v);char temp1=v[2],temp2=v[3];
  v[2]=v[7],v[3]=v[5],v[5]=v[20],v[7]=v[21];
  v[20]=v[14],v[21]=v[12],v[12]=temp1,v[14]=temp2;
}void r(vector<char>&v){
  frotatecw(12,v);char temp1=v[1],temp2=v[3];
  v[1]=v[9],v[3]=v[11],v[9]=v[21],v[11]=v[23];
  v[21]=v[18],v[23]=v[16],v[18]=temp1,v[16]=temp2;
}void b(vector<char>&v){
  frotatecw(16,v);char temp1=v[0],temp2=v[1];
  v[0]=v[13],v[1]=v[15],v[13]=v[23],v[15]=v[22];
  v[22]=v[4],v[23]=v[6],v[6]=temp1,v[4]=temp2;
}void d(vector<char>&v){
  frotatecw(20,v);char temp1=v[6],temp2=v[7];
  v[6]=v[18],v[7]=v[19],v[18]=v[14],v[19]=v[15];
  v[14]=v[10],v[15]=v[11],v[10]=temp1,v[11]=temp2;
}

void uprime(vector<char>&v){
  frotateccw(0,v);char temp1=v[4],temp2=v[5];
  v[4]=v[16],v[5]=v[17],v[16]=v[12],v[17]=v[13];
  v[12]=v[8],v[13]=v[9],v[8]=temp1,v[9]=temp2;
}void lprime(vector<char>&v){
  frotateccw(4,v);char temp1=v[0],temp2=v[2];
  v[0]=v[8],v[2]=v[10],v[8]=v[20],v[10]=v[22];
  v[20]=v[19],v[22]=v[17],v[19]=temp1,v[17]=temp2;
}void fprime(vector<char>&v){
  frotateccw(8,v);char temp1=v[2],temp2=v[3];
  v[2]=v[12],v[3]=v[14],v[12]=v[21],v[14]=v[20];
  v[20]=v[5],v[21]=v[7],v[7]=temp1,v[5]=temp2;
}void rprime(vector<char>&v){
  frotateccw(12,v);char temp1=v[1],temp2=v[3];
  v[1]=v[18],v[3]=v[16],v[16]=v[23],v[18]=v[21];
  v[21]=v[9],v[23]=v[11],v[9]=temp1,v[11]=temp2;
}void bprime(vector<char>&v){
  frotateccw(16,v);char temp1=v[0],temp2=v[1];
  v[0]=v[6],v[1]=v[4],v[4]=v[22],v[6]=v[23];
  v[22]=v[15],v[23]=v[13],v[13]=temp1,v[15]=temp2;
}void dprime(vector<char>&v){
  frotateccw(20,v);char temp1=v[6],temp2=v[7];
  v[6]=v[10],v[7]=v[11],v[10]=v[14],v[11]=v[15];
  v[14]=v[18],v[15]=v[19],v[18]=temp1,v[19]=temp2;
}

ll e=0,ee=0;
vector<pair<pair<void(*)(vector<char>&),void(*)(vector<char>&)>,pair<char,char>>>moves={
  {{u,uprime},{'U','u'}},{{l,lprime},{'L','l'}},{{f,fprime},{'F','f'}},
  {{r,rprime},{'R','r'}},{{b,bprime},{'B','b'}},{{d,dprime},{'D','d'}}
};
char opp[82][2] = {};
ll hashCube(vector<char>&v) {
    ll b=6,h=0;
    for(int i=0;i<24;i++){
      h=h*b+(v[i]-'a');
    }return h;
}
set<ll>se;
string solvebydfs(vector<char>&v,string s){
  ee++;
  int x=s.size();
  ll a=hashCube(v);
  se.insert(a);
  if(a==solvedhash){
      anssize=min(x,anssize);
      ans.push_back(s);return "";
  }
  if(checkdfs.find(a)!=checkdfs.end()){
    string t=s+checkdfs[a];
    int tt=t.size();
    anssize=min(tt,anssize);
    ans.push_back(t);return "";
  }
  if(x>=7)return "";
  for(auto y:moves){
    char a=y.second.first,b=y.second.second;
    if((x<=1||s[x-2]!=s[x-1]||s[x-1]!=a)&&(!x||(x&&s[x-1]!=b))){
      if(!x||!opp[a][0]||(opp[a][1]!=s[x-1]&&opp[a][0]!=s[x-1])){
          y.first.first(v);
          string s1=solvebydfs(v,s+a);
          if(!s1.empty())return s1;
          y.first.second(v);
      }
    }
    if((!x||(s[x-1]!=a&&s[x-1]!=b))){
      if(!x||!opp[a][0]||(opp[a][1]!=s[x-1]&&opp[a][0]!=s[x-1])){
          y.first.second(v);
          string s1=solvebydfs(v,s+b);
          if(!s1.empty())return s1;
          y.first.first(v);
      }
    }
  }
  return "";
}string solvebydfsrev(vector<char>&v,string s){
  ee++;
  int x=s.size();
  ll a=hashCube(v);
  se.insert(a);
  if(a==unsolvedhash){
      anssize=min(x,anssize);
      ans.push_back(s);return "";
  }
  checkdfs[a]=s;
  if(x>=7)return "";
  for(auto y:moves){
    char a=y.second.first,b=y.second.second;
    if((x<=1||s[1]!=s[0]||s[0]!=a)&&(!x||(x&&s[0]!=b))){
      if(!x||!opp[a][0]||(opp[a][1]!=s[0]&&opp[a][0]!=s[0])){
          y.first.second(v);
          string s1=solvebydfsrev(v,a+s);
          if(!s1.empty())return s1;
          y.first.first(v);
      }
    }
    if((!x||(s[0]!=a&&s[0]!=b))){
      if(!x||!opp[a][0]||(opp[a][1]!=s[0]&&opp[a][0]!=s[0])){
          y.first.first(v);
          string s1=solvebydfsrev(v,b+s);
          if(!s1.empty())return s1;
          y.first.second(v);
      }
    }
  }
  return "";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<char>v(24),uu(24);
    opp['L'][0]='R';opp['L'][1]='r';opp['F'][0]='B';
    opp['F'][1]='b';opp['U'][0]='D';opp['U'][1]='d';
    opp['R'][0]='L';opp['R'][1]='l';opp['B'][0]='F';
    opp['B'][1]='f';opp['D'][0]='U';opp['D'][1]='u';
    solvedcube(v);
    solvedcube(w);
    
    // write your sequences of moves here
    r(v);u(v);rprime(v);uprime(v);
    rprime(v);f(v);r(v);r(v);
    uprime(v);rprime(v);uprime(v);
    r(v);u(v);rprime(v);fprime(v);
    //For above pattern minimum 13 moves are required
    
    cout<<"Your initial cube:\n";
    printcube(v);
    ww=v;uu=w;
    solvedhash=hashCube(w);
    unsolvedhash=hashCube(v);
    solvebydfsrev(uu,"");solvebydfs(v,"");
    cout<<"Number of times dfs called: "<<ee<<endl;
    cout<<"Number of states searched: "<<se.size()<<endl;
    if(ans.size()!=0){
        if(anssize!=1)cout<<"Cube can be solved in minimum "<<anssize<<" moves.\n";
        else cout<<"Cube can be solved in minimum "<<anssize<<" move.\n";
        cout<<"Your solutions:\n";
        for(auto x:ans)if(x.size()==anssize)cout<<x<<endl;
    }
    else cout<<"No solution found!!"<<endl;
    return 0;
}
