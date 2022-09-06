#include<bits/stdc++.h>
#include<stdio.h>
#include "RedBlackTree.h"
using namespace std;

int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int n,e,x;
    cin>>n;
    cout<<n<<"\n";
    RedBlackTree<int> rbTree;
    while(n--)
    {
        cin>>e>>x;
        cout<<e<<" "<<x<<" ";
        if(e==0)
        {
            bool res=rbTree.del(x);
            if(res)
                cout<<1<<"\n";
            else
                cout<<0<<"\n";
        }
        else if(e==1)
        {
            bool res=rbTree.ins(x);
                if(res)
                    cout<<1<<"\n";
                else
                    cout<<0<<"\n";
        }
        else if(e==2)
        {
            bool res=rbTree.search(x);
            if(res)
                cout<<1<<"\n";
            else
                cout<<0<<"\n";
        }
        else
        {
            cout<<rbTree.cnt(x)<<"\n";
        }
    }
    return 0;
}