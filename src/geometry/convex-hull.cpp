#include <bits/stdc++.h>

using namespace std ;

// int
struct Point{
    int x,y;
    Point(int _x=0,int _y=0){
        x=_x;
        y=_y;
    }
};

//the input points are in dots and result in res
vector< Point > dots,res;

// double
double dist(Point a,Point b){
    return sqrt((double)(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y))));
}

//Find the bottom-most(then the left-most)
void bottom_most(){
    int id_start;
    Point start = Point(INT_MAX,INT_MAX);
    for(int i = 0; i < (int)dots.size(); i++ ){
            if(start.y > dots[ i ].y || (start.y == dots[ i ].y && start.x > dots[ i ].x )){
                    start.x = dots[ i ].x;
                    start.y = dots[ i ].y;
                    id_start = i;
            }
     }
     swap(dots[ 0 ], dots[ id_start ]);
}

bool cross(Point c,Point a,Point b){
    //clockwise
    double ans = ( (a.x - c.x) * (b.y - a.y) ) - ( (b.x - a.x) * (a.y - c.y) );
    //ans *= -1 counter clockwise
    if(ans > 0)
        return true;
    //ans == 0 colinear
    if(ans == 0 && dist( c, a) > dist( c, b))
        return true;
    return false;
}

bool compre( Point a, Point b){
    Point c = dots[ 0 ];
    return !cross( c, a, b);
}


void findconvex(){
    Point a, b, c;
    a = b = c = Point(0,0);
    stack < Point > st;
    st.push( dots[ 0 ] );
    if( (int) dots.size() >= 3){
        a = dots[ 1 ];
        b = dots[ 2 ];
    }
    for(int i = 3 ; i < (int)dots.size(); i++){
        c = dots[ i ];
        while( cross( a, b, c)){
            b = a;
            a = st.top();
            st.pop();
        }
        st.push( a );
        a = b;
        b = c;

    }
    if( (int)dots.size() >= 3){
        st.push( a );
        st.push( b );
    }else if( (int)dots.size() == 2) st.push( dots[ 1 ] );
    while( !st.empty() ){
        res.push_back( st.top() );
        st.pop();
    }
}


int main(){
    int n;
    int x, y;

    dots.clear();
    res.clear();

    cin >> n;
    for(int i = 0 ; i < n ; i++){
        cin>> x >> y;
        dots.push_back( Point( x, y) );
    }
    bottom_most();
    sort( dots.begin() + 1 , dots.end(), compre);
    findconvex();

    //print result is in res
    for( int i = 0; i < (int)res.size() ; i++ ){
        cout << res[ i ].x << ' ' <<res[ i ].y << endl;
    }

    return 0;
}
