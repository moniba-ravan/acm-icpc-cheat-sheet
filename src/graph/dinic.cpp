struct EDGE{
    ll v, u;
    ll cap, flow;
    EDGE(int _v, int _u, ll _cap){
       v = _v ;
       u = _u ;
       cap = _cap ;
       flow = 0 ;
    }
};

const ll INF = 1e18;
vector<EDGE> edges;
vector<vector<int> > adj;
int nn , mm ;
vector<int> level, ptr ;
int source , destination ;
queue<int> q;

void init(int n , int s , int t){ // node_num , source , destination
    nn = n ;
    source = s;
    destination = t;
    mm = 0 ;
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
    while(!q.empty())
        q.pop();
    edges.clear();
}

void add_edge(int v, int u, ll cap) {
    adj[v].pb(mm);
    adj[u].pb(mm + 1);
    mm += 2;
    edges.pb(EDGE(v, u, cap));
    edges.pb(EDGE(u, v, 0));
}

int bfs() {
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int other ;
        for(int i = 0 ; i < (int)adj[node].size() ; i++){
            other = adj[node][i] ;
            if (edges[other].cap - edges[other].flow < 1 || level[edges[other].u] != -1)
                continue;
            level[edges[other].u] = level[node] + 1;
            q.push(edges[other].u);
        }
    }
    if(level[destination] != -1)
        return 1;
    return -1;
}

ll dfs(ll v, ll pushed) {
    if (pushed == 0)
        return 0;
    if (v == destination)
        return pushed;

    ll mn ;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        int id = adj[v][cid];
        int u = edges[id].u;
        if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
            continue;

        ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
        if (tr == 0)
            continue;
        edges[id].flow += tr;
        edges[id ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}

ll flow() {
    ll f = 0;
    while (true) {
        fill(level.begin() , level.end() , -1);
        level[source] = 0;
        q.push(source);

        if (bfs() == -1)
            break;

        fill(ptr.begin(), ptr.end(), 0);
        while(true){
            ll pushed = dfs(source , INF) ;
            if(pushed == 0)
                break;
            f += pushed ;
        }
    }
    return f;
}
