//
//  main.cpp
//  PA3
//
//  Created by Jon Lowrey on 11/2/15.
//  Copyright © 2015 Jon Lowrey. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
enum method{quad,doub};

struct element
{   int key ;
    bool deleted;
    element()
    {
        key = -1;
        deleted=false;
    }
};

int h(int key, int sizeM)
{
    int answer;
    
    answer = key%sizeM;
    
    return answer;
}

int quadHash(int c1, int c2, element e)
{    int i = e.key;
     int ans=  c1*i + c2*i^2;
    return ans;
}
int doubleHash(int R, element e)
{   if(R!=113){ cout<<"PROBLEM IN DOUBLEHASH"<<endl; return 0;}
    int answer = R - e.key%R;
    return answer;
}

void insertQ (vector<element>& arr, element e, int m, int quadCol, int c1, int c2)
{
    int hvalue = h(e.key, m);
    
    if (arr[hvalue].key == -1)
    {
        arr[hvalue] = e;
        
    }
    else
    {   cout<<"COLLISION!"<<endl;
        quadCol++;
        int q = quadHash(c1, c2, e);
        int insert = (hvalue+q)%m;
        if (arr[insert].key == -1)
        {
            arr[insert] = e;
        }
        else
        {
            cout<<"PROBLEM IN INSERTQ!!!!!"<<endl;
            return;
        }
        
    }
    
}
void insertD (element * arr, element key, int m, int doubCol, int RValue)
{
    int hvalue = h(key.key, m);
    
}

void remove(element * arr, element key, int M, method meth)
{   int hvalue = h(key.key, M);
    if(arr[hvalue].key != key.key)

}

/////START MAIN BLOCK

int main(int argc, const char * argv[])
{   int quadCol=0, doubCol=0;
    string controller;
    stringstream str;
    fstream file;
    method strategy;
    file.open("data.txt");
    
int M,R,c1,c2;
if(argc != 5)
{
    cout<<"Incorrect Number of Arguments!"<<endl;
    return 0;
}

for(int i = 1; i <5;i++)
{str.clear();
 str<<argv[i];
    switch (i) {
        case 1:
            str>>M;
            break;
        case 2:
            str>>R;
            break;
        case 3:
            str>>c1;
            break;
        case 4:
            str>>c2;
            break;
        default:
            break;
    }

}
    
    cout<<M<<" "<<R<<" "<<c1<<" "<<c2<<endl;

    element quadraticHash[211];
    element doubleHash[211];
    vector<element> quadVec (211, element());
    vector<element> doubVec (211, element());
    
    cout<<h(R,M)<<endl;
    
    while(file>>controller)
    {   if (!controller.compare("i") || !controller.compare("r"))
        {   int j;
            file>>j;
            element e;
            e.key=j;
            if(!controller.compare("i"))
            {
                insertQ(quadVec, e, M, quadCol,c1,c2);
               // insertD(doubleHash, e, M,doubCol);
            }
        }
        controller.clear();
    }
    for (int i=0; i<211; i++) {
        cout<<i<<": "<<quadVec[i].key<<endl;
    }
    
}
