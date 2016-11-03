#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <functional>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtof */
#include <algorithm>

using namespace std;

void split( string& s, char c, vector<string>& v) {
  string::size_type i = 0;
  string::size_type j = s.find(c);
  
  while (j != string::npos) {
    v.push_back(s.substr(i, j-i));
    i = ++j;
    j = s.find(c, j);
    
    if (j == string::npos)
      v.push_back(s.substr(i, s.length()));
  }
}

int main (int argc, char* argv[]) {
  ifstream nr1;
  ifstream nr2;
  string line;
  vector<float> s1;
  vector<float> s2;
  vector<float> s3;
  vector<float> p1;
  vector<float> p2;
  vector<float> p3;

  vector<float> f1;
  vector<float> f2;

  if(argc<3){
    cout << "Usage:\n\tcompose_score <run_data_nr1> <run_data_nr2> > comp.csv\n\n";
    exit(0);
  }
  
  nr1.open (argv[1]);
  while ( getline (nr1,line) ){
    vector<string> v;
    split(line,'\t',v);
    string score = v[3];
    double val1 = atof(score.c_str());
    string pos1 = v[1];
    double val2 = atof(pos1.c_str()); 
    s1.push_back(val1);
    p1.push_back(val2);
  }
  nr1.close();
  
  nr2.open (argv[2]);
  while ( getline (nr2,line) ){
    vector<string> v;
    split(line,'\t',v);
    string score = v[3];
    double val1 = atof(score.c_str());
    string pos2 = v[1];
    double val2 = atof(pos2.c_str()); 
    s2.push_back(val1);
    p2.push_back(val2);
    
  }
  nr2.close();

  int  biggest_p1= *max_element(p1.begin(),p1.end());
  int  biggest_p2= *max_element(p2.begin(),p2.end());
  
  int len1=p1.size();
  int len2=p2.size();
  int dif;
  int i,j;
  //Fill chr with zeroes 
  for(i=0;i<=biggest_p1;i++){
    f1.push_back(0);
  }

  for(i=0;i<=biggest_p2;i++){
    f2.push_back(0);
  }


  for(i=1;i<=len1;i++){
    f1[p1[i]]=s1[i];
  }

  for(i=1;i<=len1;i++){
    f2[p2[i]]=s2[i];
  }
    
  
  for(i=1; i<=biggest_p1 - 20 ;i++){
    for(j=7;j<=20;j++){
      double comp=f1[i]*f2[i+j];
      if(comp >=0.7){
        cout << i << "\t"<< i+j << "\t"<< j<< "\t";    
        cout <<  comp << "\n";
        //s3.push_back(comp);
      }
    }
  }
  //cout << s3.size() <<"\n";
  return 0;
}
