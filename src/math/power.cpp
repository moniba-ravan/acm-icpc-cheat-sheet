#include<bits/stdc++.h>

using namespace std;

long long power(long long a , long long b){
    if(b == 1)
        return a;
        
    long long ans = power(a , b / 2) ;
    ans = ans * ans ;
    if( b % 2 )
        ans = (ans * a) ;
    return ans;
}

int main(){
    return 0;
}
