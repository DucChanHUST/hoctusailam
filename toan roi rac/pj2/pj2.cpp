#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;

int main()
{
    int n,e,i,j,x,y,cr;
    vector<vector<int> > graph;
    vector<vector<int> > edge;
    vector<int> color;
    vector<int> useded;

    ifstream fi;
    fi.open("dothi.txt");
    ofstream fo;
    fo.open("dothitomau.dot");
    
    fi>>n>>e;
    edge.resize(e);
    graph.resize(n);
    color.resize(n);
    for(i=0;i<e;i++)
    {
        fi>>x>>y;
        x--; y--;
        edge[i].push_back(x); 
        edge[i].push_back(y);
        graph[x].push_back(y);
        graph[y].push_back(x);

    }
    for(i=0; i<n; i++)
        graph[i].insert(graph[i].begin(),i);
//sorting
    sort(graph.begin(), graph.end(), [](const vector<int> & a, const vector<int> & b)
        { return a.size() > b.size(); });
//coloring
    cr=1; bool xh;
    for(i=0; i<n; i++) color[i]=-1;

    for(i=0; i<n; i++)
        if (color[i]==-1)
    {
        color[i]=color[i]+cr;
        useded.push_back(graph[i][0]);
        for(j=0; j<n; j++)
            if ((i!=j) && (color[j]==-1))
        {
            for(int k=0; k<useded.size(); k++)
            {
                xh=false;
                for(int t=0; t<graph[j].size(); t++)
                    if (graph[j][t]==useded[k])
                    {
                        xh=true;
                        break;
                    }
                if (xh==true) break;
            }
            if (xh==false)
            {
                color[j]=color[j]+cr;
                useded.push_back(graph[j][0]);
            }
        }
        cr++; useded.clear();
    }
    string hex;
        srand(time(0));
    // hex_color_code(hex);
    vector<string> mau;
    mau.resize(cr-1);
    char hex_char[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    for (i=0; i<cr-1; i++) {
        for (j=0;j<6;j++) mau[i].push_back(hex_char[rand()%16]);
    }

//print final
    fo <<"graph dothi\n{\n";
    for(i=0; i<n; i++) 
        fo<<"   "<<graph[i][0]+1<<" [fillcolor=\"#"<<mau[color[i]]<<"\", style=filled];\n";

    for(i=0;i<e;i++)
    {
        fo<<"   "<<edge[i][0]+1<<" -- "<<edge[i][1]+1<<";\n";
    }
    fo<<"}";

    fi.close();
    fo.close();
    return 0;
}