#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>

using namespace std;

//Main class
class QM
{
public:

int bien;
string dontcares;

QM(int a)
{
   bien=a;
   dontcares.append(a,'-');

}

vector<string> getVars()
{
   vector<string> v;
   string letters[]={"a","b","c","d","e","f","g","h"};
   for(int i=0;i<this->bien;i++)
    v.push_back(letters[i]);

   return v;
}


// vd: 7 = 0111

string decToBin(int n)
{
   if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}


//vd: dua vao 2, 2 =>10 => 0010
string pad(string bin)
{
   int max=bien-bin.length();
   for(int i=0; i<max; i++)
       bin="0"+bin;
   return bin;
}

//vd : 0100 va 0101 =>TRUE
bool isGreyCode(string a,string b)
{
   int flag=0;
   for(int i=0;i<a.length();i++)
   {
       if(a[i]!=b[i])
        flag++;
   }
   return (flag==1);
}


// vd: 0110 va 0111 =>> 011-
string replace_complements(string a,string b)
{
   string temp="";
   for(int i=0;i<a.length();i++)
   if(a[i]!=b[i])
       temp=temp+"-";
   else
       temp=temp+a[i];

   return temp;
}

bool in_vector(vector<string> a,string b)
{
   for(int i=0;i<a.size();i++)
     if(a[i].compare(b)==0)
      return true;
    return false;
}


vector<string> reduce(vector<string> minterms)
{
for (int i=0; i<minterms.size(); i++)
       cout << minterms[i]<<endl;
       cout <<endl;

      vector<string> newminterms;

      int max=minterms.size();
      int* checked = new int[max];
      for(int i=0;i<max;i++)
      {
          for(int j=i;j<max;j++)
          {
               // neu tim thay lien ke nhau va chi co 1 vi tri khac nhau thi dua bit do ve -
               if(isGreyCode(minterms[i],minterms[j]))
               {
                  checked[i]=1;
                  checked[j]=1;
                  if(!in_vector(newminterms,replace_complements(minterms[i],minterms[j])))
                     newminterms.push_back(replace_complements(minterms[i],minterms[j]));
               }
          }
      }

      //dua vo vector moi
      for(int i=0;i<max;i++)
      {
          
          if(checked[i]!=1 && ! in_vector(newminterms,minterms[i]))
           newminterms.push_back(minterms[i]);
      }

       delete[] checked;
   
       return newminterms;
}



// vd: 011- =>> a'bc
string getValue(string a)
{
   string temp="";
   vector<string> vars=this->getVars();
   if(a==dontcares)
     return "1";

   for(int i=0;i<a.length();i++)
   {
     if(a[i]!='-')
     {
        if(a[i]=='0')
         temp=temp+vars[i]+"\'";
        else
         temp=temp+vars[i];
     }
   }
   return temp;
}

//hàm check 2 vector bang nhau
bool VectorsEqual(vector<string> a,vector<string> b)
{
   if(a.size()!=b.size())
      return false;

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i])
        return false;
    }
    return true;
}

};

//hàm chính
int main ()
{
   
      int no;
      cout<<endl<<"Nhap so bien (luu y so luong trong khoang 1-8):	"<<endl;
      cin>>no;
      QM q(no);

      string temp="";
      cout<<"nhap cac minterms (tu=0-"<<pow(2,no)-1<<") duoc phan cach boi dau phay(,)"<<endl;
      cin>>temp;
      vector<string> minterms;
      istringstream f(temp);
      string s;
      while (getline(f, s, ','))
      {
         int t=atoi(s.data());
         minterms.push_back(q.pad(q.decToBin(t)));
      }
      sort(minterms.begin(),minterms.end()); // sap xep theo gia tri tang dan tu minterms dau den minterms cuoi
      do
      {
         minterms=q.reduce(minterms);
         sort(minterms.begin(),minterms.end());
      }while(!q.VectorsEqual(minterms,q.reduce(minterms)));

      int i;
      cout << "Ket qua thu duoc tu thuat toan QM:" << endl;
      for (i=0;i<minterms.size()-1; i++)
          cout <<q.getValue(minterms[i])<<"+";
      cout<<q.getValue(minterms[i])<<endl;  
}
