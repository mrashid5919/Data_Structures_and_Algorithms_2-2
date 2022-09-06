#include<bits/stdc++.h>
using namespace std;

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

void prim(int n) {
    float total_weight = 0.0;
    vector<Edge> min_e(n);
    min_e[0].w = 0.0;
    set<Edge> q;
    Edge temp;
    temp.to=0;
    temp.w=0.0;
    q.insert(temp);
    vector<bool> selected(n, false);
    for (int i = 0; i < n; ++i) {

        int v = q.begin()->to;
        selected[v] = true;
        total_weight += q.begin()->w;
        q.erase(q.begin());

        if (min_e[v].to != -1)
            prp.push_back(make_pair(v,min_e[v].to));
            //cout << min_e[v].to << " " << v << endl;

        for (Edge e : adj2[v]) {
            if (!selected[e.to] && e.w < min_e[e.to].w) {
                Edge tmp;
                tmp.to=e.to;
                tmp.w=min_e[e.to].w;
                q.erase(tmp);
                tmp.to=v;
                tmp.w=e.w;
                min_e[e.to] = tmp;
                tmp.w=e.w; tmp.to=e.to;
                q.insert(tmp);
            }
        }
    }

    cout << total_weight << endl;
}

/*vector<vector<int, pair<int,float> > > adj2;
vector<pair<int,int> > prp;
int visited[1000];
float pw,mx;

struct vertex
{
    int child;
    float key;
};

class com{
public:
    // Comparator function
    bool operator()(vertex a,
                    vertex b)
    {
        if (a.key<b.key) {
            return true;
        }
        return false;
    }
};

void prim(int vert)
{
    vertex ara[vert];
    for(int i=0;i<vert;i++)
    {
        ara[i].key=mx+1;
        ara[i].child=-1;
        visited[i]=-1;
    }
    ara[0].key=0;
    set<vertex,com> q;
    q.insert({0,0.0});
    for(int i=0;i<vert;i++)
    {
        int u=q.begin()->child;
        visited[u]=true;
        pw+=q.begin()->key;
        q.erase(q.begin());

        if(ara[u].child!=-1)
            cout<<u<<" "<<ara[u].child<<"\n";
        for(int j=0;j<adj2[u].size();j++)
        {
            if(visited[adj2[u][j].first]==-1 && adj2[u][j].second<ara[adj2[u][j].first].key)
            {
                q.erase({ara[adj2[u][j].first].key,adj2[u][j].first});
                ara[adj2[u][j].first]={adj2[u][j].second,u};
                q.insert({adj2[u][j].second,adj2[u][j].first});
            }
        }
    }
    cout<<pw<<"\n";
}*/

int main()
{
    int v,e,x,y;
    float wt;
    cin>>v>>e;
    for(int i=0;i<e;i++)
    {
        cin>>x>>y>>wt;
        /*if(i==0)
            mx=w;
        else
            mx=max(mx,w);*/
        Edge temp1;
        temp1.to=y;
        temp1.w=wt;
        adj2[x].push_back(temp1);
        temp1.to=x;
        adj2[y].push_back(temp1);
    }
    prim(v);
    for(int i=0;i<prp.size();i++)
        cout<<prp[i].first<<" "<<prp[i].second<<"\n";
}

