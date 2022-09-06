#include<bits/stdc++.h>
#include<string>
using namespace std;

vector<int> adj[100005];
int ara[100005],occ[10][100005],cnt[10];
queue<int> q;

void BFS(int source,vector<bool> &visited,vector<int> &distance,vector<int> &parent)
{
        q.push(source);
        visited[source]=true;
        distance[source]=0;
        parent[source]=-1;
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=adj[u].size()-1;i>=0;i--)
            {
                if(visited[adj[u][i]]==false)
                {
                    visited[adj[u][i]]=true;
                    q.push(adj[u][i]);
                    parent[adj[u][i]]=u;
                    distance[adj[u][i]]=distance[u]+1;
                    /*if(distance[adj[u][i]]==0)
                        distance[adj[u][i]]=distance[u]+1;
                    else
                        distance[adj[u][i]]=min(distance[adj[u][i]],distance[u]+1);*/
                }
            }
        }
}


int main()
{
    int n,i;
    string s;
    cin>>s;
    n=s.size();
    vector<bool> visited(n+1);
    vector<int> distance(n+1);
    vector<int> parent(n+1);
    for(i=0;i<n;i++)
    {
        distance.push_back(0);
        if(i>0)
            adj[i].push_back(i-1);
        if(i<n-1)
            adj[i].push_back(i+1);
        int y=s[i]-'0';
        occ[y][cnt[y]]=i;
        for(int j=0;j<cnt[y];j++)
        {
            adj[occ[y][j]].push_back(i);
        }
        cnt[y]++;
    }
    BFS(0,visited,distance,parent);
    cout<<distance[n-1]<<"\n";
    return 0;
}
