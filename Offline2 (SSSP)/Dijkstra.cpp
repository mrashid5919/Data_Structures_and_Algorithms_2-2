#include<bits/stdc++.h>
#include<stdio.h>
#include<string>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

vector<pair<long long,long long> > adj[10000];
long long dist[1000],parent[1000];

void dijkstra(long long n,long long source)
{
    for(long long i=0;i<n;i++)
    {
        dist[i]=INT_MAX;
        parent[i]=-1;
    }
    dist[source]=0;
    set<pair<long long,long long> > st;
    st.insert(make_pair(0,source));
    while(!st.empty())
    {
        long long x=st.begin()->second;
        st.erase(st.begin());
        for(long long i=0;i<adj[x].size();i++)
        {
            long long dif=(adj[x][i]).second;
            long long nxt=(adj[x][i]).first;
            if(dist[x]+dif<dist[nxt])
            {
                st.erase({dist[nxt],nxt});
                dist[nxt]=dist[x]+dif;
                parent[nxt]=x;
                st.insert(make_pair(dist[nxt],nxt));
            }
        }
    }
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
    dijkstra(n,source);
    cout<<"Shortest path cost: "<<dist[dest]<<"\n";
    vector<long long> path;
    long long temp=dest;
    while(temp!=-1)
    {
        path.push_back(temp);
        temp=parent[temp];
    }
    for(long long i=path.size()-1;i>=0;i--)
    {
        if(i!=path.size()-1)
            cout<<"-> ";
        cout<<path[i]<<" ";
    }
    return 0;
}

/*
9 17
0 7 60
7 1 150
4 8 70
6 4 80
5 1 4000
8 0 100000
2 3 200
8 2 1000
0 3 300
3 8 50000
3 7 200
2 5 120
6 3 1500
4 0 90
5 7 50
1 6 100
4 1 90
0 5
*/
