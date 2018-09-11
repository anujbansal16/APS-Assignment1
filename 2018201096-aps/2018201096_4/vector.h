/***********************************************************

OWNER: 	ANUJ BANSAL
ROLLNO. 2018201096
COPYRIGHT PROTECTED
***********************************************************/
#include<bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
#define rep(i,a,n) for(int i=(a);i<(n);++i)
using namespace std;

#ifndef INC_MODULE2_H
#define INC_MODULE2_H

class Vector
{

public:
    int sizee,capacity,load;
    int *a;
    Vector();
    Vector(int n, int x);
    int size();
    int vector1();
    int vector1(int n, int x);
    int push_back(int x);
    int pop_back();
    int insert(int i,int x);
    int erase(int i);
    int front();
    int back();
    void print();
    void checkCapacityToExpand();
    void createNewArr();
    void shrinkOldArray();
    void checkCapacityToShrink();
    int operator [](int i);
};
Vector:: Vector(){
    load=2;
    sizee=0;
    capacity=1;
    a=new int[capacity];
}

Vector :: Vector(int n, int x){
    load=2;
    sizee=n;
    capacity=n;
    a=new int[n];
    rep(i,0,n)
    a[i]=x;
}

int Vector :: operator [](int i){
    if(i<0||i>=sizee){
        cout<<"Exception : Index Out of Bound\n";
        exit(0);
    }
    return a[i];
}

void Vector:: print(){
    rep(i,0,sizee)
        cout<<a[i]<<" ";
    cout<<"size="<<sizee<<" "<<"cap="<<capacity<<endl;
}

int Vector:: size(){

    return sizee;
}

int Vector:: push_back(int x){
    checkCapacityToExpand();
    a[sizee]=x;
    sizee++;
    return 1;
}
int Vector:: pop_back(){
    if(sizee==0){
        cout<<"Vector is empty\n";
        exit(0);
    }
    checkCapacityToShrink();
    int temp=a[--sizee];
    return temp;

}
int Vector:: insert(int i, int x){
    if(i<0||i>sizee){
        cout<<"Exception : Index Out of Bound\n";
        exit(0);
    }
    checkCapacityToExpand();
    for(int j=sizee-1;j>=i;j--)
        a[j+1]=a[j];
    a[i]=x;
    sizee++;
    return 1;
}   
int Vector:: erase(int i){
    if(sizee==0){
        cout<<"Vector is empty\n";
        exit(0);
    }

    if(i<0||i>=sizee){
        cout<<"Exception : Index Out of Bound\n";
        exit(0);
    }
    checkCapacityToShrink();
    int temp=a[i];
    for(int j=i+1;j<sizee;j++)
        a[j-1]=a[j];
    sizee--;
    return temp;
}
int Vector:: front(){
    if(sizee==0){
        cout<<"Vector is empty\n";
        exit(0);
    }
    return a[0];      
}
int Vector:: back(){
    if(sizee==0){
        cout<<"Vector is empty\n";
        exit(0);
    }
    return a[sizee-1];      
}
void Vector::checkCapacityToExpand(){
    if(sizee+1>capacity*0.75)
        createNewArr();
}
void Vector::checkCapacityToShrink(){
    if(sizee-1<capacity/load)
       shrinkOldArray();
}
void Vector::createNewArr(){
    capacity=load*capacity;
    int *temp=new int[capacity];
    rep(i,0,sizee){
        temp[i]=a[i];
    }
    delete[] a;
    a=temp;
}
void Vector::shrinkOldArray(){
    capacity=capacity/load;
    int *temp=new int[capacity];
    rep(i,0,sizee){
        temp[i]=a[i];
    }
    delete[] a;
    a=temp;
}


#endif