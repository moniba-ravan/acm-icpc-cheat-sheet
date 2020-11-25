#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

ordered_set st;
int k, temp;
int main () {
    // Number of items strictly smaller than k .
    // if greater<int> -> the number of items strictly greater than 'k'
    temp = st.order_of_key (k);

    // K-th element in a set (counting from zero).
    temp =*st.find_by_order(k);

    return 0;
}
