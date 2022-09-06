#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

vector<pair<float, pair<int,int> > > adj;
vector<pair<int,int> > krp;
int parent[1000];
float kw,pw;


const float INF = 100000.00;

struct Edge {
    int to = -1;
    float w=INF;
    bool operator<(Edge const& other) const {
        return make_pair(w, to) < make_pair(other.w, other.to);
    }
};

vector<Edge> adj2[1000];
vector<pair<int,int> > prp;

int find_set(int i)
{
    if(i==parent[i])
        return i;
    else
        return find_set(parent[i]);
}

void union_set(int u,int v)
{
    parent[u]=parent[v];
}

void krus(int n)
{
    for(int i=0;i<n;i++)
        parent[i]=i;
    sort(adj.begin(),adj.end());
    for(int i=0;i<adj.size();i++)
    {
        int a=find_set(adj[i].second.first);
        int b=find_set(adj[i].second.second);
        if(a!=b)
        {
            krp.push_back(adj[i].second);
            kw=kw+adj[i].first;
            union_set(a,b);
        }
    }
}

void prim(int n) {
    vector<Edge> minEdge(n);
    minEdge[0].w = 0.0;
    set<Edge> q;
    Edge temp;
    temp.to=0;
    temp.w=0.0;
    q.insert(temp);
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++) {

        int v = q.begin()->to;
        vis[v] = true;
        pw += q.begin()->w;
        q.erase(q.begin());

        if (minEdge[v].to != -1)
            prp.push_back(make_pair(minEdge[v].to,v));
            //cout << min_e[v].to << " " << v << endl;

        for (Edge e : adj2[v]) {
            if (vis[e.to]==false && e.w < minEdge[e.to].w) {
                Edge tmp;
                tmp.to=e.to;
                tmp.w=minEdge[e.to].w;
                q.erase(tmp);
                tmp.to=v;
                tmp.w=e.w;
                minEdge[e.to] = tmp;
                tmp.w=e.w; tmp.to=e.to;
                q.insert(tmp);
            }
        }
    }
}


int main()
{
    freopen("mst.in","r",stdin);
    int v,e,x,y;
    float wt;
    cin>>v>>e;
    for(int i=0;i<e;i++)
    {
        cin>>x>>y>>wt;
        adj.push_back(make_pair(wt,make_pair(x,y)));
        adj.push_back(make_pair(wt,make_pair(y,x)));
        Edge temp1;
        temp1.to=y;
        temp1.w=wt;
        adj2[x].push_back(temp1);
        temp1.to=x;
        adj2[y].push_back(temp1);
    }
    krus(v);
    prim(v);
    cout<<"Cost of the minimum spanning tree : "<<setprecision(6)<<min(kw,pw)<<"\n";
    cout<<"List of edges selected by Prim's : ";
    cout<<"{";
    for(int i=0;i<prp.size();i++){
        if(i!=0)
            cout<<",";
        cout<<"("<<prp[i].first<<","<<prp[i].second<<")";
    }
    cout<<"}\n";
    cout<<"List of edges selected by Kruskal's : ";
    cout<<"{";
    for(int i=0;i<krp.size();i++){
        if(i!=0)
            cout<<",";
        cout<<"("<<krp[i].first<<","<<krp[i].second<<")";
    }
    cout<<"}\n";
    return 0;
}
