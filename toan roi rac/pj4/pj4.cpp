#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>

using namespace std;

    const int SL = 5757;
    int pre[SL];
    bool check[SL];
    string sgb[SL];
    vector<vector<int> > graph;
    vector<vector<int> > d_graph;

// 1a
void DFS1a(int u){
    check[u] = true;
    for (int i = 0; i < graph[u].size(); i++)
        if (!check[graph[u][i]])
            DFS1a(graph[u][i]);
}
bool khacNhau1VT(string a, string b){
    // bool status = true; 
    int dem = 0;
    for (int i = 0; i < 5; i++)
    {
        if (a[i] != b[i]) dem++;
    }
    if (dem == 1) return true;
    else return false;
}
void soThanhPhanLT(){
    int res = 0;
    for (int i = 0; i < SL; i++)
    {
        if (!check[i])
        {
            res++;
            DFS1a(i);
        }
    }
    cout<<res<<"\n";
}

// 1b
void BFS1b(int u, int v){
    queue<int> q;
    q.push(u);
    while (q.size()>0)
    {
        int top = q.front(); q.pop();
        check[top] = true;
        if (top == v) return;
        for (int i = 0; i < graph[top].size(); i++)
        {
            if (!check[graph[top][i]])
            {
                check[graph[top][i]] = true;
                pre[graph[top][i]] = top;
                q.push(graph[top][i]);
            }
        }
    }
}
void trace(int u, int v){
    if (!check[v])
    {
        cout<<"-1";
        return;
    }
    vector<int> x;
    while (u != v)
    {
        if (u == 0)
        {
            cout<<"-2";
            return;
        }
        x.push_back(u);
        u = pre[u];
    }
    x.push_back(v);
    reverse(x.begin(), x.end());
    for(int i = 0; i < x.size(); i++)
        cout <<sgb[x[i]]<<" ";
}
void timDuong1b(){
    string a, b;
    int x, y, dem = 0;
    cout<<"from: "; cin>>a;
    cout<<"to: "; cin>>b;
    for (int i = 0; i < SL; i++)
    {
        if (a == sgb[i])
        {
            dem++;
            x = i;
            // cout<<x<<"\n";
        }
        else if (b == sgb[i])
        {
            dem++;
            y = i;
            // cout<<y<<"\n";
        }
        if (dem == 2) break;
    }
    BFS1b(x, y);
    trace(y, x);
    cout<<"\n";
}

// 2a
bool giong4ChuCuoi(string a, string b){
    string temp = b;
    for (int i = 1; i < 5; i++)
    {
        int j = 0;
        while (j < temp.length())
        {
            if (a[i] == temp[j]){
                temp.erase(temp.begin() + j);
                break;
            } 
            j++;
        }
    }
    if (temp.length() == 1) return true;
        else return false;
}

bool onStack[SL];
int in[SL], low[SL];
stack<int> st;
int timer = 0, scc = 0;
void DFS2a(int u){
    // 
    check[u] = true;
    in[u] = low[u] = timer++;
    onStack[u] = true;
    st.push(u);
   
    for (int v : d_graph[u])
    {
        if (check[v] == true && onStack[v] == true)
        {
            low[u] = min(low[u], in[v]);
        }
        else if (check[v] == false)
        {
            DFS2a(v);
            if(onStack[v] == true)
                low[u] = min(low[u], low[v]);
        }
    }
    if(in[u] == low[u])
    {
        scc++;
        // cout<<"scc# "<<scc<<"\n";
        int v;
        while (1)
        {
            v = st.top();
            st.pop(); onStack[v] = false;
            // cout<<sgb[v]<<" ";
            if(v == u) break;
        }
        // cout<<"\n";
    }
}
void soThanhPhanLTM(){
    memset(check, false, SL);
    scc=0;
    for(int i = 0; i < SL; i++)
        if(!check[i]) DFS2a(i);
    cout<<scc<<"\n";
}

