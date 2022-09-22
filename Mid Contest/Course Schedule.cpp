#include<bits/stdc++.h>
using namespace std;

int count=0,vis[100005]={0},par[100005]={0},flag;
vector<int> adj[100005];
vector<int> ans;

void dfs(int v) {
    vis[v]=1;
    for (int i=0;i<adj[v].size();i++) {
        if (vis[adj[v][i]]==0)
            dfs(adj[v][i]);
        if(vis[adj[v][i]] && par[adj[v][i]]==0)
            flag=1;
    }
    ans.push_back(v);
    par[v]++;
}


int main()
{
    int n,m,i,x,y;
    cin>>n>>m;
    for(i=0;i<m;i++)
    {
        cin>>x>>y;
        adj[x-1].push_back(y-1);
    }
    for (i = 0; i < n; i++) {
        if (vis[i]==0)
            dfs(i);
    }
    if(ans.size()<n || flag==1)
        cout<<"IMPOSSIBLE\n";
    else
    {
        for(i=n-1;i>=0;i--)
            cout<<ans[i]+1<<" ";
        cout<<"\n";
    }
    return 0;
}

