#include<bits/stdc++.h>

using namespace std;

int substr_search(string sub, string s, vector<int> &p){
    int l = 0, r = s.size() - 1;
    int n = s.size();
    while(l <= r){ // !!check equal
        int mid = ( l + r ) >> 1;
        int temp = sub.compare(s.substr(p[mid],min((int)sub.size(),n - p[mid])));
        if( temp == 0 )
            return mid;// exists
        if( temp > 0 ) l = mid + 1;
        else r = mid - 1;
    }
    return -1;// not exists
}

void count_sort(vector<int> &p, vector<int> &c ){
    int n = p.size();
    vector< int > cnt(n, 0), pos(n);
    for(auto ci: c)
        cnt[ ci ] ++;
    pos[ 0 ] = 0;
    for(int i = 1; i < n ; i ++ )
        pos[ i ] = pos[ i - 1 ] + cnt[ i - 1];
    vector< int > new_p(n);
    for( auto pi: p){
        int i = c[ pi ];
        new_p[ pos[ i ] ] = pi;
        pos[ i ] ++;
    }
    p = new_p;
}

void suffix_array(string s, vector<int> &p, vector<int> &c){
    int n = s.size();
    {
        // k = 0
        vector< pair< char, int> > a(n);
        for( int i = 0 ; i < n ; i ++ )
            a[ i ] = {s[ i ], i};
        sort( a.begin(), a.end() );

        for( int i = 0 ; i < n ; i++ )
            p[ i ] = a[ i ].second;

        c[ p[ 0 ] ] = 0;
        for( int i = 1 ; i < n ; i ++ ){
            c[ p[ i ] ] = c[ p [ i - 1 ] ];
            if( a[ i ].first != a[ i - 1 ].first )
                c[ p[ i ] ] ++;
        }
    }
    {
        // k -> k + 1
        int k = 0;
        while( (1<<k) < n ){
            for( int i = 0 ; i < n ; i ++ )
                p[ i ] =(p[ i ] - ( 1 << k ) + n ) % n ;
            count_sort(p, c);
            vector<int> new_c(n);

            new_c[ p[ 0 ] ] = 0;
            for( int i = 1; i < n ; i ++ ){
                pair< int, int > pre, now;
                pre = {c[ p[ i - 1] ], c[ (p[ i - 1 ] + ( 1 << k )) % n ]};
                now = {c[ p[ i ] ], c[ (p[ i ] + ( 1 << k )) % n ]};
                new_c[ p [ i ] ] = new_c[ p [ i - 1] ];
                if( pre != now )
                    new_c[ p [ i ] ] ++;
            }
            c = new_c;
            k++;
        }
    }
    /*for( int i = 0 ; i < n ; i ++ )
        cout << p[ i ] <<' '<<s.substr(p[ i ], n - p[ i ] ) <<'\n';
    */
}
int main(){
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
    vector<int> p(n), c(n);
    suffix_array(s, p, c);

    string sub;
    cin >> sub;
    int ans = substr_search(sub, s, p);
    if( ans == -1 ) cout << "Not Exists" << '\n';
    else cout << "Exists" << '\n';
    return 0;
}
