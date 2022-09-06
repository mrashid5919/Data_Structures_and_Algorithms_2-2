#include<bits/stdc++.h>
#include<stdio.h>
#include<string>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

vector<pair<long long,long long> > adj[10000];
long long dist[1000],parent[1000];

bool bellman(long long n,long long source)
{
    for(long long i=0;i<n;i++)
    {
        dist[i]=INT_MAX;
        parent[i]=-1;
    }
    dist[source]=0;
    for(long long i=0;i<n-1;i++)
    {
        for(long long j=0;j<n;j++)
        {
            for(long long k=0;k<adj[j].size();k++)
            {
                long long dif=adj[j][k].second;
                long long nxt=adj[j][k].first;
                if(dist[j]+dif<dist[nxt])
                {
                    dist[nxt]=dist[j]+dif;
                    parent[nxt]=j;
                }
            }
        }
    }
    for(long long j=0; j<n; j++)
    {
        for(long long k=0; k<adj[j].size(); k++)
        {
            long long dif=adj[j][k].second;
            long long nxt=adj[j][k].first;
            if(dist[j]+dif<dist[nxt])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    fastio;
    //freopen("input.txt","r",stdin);
    long long n,m,u,v,w,source,dest;
    cin>>n>>m;
    for(long long i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        adj[u].push_back(make_pair(v,w));
    }
    cin>>source>>dest;
    if(!bellman(n,source)){
        cout<<"The graph contains a negative cycle\n";
    }
    else
    {
        cout<<"The graph does not contain a negative cycle\n";
        cout<<"Shortest path cost: "<<dist[dest]<<"\n";
        vector<long long> path;
        long long temp=dest;
        while(temp!=-1)
        {
            path.push_back(temp);
            temp=parent[temp];
        }
        for(long long i=path.size()-1; i>=0; i--)
        {
            if(i!=path.size()-1)
                cout<<"-> ";
            cout<<path[i]<<" ";
        }
    }
    return 0;
}

/*
7 7
0 1 2
1 2 3
1 3 4
4 3 2
6 4 -3
5 6 -2
4 5 1
0 2
*/
