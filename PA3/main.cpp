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
    int collisions;
    bool deleted,placed;
    element()
    {   collisions = 0;
        key = -1;
        deleted=false;
        placed=false;
    }
};

int h(int key, int sizeM)
{
    int answer;
    
    answer = key%sizeM;
    
    return answer;
}

int quadHash(int c1, int c2, int i)
{   int ans=  c1*i + c2*i^2;
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
        e.collisions++;
        while(arr[(hvalue+quadHash(c1, c2, e.collisions))%m].key !=-1)
        {
            e.collisions++;
            quadCol++;
        }
        arr[(hvalue+quadHash(c1, c2, e.collisions))%m]=e;
    }
    
}
void insertD (element * arr, element key, int m, int doubCol, int RValue)
{
    int hvalue = h(key.key, m);
    
}

void remove(element e,vector<element> arr, int M, method meth)
{
    for(int i = 0; i<212;i++)
    {
        if(arr[i].key == e.key && arr[i].deleted == false)
        {
            arr[i].deleted = true;
            cout<<arr[i].key<<": HAS BEEN DELETED"<<endl;
        }
    }
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

   // element quadraticHash[211];
    //element doubleHash[211];
    vector<element> quadVec (212, element());
    vector<element> doubVec (212, element());
    
    
    while(file>>controller)
    {   if (!controller.compare("i") || !controller.compare("r"))
        {   int j;
            file>>j;
            element e;
            e.key=j;
            if(!controller.compare("i"))
            {   cout<<"INSERT: "<<e.key<<endl;
                int hvalue = h(e.key, M);
                /*      QUADRATIC METHOD    */
                if (quadVec[hvalue].key == -1) {
                    quadVec[hvalue]=e;
                }
                else
                {
                    while(!e.placed)
                    {   e.collisions++;
                        quadCol++;
                        if(e.collisions>=20)
                        {
                            cout<<e.key<<": has too many collisions using quadratic hashing! "<<e.collisions<<endl;
                            break;
                        }
                        int place = (hvalue+quadHash(c1, c2, e.collisions))%M;
                        if(quadVec[place].key ==-1)
                        {
                            quadVec[place]=e;
                            e.placed = true;
                        }
                    }
                }
                /*      DOUBLE HASHING METHOD       */
                e.collisions = 0;
                e.placed = false;
                if (doubVec[hvalue].key == -1) {
                    doubVec[hvalue] = e;
                }
            }
            if(!controller.compare("r"))
            {   cout<<"REMOVE: "<<e.key<<endl;
                remove(e,quadVec,M,strategy);
            }
        }
        controller.clear();
    }
    for (int i=0; i<211; i++) {
        if (!quadVec[i].deleted) {
            cout<<i<<": "<<quadVec[i].key<<endl;
        }
        else if(quadVec[i].deleted){
            cout<<i<<":DELETED "<<quadVec[i].key<<endl;}
        }
    cout<<"Quadratic Collisions: "<<quadCol<<endl;
    
}
