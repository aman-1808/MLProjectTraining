#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7FFFFFFF;//max value of int
const int MAXN = 5e5 + 2;
const int MAXQ = 5e5 + 2;

void fast(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

template <typename T> void print(T &v) {
    for (auto& a:v) {
        cout << a << " ";
    }
    cout << endl;
}

int n, q;
int num_query=1;
string op;

int row, col, ind, val, timer;
vector<bool> rowVal(MAXN), colVal(MAXN), *values;

struct segment_tree
{
    int count[MAXQ*4], edit[MAXN];
    //count stores number of times row was set to 0 (or something like that) in segment of time
    //edit stores time of last 'query' which edited index in specified way
    
    void init(bool flag)
    {
        memset(edit, 0, sizeof(edit));
        memset(count, 0, sizeof(count));
        if(flag)//flag is true for row0, col0
        {
            changeTm(0, n);
        }
    }
    
    void changeTm(int tm, int chng, int l=0, int r=q, int pos=1)
    {
        if(l==r)
        {
            count[pos]+=chng;
            // cout<<"after change -> count from "<<l<<" to "<<r<<" = "<<count[pos]<<endl;
            return;
        }
        
        int mid = (l+r)/2;
        
        if(tm <= mid)
            changeTm(tm, chng, l, mid, pos*2);
        else
            changeTm(tm, chng, mid+1, r, pos*2+1);
        
        count[pos] = count[pos*2] + count[pos*2+1];
    }
    
    void change(int ind, bool set)
    {
        // cout<<"change "<<ind<<" with time "<<edit[ind]<<"  by "<<(set?1:-1)<<" at time "<<num_query<<endl;
        if(set)
        {
            edit[ind] = num_query;
            changeTm(num_query, 1);
        }
        else
        {
            changeTm(edit[ind], -1);
            //edit[ind]=0;
        }
    }
    
    int query(int qL, int qR=num_query, int l=0, int r=q, int pos=1)
    {
        // cout<<"count["<<pos<<"] = "<<count[pos]<<endl;
        if(qL <= l && qR >= r)
        {
            return count[pos];
        }
        else if(qL > r || qR < l)
        {
            return 0;
        }
        else
        {
            int mid = (l+r)/2;
            
            return query(qL, qR, l, mid, pos*2) + query(qL, qR, mid+1, r, pos*2+1);
        }
    }
} row0, row1, col0, col1, *a0, *a1, *b0, *b1;

void solve()
{
    cin>>n>>q;
    
    row0.init(true);
    col0.init(true);
    row1.init(false);
    col1.init(false);
    
    for(num_query=1; num_query<=q; num_query++)
    {
        
        cin>>op;
        
        if(op[0]=='R')
        {
            a0 = &row0;
            a1 = &row1;
            b0 = &col0;
            b1 = &col1;
            values = &rowVal;
        }
        else
        {
            a0 = &col0;
            a1 = &col1;
            b0 = &row0;
            b1 = &row1;
            values = &colVal;
        }
        
        if(op[3]=='S')
        {
            cin>>ind>>val;
            
            ((*values)[ind] ? a1 : a0)->change(ind, 0);
            (val            ? a1 : a0)->change(ind, 1);
            
            (*values)[ind] = val;
        }
        else
        {
            cin>>ind;
            
            if((*values)[ind])
            {
                timer = a1->edit[ind];
                cout<<b0->query(timer) << '\n';
            }
            else
            {
                timer = a0->edit[ind];
                cout<<n - b1->query(timer) << '\n';
            }
        }
        
    }
    
}

int main() {
    fast();
    
    int T=1;
    //cin>>T;
    
    while(T--){
        solve();
    }
    
	return 0;
}
