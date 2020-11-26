const int N = 1e4 + 5 ;

vector<int> adj[N];
vector<int> visited;
vector<int> tin, low;
vector<pair<int, int> > BRIDGE ;
set<int> CUTPOINT;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;

    for (int to : adj[v]) {
        if (to == p) continue;

        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        }
        else {

            dfs(to, v);
            low[v] = min(low[v], low[to]);

            if (low[to] >= tin[v] && p!=-1)
                CUTPOINT.insert(v) ;
            children++;

            if (low[to] > tin[v])
                BRIDGE.push_back( {v, to} );
        }
    }
    if(p == -1 && children > 1)
        CUTPOINT.insert(v);
}

void find_cutpoints(int n) {// number of nodes
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    CUTPOINT.clear();
    BRIDGE.clear();

    for (int i = 0 ; i < n; ++i) {
        if (!visited[i]){
            dfs (i);
        }
    }
}
/** node numbers are considered to be 0-base
    fill the adj[0..n] . and don't forget to clear it for each test case
    other initializations has been taken care of **/

int main(){
    ios_base :: sync_with_stdio(false);
    // your code
    return false;
}
