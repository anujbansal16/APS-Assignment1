#include<bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
#define rep(i,a,n) for(int i=(a);i<(n);++i)
using namespace std;
typedef long  l;
l leftC(l p){
    return 2*p+1;
}
l parent(l c){
    return (c-1)/2;
}
l rightC(l p){
    return 2*p+2;   
}
void maxHeapify(l a[],l n,l i){
    l left=leftC(i);
    l right=rightC(i);
    l max=i;
    if(left<n&&a[left]>a[i])
        max=left;
    if(right<n&&a[max]<a[right])
        max=right;
    if(max!=i){
        swap(a[i],a[max]);
        maxHeapify(a,n,max);
    }
}
void minHeapify(l b[],l n,l i){
    l left=leftC(i);
    l right=rightC(i);
    l min=i;
    if(left<n&&b[left]<b[i])
        min=left;
    if(right<n&&b[min]>b[right])
        min=right;
    if(min!=i){
        swap(b[i],b[min]);
        minHeapify(b,n,min);
    }
}
void insertMax(l a[],l n){
    if(n!=0){
        l p=parent(n);
        while(a[p]<a[n]&&p>=0){
            swap(a[p],a[n]);
            n=p;
            p=parent(n);
        }
    }
}
void insertMin(l b[],l n){
    if(n!=0){
        l p=parent(n);
        while(b[p]>b[n]&&p>=0){
            swap(b[p],b[n]);
            n=p;
            p=parent(n);
        }
    }
}
void printA(l a[], l n){
    for (l i = 0; i < n; i++)
        cout<<a[i]<<" ";
}
int main() {
    l n,temp;
    cin>>n;
    l a[n],b[n],x=0,y=0,median=0;
    for (l i = 0; i < n; i++){
        cin>>temp;
        if(x==y){
            if(temp>median){
                // cout<<"If a";
                b[y]=temp;
                insertMin(b,y);
                y++;
                median=b[0];
                // printf("\n");
                //
            }
            else{
                //left
                a[x]=temp;
                insertMax(a,x);
                x++;
                median=a[0];
            }
            
        }
        else{
            if(temp<median){
                if((x+1)==y){
                    a[x]=temp;
                    insertMax(a,x);
                    x++;
                    median=a[0];
                }
                else{
                    b[y]=a[0];
                    insertMin(b,y);
                    y++;

                    median=b[0];
                    swap(a[0],a[x-1]);
                    x--;
                    maxHeapify(a,x,0);
                    a[x]=temp;
                    insertMax(a,x);
                    x++;
                }    
            }
            else{
                if((y+1)==x){
                    b[y]=temp;
                    insertMin(b,y);
                    y++;
                    median=b[0];
                }
                else{
                    // cout<<"here";
                    a[x]=b[0];
                    // cout<<"x="<<x;
                    insertMax(a,x);
                    x++;

                    median=a[0];
                    swap(b[0],b[y-1]);
                    y--;
                    minHeapify(b,y,0);
                    b[y]=temp;
                    insertMin(b,y);
                    y++;
                }    

            }
        }
        if(i%2){
            printf("%0.1f\n",(a[0]+b[0])/2.0 );
        }
        else{
            printf("%0.1f\n",median*1.0 );
        }
        
    }
    return 0;
}