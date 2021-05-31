#include<iostream>
#include<cmath>
#include<bits/stdc++.h>
#include<string.h>
#include<vector>
#define ROWS 2
#define COLS 4
using namespace std;
struct cell{

    int place;
    bool state;
    char binary[5];
    int b;
	int counter=0; 
};

class Kmap_Process{
protected:
int N_minterms;
cell kmap[ROWS][COLS];  
int* array;
string Experssion;
vector<cell>substiute[5];
vector<cell>all;
vector<vector<cell> > implicants;

public:
/* INPUT */
void input(int* array)
{
for (int i = 0 ; i<N_minterms ;i++)
        cin>>array[i];
strcpy(kmap[0][0].binary, "000");
strcpy(kmap[1][0].binary, "100");
strcpy(kmap[0][1].binary, "001");
strcpy(kmap[0][2].binary, "011");
strcpy(kmap[0][3].binary, "010"); 
strcpy(kmap[1][1].binary, "101");
strcpy(kmap[1][2].binary, "111");
strcpy(kmap[1][3].binary, "110"); 
}
/************************** IMPORTANT *************************/
int DEC_BINA( int x)
{
 int h=1, i=0;
    while ( x != 0)
  { int c = 0;
    c = x%2;
    x=x/2;
  i += c*h;
  h*=10;
  }
return i;
}
/*************************** ALGORITHM ************************/
Kmap_Process(){
cout << " Enter the number of minterms"<< endl;
cin >> N_minterms;
 int* array = new int[N_minterms];
cout << " ENTER THE minterms"<< endl;
input(array);
for ( int i = 0 ; i<ROWS; i++)
{
    for (int j = 0 ; j<COLS; j++)
    { kmap[i][j].state = false;
        kmap[i][j].place = 4*i+j;
        int f = DEC_BINA(4*i+j);
        kmap[i][j].b = f;
        int x = 0;
           while (x!= N_minterms){

                if(4*i+j== array[x])
                {kmap[i][j].state=true;
                    break;
                }  
            x++;
            }
    }

}

    swap(kmap[0][3].place,kmap[0][2].place);
    swap(kmap[1][2].place,kmap[1][3].place);
    swap(kmap[0][3].state,kmap[0][2].state);
    swap(kmap[1][2].state,kmap[1][3].state);
    swap(kmap[0][3].b,kmap[0][2].b);
    swap(kmap[1][2].b,kmap[1][3].b);
    cout << " KMAP IS: "<< endl; 
    for ( int i = 0 ; i<ROWS ;i++)
    {
        for ( int j = 0 ; j< COLS ; j++)
        {
            cout << kmap[i][j].state<< " ";
        }
        cout << endl;
    }
cout << "****************************************************" << endl; 
}
/************************************************************/
vector <cell> GetVectorOfMaxSize(vector<cell> V1, vector<cell> V2, vector<cell> V3, vector<cell> V4, vector<cell> V5)
{
int Sizes[5];
Sizes[0] = V1.size();
Sizes[1] = V2.size();
Sizes[2] = V3.size();
Sizes[3] = V4.size();
Sizes[4] = V5.size();

int max = -1;
int a;
for (int i = 0; i < 5; i++)
{
if (Sizes[i] > max)
{
max = Sizes[i];
a = i + 1;
}
}
if (a == 1)
return V1;
if (a == 2)
return V2;
if (a == 3)
return V3;
if (a == 4)
return V4;
if (a == 5)
return V5;
}
/************************************************************/
void generate_KMAP()
{
//memset(Experssion, 0, 100);
if ( N_minterms == 0)
{ cout << "F(ABC) = 0"<< endl;
    return;
}
else if (N_minterms == 8) 
{cout << "F(ABC)= 1"<<endl;
return; 
}
// Trying to get an algorithm to find the all implicants and then remove the duplicates
else
{
for ( int i = 0 ; i<ROWS; i++)
{
    for ( int k = 0 ; k<COLS ; k++)
    {  int c1[5]={0,0,0,0,0};
        if ( kmap[i][k].state == true)
        {       // first prime implicant
                 substiute[0].push_back(kmap[i][k]);
                /** Second PRIME IMPLICANT **/
                c1[0]= substiute[0].size();
               if(kmap[i][(k+1)%COLS].state==true)    
                {substiute[1].push_back(kmap[i][k]);
                substiute[1].push_back(kmap[i][(k+1)%COLS]);
                   c1[1]= substiute[1].size(); }
                /** THIRD PRIME IMPLICANT **/
                if(kmap[(i+1)%ROWS][k].state==true)
                {substiute[2].push_back(kmap[i][k]);
                substiute[2].push_back(kmap[(i+1)%ROWS][k]);
                c1[2]= substiute[2].size();
                }
                /**** Fourth PRIME IMPLICANT ****/
                if(kmap[i][(k+1)%COLS].state==true && kmap[i][(k+2)%COLS].state==true && kmap[i][(k+3)%COLS].state==true)
                {substiute[3].push_back(kmap[i][k]);
                substiute[3].push_back(kmap[i][(k+1)%COLS]);
                substiute[3].push_back(kmap[i][(k+2)%COLS]);
                substiute[3].push_back(kmap[i][(k+3)%COLS]);
                c1[3]=substiute[3].size();
                }
                /*** Fifth Prime IMPLICANT ***/
                if(kmap[i][(k+1)%COLS].state==true && kmap[(i+1)%ROWS][k].state==true && kmap[(i+1)%ROWS][(k+1)%COLS].state==true )
                {
                    substiute[4].push_back(kmap[i][k]);
                    substiute[4].push_back(kmap[(i+1)%ROWS][k]);
                    substiute[4].push_back(kmap[i][(k+1)%COLS]);
                    substiute[4].push_back(kmap[(i+1)%ROWS][(k+1)%COLS]);
                    c1[4]=substiute[4].size();
                }
             all = GetVectorOfMaxSize(substiute[0], substiute[1], substiute[2], substiute[3], substiute[4]);
        implicants.push_back(all);
        substiute[0].clear();
substiute[1].clear();
substiute[2].clear();
substiute[3].clear();
substiute[4].clear();
        }
    }
}
}


/**** Removing the duplicate ****/
int counter =0;
for ( int i = 0 ; i<implicants.size() ; i++)
{
    for(int j = 0; j<implicants.size()-1;j++)
    {   bool flag=false;
         if (i==j)j++;
         if (j==implicants.size()-1)break;

        for ( int k = 0 ; k< implicants[i].size(); k++)
        {

            for (int q=0 ; q<implicants[j].size() ;q++)
            {
           
                if(strcmp(implicants[i][k].binary, implicants[j][q].binary) == 0) flag=true;
            if((k==implicants[i].size()-1)&& strcmp(implicants[i][k].binary, implicants[j][q].binary) == 0){
                implicants[i].clear();
            }
            }
         if (flag==false)break;
          }
    }
    

}

for ( int i = 0 ; i<implicants.size() ; i++)
{
    for(int j = 0; j<implicants.size()-1;j++) {   
         if (i==j)j++;
         if (j==implicants.size()-1)break;

        for ( int k = 0 ; k< implicants[i].size(); k++)
        {

            for (int q=0 ; q<implicants[j].size() ;q++)
            {
           if(strcmp(implicants[i][k].binary, implicants[j][q].binary) == 0)implicants[i][k].counter =implicants[j][q].counter =1;
}
}
}
}

bool f;

for (int i = 0; i < implicants.size(); i++) {
	f= false;
        for (int j = 0; j < implicants[i].size() ; j++){
        if (implicants[i][j].counter!=1)f=true;
    }
    if (f==false)implicants[i].clear();

}

cout << " FOR EXEXCUTION "<< endl; 
for (int i = 0; i < implicants.size(); i++) {
        for (int j = 0; j < implicants[i].size()  ; j++)
            cout << implicants[i][j].binary << " ";
     cout << endl; 

    }
cout << "***********************************"<< endl; 
EXperssion(); 
}

void EXperssion() 
{
    int counter = 0; 
    int k; 
for ( int i = 0 ; i<implicants.size() ; i++)
{   if(implicants[i].size() == 1){
    for ( int r= 0 ; r<3 ; r++)
    
{       
         if (implicants[i][0].binary[r] =='1'){
           Experssion+="(";
           Experssion+=(r+65);
           Experssion+= ")";
            }
           else if ( implicants[i][0].binary[r] == '0')
           {
            Experssion+="(~";
           Experssion+=(r+65);
           Experssion+= ")";
           }
         
        }
        Experssion+= "+";
}

else {
  
     for ( int k = 0 ; k<3 ; k++)
   { counter = 0; 
       for ( int j = 0 ; j<implicants[i].size() &&implicants[i].size()!=0 ;j++)
    {   
        
              
            if (implicants[i][j].binary[k]==implicants[i][j+1].binary[k] && strcmp(implicants[i][j].binary," ")!=0 ) 
            {   
                counter++;
            }

        }
        if ( counter == implicants[i].size()-1 && counter !=0)
    {  

            if (implicants[i][0].binary[k] =='1'){
           Experssion+="(";
           Experssion+=(k+65);
           Experssion+= ")";
            }
           else if ( implicants[i][0].binary[k] == '0')
           {
            Experssion+="(~";
           Experssion+=(k+65);
           Experssion+= ")";
           }
         
        }
         

    }
    if (implicants[i].size() !=0 )
    Experssion += "+";
    }
}
    char ex[100];
    memset(ex,0,100);
    strcpy(ex,Experssion.c_str());
    int w=0; 
        int x= strlen(ex); 
            cout << "F(ABC)= "; 
/*
for ( int i = 0 ; i<(strlen(ex)-1)/2; i++) { if(ex[i]==ex[(strlen(ex)-1)/2 +1+i])w++; 
 } if( w == (strlen(ex)-1)/2) { for ( int i = 0 ; i< (Experssion.length()-1)/2 ; i++) cout<<  ex[i]; cout << endl; exit(1); }
   // cout << w << " == "<< Experssion.length()/2<< endl;*/
    
    if(ex[Experssion.length()-1] == '+')
    {      
        for ( int i = 0 ; i< x-1 ; i++)
        cout << ex[i];
        cout << endl; 
        exit(1);
    }
     
    

    cout << Experssion << endl; 
    
}
};

int main (){
Kmap_Process x;
x.generate_KMAP();
}
