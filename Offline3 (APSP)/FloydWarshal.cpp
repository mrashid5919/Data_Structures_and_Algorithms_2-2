#include<bits/stdc++.h>
using namespace std;

const long long INF=10000000000;

void floyd_warshall(long long n,long long adj[][100],long long pr[][100])
{
    for(long long k=1;k<=n;k++)
    {
        for(long long i=1;i<=n;i++)
        {
            for(long long j=1;j<=n;j++)
            {
                if (adj[i][k]<INF && adj[k][j]<INF && adj[i][k]+adj[k][j]<adj[i][j])
                {
                    adj[i][j]=adj[i][k]+adj[k][j];
                    pr[i][j]=pr[k][j];
                }
            }
        }
    }
}

void print_path(long long pr[100][100],long long i,long long j)
{
    if(i==j)
        cout<<i<<" ";
    else if(pr[i][j]==0)
        cout<<"No path from "<<i<<" to "<<j<<" exists";
    else
    {
        print_path(pr,i,pr[i][j]);
        cout<<"->"<<j<<" ";
    }

}

int main()
{
    long long n,m,i,j,u,v,w,adj[100][100],pr[100][100];
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(i==j)
                adj[i][j]=0;
            else
                adj[i][j]=INF;
            pr[i][j]=0;
        }
    }
    for(i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        adj[u][v]=w;
        pr[u][v]=u;
    }
    floyd_warshall(n,adj,pr);
    cout<<"Shortest distance matrix\n";
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(adj[i][j]==INF)
                cout<<"INF ";
            else
                cout<<adj[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"Parent matrix\n";
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(pr[i][j]==0)
                cout<<"N ";
            else
                cout<<pr[i][j]<<" ";
        }
        cout<<"\n";
    }
    long long source, destination;
    cin>>source>>destination;
    print_path(pr,source,destination);
    return 0;
}
