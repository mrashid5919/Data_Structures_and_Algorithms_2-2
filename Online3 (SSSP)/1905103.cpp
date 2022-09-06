#include<bits/stdc++.h>
#include<stdio.h>
#include<string>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

vector<pair<long long,float> > adj[10000];
long long parent[1000];
float dist[1000];

bool bellman(long long n,long long source)
{
    for(long long i=0;i<n;i++)
    {
        dist[i]=0.0;
        parent[i]=-1;
    }
    dist[source]=1.0;
    for(long long i=0;i<n-1;i++)
    {
        for(long long j=0;j<n;j++)
        {
            for(long long k=0;k<adj[j].size();k++)
            {
                float dif=adj[j][k].second;
                long long nxt=adj[j][k].first;
                if(dist[j]*dif>dist[nxt])
                {
                    dist[nxt]=dist[j]*dif;
                    parent[nxt]=j;
                }
            }
        }
    }
    /*for(long long j=0; j<n; j++)
    {
        for(long long k=0; k<adj[j].size(); k++)
        {
            float dif=adj[j][k].second;
            long long nxt=adj[j][k].first;
            if(dist[j]*dif>dist[nxt])
            {
                return false;
            }
        }
    }*/
    return true;
}

int main()
{
    fastio;
    //freopen("input.txt","r",stdin);
    long long n,m,u,v,source,dest;
    float w;
    cin>>n>>m;
    for(long long i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        adj[u].push_back(make_pair(v,w));
    }
    cin>>source>>dest;
    if(!bellman(n,source))
        cout<<"The graph contains a negative cycle\n";
    else
    {
        cout<<"Most reliable path score: "<<dist[dest]<<"\n";
        if(dist[dest]==0.0)
        {
            cout<<"Not reachable";
            return 0;
        }
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