// 2b
void DFS2b(int u){
    // 
    check[u] = true;
    in[u] = low[u] = timer++;
    onStack[u] = true;
    st.push(u);
   
    for (int v : d_graph[u])
    {
        if (check[v] == true && onStack[v] == true)
        {
            low[u] = min(low[u], in[v]);
        }
        else if (check[v] == false)
        {
            DFS2b(v);
            if(onStack[v] == true)
                low[u] = min(low[u], low[v]);
        }
    }

    if(in[u] == low[u])
    {
        scc++;
        // cout<<"scc# "<<scc<<"\n";
        int v;
        while (1)
        {
            v = st.top();
            st.pop(), onStack[v] = false;
            cout<<sgb[v]<<" ";
            if(v == u) break;
        }
        cout<<"\n";
    }
}
void cungLTM(){
    memset(check, false, SL);
    scc = 0; 
    string s;
    cin>>s; int u;
    for(int i = 0; i < SL; i++)
        if(sgb[i] == s){
            u = i;
            break;
        }      
    DFS2b(u);
}

// 2c
void BFS2c(int u, int v){
    queue<int> q;
    q.push(u);
    while (q.size()>0)
    {
        int top = q.front(); q.pop();
        check[top] = true;
        if (top == v) return;
        for (int i = 0; i < d_graph[top].size(); i++)
        {
            if (!check[d_graph[top][i]])
            {
                check[d_graph[top][i]] = true;
                pre[d_graph[top][i]] = top;
                q.push(d_graph[top][i]);
            }
        }
    }
}
void timDuong2c(){
    string a, b;
    int x, y, dem = 0;
    cout<<"from: "; cin>>a;
    cout<<"to: "; cin>>b;
    for (int i = 0; i < SL; i++)
    {
        if (a == sgb[i])
        {
            dem++;
            x = i;
            // cout<<x<<"\n";
        }
        else if (b == sgb[i])
        {
            dem++;
            y = i;
            // cout<<y<<"\n";
        }
        if (dem == 2) break;
    }
    BFS2c(x, y);
    trace(y, x);
    cout<<"\n";
}

void menu(){
    cout<<"PROJECT 4\n";
    cout<<"1 -> A. a\n";
    cout<<"2 -> A. b\n";
    cout<<"3 -> B. a\n";
    cout<<"4 -> B. b\n";
    cout<<"5 -> B. c\n";
    cout<<"0 -> quit\n";
    cout<<"=========\n";
}
int selectMenu(){
    int n = 0;
    cout<<"select a number: ";
    cin>>n;
    if (n > 5 || n < 0) return selectMenu();
        else return n;
}
void handleMenu(){
    int select = selectMenu();
    switch (select)
    {
    case 1:
        cout<<"Dem so thanh phan lien thong\n";
        soThanhPhanLT();
        break;
    case 2:
        cout<<"Tim duong di ngan nhat\n";
        timDuong1b();
        break;
    case 3:
        cout<<"So thanh phan lien thong manh\n";
        soThanhPhanLTM();
        break;
    case 4:
        cout<<"Cac tu cung thanh phan lien thong manh\n";
        cungLTM();
        break;
    case 5:
        cout<<"Tim duong di ngan nhat\n";
        timDuong2c();
        break;
    case 0:
        cout<<"Exit\n";
        exit(1);
        break;
    default:
        break;
    }
}

int main(){
    graph.resize(SL);
    d_graph.resize(SL);
    ifstream fi;
    fi.open("sgb-words.txt");
    
    int i = 0;
    while (!fi.eof())
    {
        fi>>sgb[i++];
    }

// do thi vo huong
    for(int i = 0; i < SL-1; i++){
        for(int j = i+1; j < SL; j++){
            if(khacNhau1VT(sgb[i], sgb[j])) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

// do thi co huong
    for(int i = 0; i < SL-1; i++){   
        for(int j = i+1; j < SL; j++){
            if(giong4ChuCuoi(sgb[i], sgb[j]))
                d_graph[i].push_back(j);
            if(giong4ChuCuoi(sgb[j], sgb[i]))
                d_graph[j].push_back(i);
        }
    }

// test print
    // for (int i = 0; i < SL; i++)
    // {
    //     cout<<sgb[i]<<": ";
    //     for (int j = 0; j < d_graph[i].size(); j++)
    //     {
    //         cout<<sgb[d_graph[i][j]]<<" ";
    //     }
    //     cout<<"\n";
    // }

    menu();
    while (true)
    {   
        memset(onStack, false, sizeof(onStack));
        memset(check, false, sizeof(check));
        memset(pre, 0, sizeof(pre));
        handleMenu();
    }
    
    fi.close();
    return 0;
}
