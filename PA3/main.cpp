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
#include <cmath>
#include <vector>

using namespace std;
enum method{quad,doub,line};

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
{   int ans=  c1*i + c2*pow(i, 2);
    return ans;
}
int doubleHash(int R, element e)
{   if(R!=113){ cout<<"PROBLEM IN DOUBLEHASH"<<endl; return 0;}
    int answer = R - e.key%R;
    return answer;
}


void remove(element e,vector<element>& arr, int M, method meth)
{   /*
     Assignment Outline did not detail design of remove function.
     For Real World Use remove function would take hashing method into account to search for variables then delete.
     With M=211 this method is sufficient.
     */
    for(int i = 0; i<212;i++)
    {
        if(arr[i].key == e.key && arr[i].deleted == false)
        {
            arr[i].deleted = true;
          //  cout<<arr[i].key<<": HAS BEEN DELETED"<<endl; DEBUG
        }
    }
}

/////START MAIN BLOCK

int main(int argc, const char * argv[])
{   int quadCol=0, doubCol=0, probes = 0;
    string controller;
    stringstream str;
    fstream file;
    method strategy=line;
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
    vector<element> quadVec (M, element());
    vector<element> doubVec (M, element());
    
    
    while(file>>controller)
    {   if (!controller.compare("i") || !controller.compare("r"))
        {   int j;
            file>>j;
            element e;
            e.key=j;
            if(!controller.compare("i"))
            {   //cout<<"INSERT: "<<e.key<<endl; DEBUG
                int hvalue = h(e.key, M);
                
                if (c1 || c2)
                {   strategy = quad;
                    
                //    cout<<"QUADRATIC METHOD"<<endl;
                        /*      QUADRATIC METHOD    */
                        if (quadVec[hvalue].key == -1) {
                            quadVec[hvalue]=e;
                            probes++;
                        }
                        else
                        {
                            while(!e.placed)
                            {   e.collisions++;
                                probes++;
                                quadCol++;
                                if(e.collisions>=211)
                                {
                                    cout<<e.key<<": has too many collisions! "<<e.collisions<<endl;
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
                }
                
if (R) {    /*      DOUBLE HASHING METHOD       */
    strategy = doub;
    //cout<<"DOUBLE HASH METHOD"<<endl;
                e.collisions = 0;
                e.placed = false;
                if (doubVec[hvalue].key == -1) {
                    doubVec[hvalue] = e;
                    e.placed=true;
                    probes++;
                }
                else
                {
                    while (!e.placed) {
                        e.collisions++;
                        probes++;
                        doubCol++;
                        if(e.collisions>=211)
                        {
                            cout<<e.key<<": has too many collisions! "<<e.collisions<<endl;
                            break;
                        }
                        int place = (e.collisions*doubleHash(R, e)+hvalue)%M;
                        if (doubVec[place].key==-1) {
                            doubVec[place]=e;
                            e.placed =true;
                        }
                    }
                
                }
            }
            }
            if(!controller.compare("r"))
            {   //cout<<"REMOVE: "<<e.key<<endl; DEBUG
                if(strategy==quad){
                    remove(e,quadVec,M,strategy);}
                if(strategy==doub){
                    remove(e,doubVec,M,strategy);}
            }
        }
        controller.clear();
    }
    /* DEBUG PRINT STATEMENT
    for (int i=0; i<211; i++)
    {
        if (!doubVec[i].deleted)
        {
            cout<<i<<": "<<doubVec[i].key<<endl;
        }
        if(doubVec[i].deleted)
        {
            cout<<i<<":DELETED "<<doubVec[i].key<<endl;
        }
    }*/
    cout<<"Quadratic Collisions: "<<quadCol<<" Probes: "<<probes<<" Double Collisons: "<<doubCol<<endl;
    
    }
