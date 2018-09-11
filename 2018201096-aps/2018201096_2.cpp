#include<bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
#define CCLR(a) memset(a,'0',sizeof(a))
using namespace std;
typedef long  l;
typedef struct Node Node;
struct Node
{
    l value;
    l height;
    Node *left;
    Node *right;
    l count;

};
void inorder(Node *root){
    if(root!=NULL){
    inorder(root->left);
    cout<<root->value<<" "<<root->height<<"\n";
    inorder(root->right);
    }

}
void preorder(Node *root){
    if(root!=NULL){
    cout<<root->value<<" "<<root->height<<" "<<root->count<<"\n";
    preorder(root->left);
    preorder(root->right);
    }

}
Node * newNode(l value){
    Node* newN=(Node *)malloc(sizeof(Node));
    newN->value=value;
    newN->left=NULL;
    newN->right=NULL;
    newN->height=1;
    newN->count=1;
    return newN;
}

Node * LL(Node *root){
    Node *leftN=root->left;
    Node *leftNRight=leftN->right;

    leftN->right=root;
    root->left=leftNRight;

    root->height=1+max(root->left==NULL?0:root->left->height,root->right==NULL?0:root->right->height);
    root->count=(root->left==NULL?0:root->left->count)+(root->right==NULL?0:root->right->count)+1;
    leftN->height=1+max(leftN->left==NULL?0:leftN->left->height,leftN->right==NULL?0:leftN->right->height);
    leftN->count=(leftN->left==NULL?0:leftN->left->count)+(leftN->right==NULL?0:leftN->right->count)+1;
    return leftN;
}
Node * RR(Node *root){
    Node *rightN=root->right;
    Node *rightNLeft=rightN->left;

    rightN->left=root;
    root->right=rightNLeft;

    root->height=1+max(root->left==NULL?0:root->left->height,root->right==NULL?0:root->right->height);
    root->count=(root->left==NULL?0:root->left->count)+(root->right==NULL?0:root->right->count)+1;
    rightN->height=1+max(rightN->left==NULL?0:rightN->left->height,rightN->right==NULL?0:rightN->right->height);
    rightN->count=(rightN->left==NULL?0:rightN->left->count)+(rightN->right==NULL?0:rightN->right->count)+1;
    return rightN;
}

Node * insert(Node *root,l value){
    if(root==NULL){
         return newNode(value);
    }
    else if(value>root->value){
        root->right=insert(root->right,value);
    }
    else if(value<root->value){
        root->left=insert(root->left,value);
    }
    root->height=1+max(root->left==NULL?0:root->left->height,root->right==NULL?0:root->right->height);
    root->count=(root->left==NULL?0:root->left->count)+(root->right==NULL?0:root->right->count)+1;

    l bf=(root->left==NULL?0:root->left->height)-(root->right==NULL?0:root->right->height);
    if(bf>1){
        //LL or LR
        if(value>root->left->value){
            //LR
            root->left=RR(root->left);
            return LL(root);
        }
        else if(value<root->left->value){
            return LL(root);
        }
    }
    else if(bf<-1){
        //RR or RLs
        if(value<root->right->value){
            root->right=LL(root->right);
            return RR(root);
        }
        else if(value>root->right->value){
            return RR(root);
        }
        
    }
    return root;
}

l search(Node *root,l x){
    if(root==NULL)
        return 0;
    if(root->value==x){
        return 1;
    }
    else if(x<root->value)
        return search(root->left,x);
    else
        return search(root->right,x);
}

l countNodes(Node * root){
    if(root==NULL)
        return 0;
    else{
        root->count=countNodes(root->left)+countNodes(root->right)+1;
        return root->count;
    }

}

Node * XthSmallest(Node * root, l x){
    // cout<<"root= "<<root->value<<" "<<x<<"\n";
    if(root->left==NULL&&root->right==NULL)
        return root;
    if(root->left==NULL){
        if(root->count-1==x)
            return root;
        return XthSmallest(root->right,x-root->right->count-1);
    }
    else if(x==root->left->count+1)
        return root;
    else if(x<=root->left->count){
        return XthSmallest(root->left,x);
    }
    else{
        return XthSmallest(root->right,x-root->left->count-1);
    }

}

Node * inorderSucces(Node *root)
{
    struct Node* temp = root;
    while (temp->left!= NULL){
        temp=temp->left;
    }
    return temp;
}

struct Node* deleteNode(struct Node* root, l value)
{
    if (root == NULL)
        return root;
    if ( value < root->value )
        root->left = deleteNode(root->left, value);
    else if( value > root->value )
        root->right = deleteNode(root->right, value);
    else{
        struct Node *leftOrRight;
        //1 or 0 childs simply copy the value
        if((root->left==NULL)||(root->right == NULL))
        {   
            leftOrRight=root->left?root->left:root->right;
            if (leftOrRight == NULL){
                leftOrRight = root;
                root = NULL;
            }
            else
             *root = *leftOrRight;
            free(leftOrRight);
        }
        else
        {   //2 childs
            leftOrRight = inorderSucces(root->right);
            root->value = leftOrRight->value;
            root->right = deleteNode(root->right,leftOrRight->value);//delete succsssor
        }
    }
    if (root == NULL)
      return root;
    root->height=1+max(root->left==NULL?0:root->left->height,root->right==NULL?0:root->right->height);
    root->count=(root->left==NULL?0:root->left->count)+(root->right==NULL?0:root->right->count)+1;
    l bf=(root->left==NULL?0:root->left->height)-(root->right==NULL?0:root->right->height);
    if(bf>1){
        //LL or LR
        l bf1=(root->left->left==NULL?0:root->left->left->height)-(root->left->right==NULL?0:root->left->right->height);
        if(bf1<0){
            //LR
            root->left=RR(root->left);
            return LL(root);
        }
        else{
            return LL(root);
        }
    }
    else if(bf<-1){
        //RR or RLs
        l bf2=(root->right->left==NULL?0:root->right->left->height)-(root->right->right==NULL?0:root->right->right->height);
        if(bf2>0){
            root->right=LL(root->right);
            return RR(root);
        }
        else{
            return RR(root);
        }
        
    }
    return root;
}

int main() {

    l n,m,num;
    cin>>n>>m;
    Node *root=NULL;
    for(l i=0;i<n;i++){
        cin>>num;
        root=insert(root,num);
    }
    while(m--){
        l temp;
        cin>>num>>temp;
        
        switch(num){
            case 1:
                root=insert(root,temp);
                break;
            case 2:
                cout<<search(root,temp)<<"\n";
                break;
            case 3:
                // countNodes(root);        
                Node * xTh=XthSmallest(root,temp);
                cout<<xTh->value<<"\n";
             root=deleteNode(root,xTh->value);            
                break;
        }
         

    }

    return 0;
}