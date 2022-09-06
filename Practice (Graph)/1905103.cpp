#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100];
vector<pair<int,int> > vect;
int visited[100],start[100],en[100],tim;
vector<int> temp;

void revDFS(int x)
{
    visited[x]=1;
    temp.push_back(x+1);
    start[x]=++tim;
    if(temp.size()==2)
        cout<<temp[0]<<" "<<temp[1]<<" ";
    else if(temp.size()>2)
        cout<<x+1<<" ";
    for(int i=0;i<adj[x].size();i++)
    {
        if(visited[adj[x][i]]==0)
            revDFS(adj[x][i]);
    }
    en[x]=++tim;
}

void DFS(int x)
{
    visited[x]=1;
    start[x]=++tim;
    for(int i=0;i<adj[x].size();i++)
    {
        if(visited[adj[x][i]]==0)
            DFS(adj[x][i]);
    }
    en[x]=++tim;
}

int main()
{
    int n,e,i,j,a,b,p[100],q[100];
    cin>>n;
    cin>>e;
    for(i=0;i<e;i++)
    {
        cin>>a>>b;
        p[i]=a-1;
        q[i]=b-1;
        adj[a-1].push_back(b-1);
        //rev[b-1].push_back(a-1);
    }
    for(i=0;i<n;i++)
    {
        if(visited[i]==0)
        {
            DFS(i);
        }
    }
    for(i=0;i<n;i++){
        vect.push_back(make_pair(en[i],i));
        visited[i]=0;
    }
    sort(vect.begin(),vect.end());
    for(i=0;i<n;i++)
        adj[i].clear();
    for(i=0;i<e;i++)
    {
        adj[q[i]].push_back(p[i]);
    }
    for(i=n-1;i>=0;i--)
    {
        if(visited[vect[i].second]==0)
            revDFS(vect[i].second);
        if(temp.size()>1)
            cout<<"\n";
        temp.clear();
    }
    /*cout<<"\n";
    for(i=0;i<n;i++)
    {
        cout<<i+1<<" "<<start[i]<<" "<<en[i]<<"\n";
    }*/
    return 0;
}
