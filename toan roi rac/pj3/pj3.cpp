#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ofstream output;
int state[11][5][8]={0},a1=0;
int graph[30][3];
vector <int> edge[30];
int visit[30]={0};

void printGraph(int u,int v){
    output<<"<"<<graph[u][0]<<","<<graph[u][1]<<","<<graph[u][2]<<"> -- "<<"<"<<graph[v][0]<<","<<graph[v][1]<<","<<graph[v][2]<<">;"<<endl;
}

int edgeCheck(int u, int v){
    if((graph[u][0]==graph[v][0])&&(graph[v][1]==4||graph[v][2]==7||graph[v][1]==0||graph[v][2]==0))
        return 1;
    else if((graph[u][1]==graph[v][1])&&(graph[v][0]==10||graph[v][2]==7||graph[v][0]==0||graph[v][2]==0))
        return 1;
    else if((graph[u][2]==graph[v][2])&&(graph[v][1]==4||graph[v][0]==10||graph[v][1]==0||graph[v][0]==0))
        return 1;
    else return 0;
}


void stateCheck(){
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)
            if(i!=j&&edgeCheck(i,j))    
                    edge[i].push_back(j);
}

void waterJug(int x, int y, int z){
    if(!state[x][y][z]){
        state[x][y][z]=1;
        graph[a1][0]=x;
        graph[a1][1]=y;
        graph[a1][2]=z;
        a1++;

        if(x!=0){
            if ((x-(4-y))<=0)
                waterJug(0,y+x,z);
            else waterJug(x-(4-y),4,z);
            if (x-(7-z)<=0)
                waterJug(0,y,z+x);
            else waterJug(x-(7-z),y,7);
        }
        if(y!=0){
            if(y-(10-x)<=0)
                waterJug(x+y,0,z);
            else waterJug(10,y-(10-x),z);
            if(y-(7-z)<=0)
                waterJug(x,0,z+y);
            else waterJug(x,y-(7-z),7);
        }
        if(z!=0){
            if(z-(10-x)<=0)
                waterJug(x+z,y,0);
            else waterJug(10,y,z-(10-x));
            if(z-(4-y)<=0)
                waterJug(x,y+z,0);
            else waterJug(x,4,z-(4-y));
        }
    }
}

void kp(int a){
    visit[a]=1;
    for (int b: edge[a]){
        if(visit[b]==0){
            printGraph(a,b);
            kp(b);
        }
    }
}
void DFS(int N){
    for (N=0;N<21;N++)
        if (visit[N]==0)
            kp(N);
}
int main(){
    output.open("donuoc.dot", ios_base::out);
    output<<"graph{"<<endl;
    waterJug(0,4,7);  
    stateCheck();        
    DFS(0);
    output<<"}";
    output.close();
    return 0;
}
