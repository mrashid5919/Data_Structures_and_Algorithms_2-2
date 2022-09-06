#include<bits/stdc++.h>
using namespace std;

const long long INF=10000000000;

long long adj[100][100];

void matrix_multiplication(long long n)
{
    long long temp[100][100];
    for(long long i=1;i<=n;i++)
    {
        for(long long j=1;j<=n;j++)
        {
            temp[i][j]=INF;
            for(long long k=1;k<=n;k++)
            {
                if (adj[i][k]+adj[k][j]<=temp[i][j])
                {
                    temp[i][j]=adj[i][k]+adj[k][j];
                }
            }
        }
    }
    for(long long i=1;i<=n;i++)
    {
        for(long long j=1;j<=n;j++)
            adj[i][j]=temp[i][j];
    }
}

int main()
{
    long long n,m,i,j,u,v,w;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(i==j)
                adj[i][j]=0;
            else
                adj[i][j]=INF;
        }
    }
    for(i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        adj[u][v]=w;
    }
    for(i=1;i<n-1;i*=2)
        matrix_multiplication(n);
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
    return 0;
}

