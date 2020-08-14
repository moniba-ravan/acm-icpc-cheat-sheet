#include <bits/stdc++.h>

using namespace std ;


struct segtree{
    // !!! Root is 1
    vector<int> st, prop;

    segtree( int n){
        // n is tree size
        st.resize(n,0);
        prop.resize(n,0);
    }

    void build( int r, int s, int e, int *arr ){
        if( e < s )
            return;

        if( s == e ){
            st[ r ] = arr[ s ];
            return;
        }
        int mid = ( s  + e ) >> 1;
        build( 2*r, s, mid, arr);
        build( 2*r + 1, mid + 1, e, arr);
        st[ r ] = max( st[ 2*r ] , st[ 2*r + 1 ]); // max?
    }

    void push( int r, int s, int e){
        if( s != e){
            prop[ 2*r ] += prop[ r ]; // max? or (e - s + 1)*prop[r]?sum?
            prop[ 2*r + 1 ] += prop[ r ]; // max?
        }
        st[ r ] += prop[ r ]; // max?
        prop[ r ] = 0;
    }

    void update( int r, int s, int e, int qs, int qe, int val){
        if( e < s )
            return;
        push(r, s, e);
        if( qs > e || qe < s)
            return;

        if( qs <= s && e <= qe ){
            prop[ r ] += val; // max?
            push(r, s, e);
            return;
        }

        int mid = (s + e ) >> 1;
        update(2*r, s, mid, qs, qe, val);
        update(2*r + 1, mid + 1, e, qs, qe, val);
        st[ r ] = max( st[ 2*r ], st[ 2*r + 1 ] ); // max?
    }

    void set_val( int r, int s, int e, int pos, int val ){
        if( e < s )
            return;
        push(r, s, e);
        if( pos < s || e < pos )
            return;
        if( s == e ){
            st[ r ] = val;
            return;
        }

        int mid = ( s + e ) >> 1;
        set_val(2*r, s, mid, pos, val);
        set_val(2*r + 1, mid + 1, e, pos, val);
        st[ r ] = max( st[ 2*r ], st[ 2*r + 1]); // max?
    }

    //query returns the max of [qs,qe] range
    int query(int r, int s, int e, int qs, int qe){
        if( e < s )
            return 0; // return 0? max? or INT_MAX? min?
        push(r, s, e);
        if( qe < s || qs > e )
            return 0; // return 0? max? or INT_MAX? min?
        if( qs <= s && e <= qe)
            return st[ r ];

        int mid = ( s + e ) >> 1;
        return max(query( 2*r , s, mid, qs, qe) , query( 2*r + 1, mid + 1, e, qs, qe)); // max?
    }
};

int main{return 0;}
