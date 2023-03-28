#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Queue{
    unsigned long long rear, size, front;
    unsigned long long capacity;
    int* array; // fix datatype
}Queue;


Queue* createQueue(unsigned long long capacity){
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->size = queue->front = 0;
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(capacity * sizeof(int)); //fix datatype
    return queue;
}

bool isEmpty(Queue* queue){ return queue->size == 0;}

bool isFull(Queue* queue){ return queue->size == queue->capacity;}

int rear(Queue* queue){ //fix datatype
    if (isEmpty(queue)) return INT_MIN;
    return queue->array[queue->rear];
}

int font(Queue* queue){
    if (isEmpty(queue)) return INT_MIN;
    return queue->array[queue->front];
}

void Enqueue(Queue* queue,int value){ // fix datatype
    if (isFull(queue)) {
        printf("Queue is full");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = value;
    queue->size++;
}

int Dequeue(Queue* queue){//fix datatype
    if (isEmpty(queue)) {
        printf("Queue is empty");
        return INT_MIN;
    }
    int value = queue->array[queue->front]; //fixdatatype
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

int max =  __INT_MAX__;//#difine


int graph[100][100];
int n,m,a,b,c,d;
unsigned int r;
bool havePath;


//dfs
bool checkStep[100][100];
int step[100][100];
int path = 0;
int count = 0;
int countStep[100] ;
int parent[2][100];
bool visited[100];



void resetDFS(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            checkStep[i][j] = false;
        }
        
    }
}

void createGraph(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            graph[i][j] = 0;
        }
    }
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++)
    {
        int x,y,w;
        scanf("%d %d %d",&x,&y,&w);
        graph[x][y] = w;
        graph[y][x] = w;
    }
    scanf("%d %d",&a,&b);
    scanf("%d %d",&c,&d);
    scanf("%d",&r);
}

int Dijkstra(int s,int v){
    int dist[100];
    int countOut = 0;
    bool check[100];
    for (int i = 0; i < n; i++)
    {
        dist[i] = max;
        check[i] = true;
        //pre
    }
    dist[s] = 0;
    //check[s] = false;
    countOut++;
    while (countOut <= n)
    {
        int u;
        int min = max;
        int min_index = -1;
        for (int i = 0; i < n; i++){
            if (check[i] && dist[i] <= min) {
                min = dist[i];
                min_index = i;
            }
        }
        u = min_index;
        if(u == v) return dist[v];
        check[u] = false;
        countOut++;
        for (int i = 0; i < n; i++)
        {
            if (check[i] && graph[u][i] != 0 && dist[u] != max && dist[u] + graph[u][i] < dist[i]){
                dist[i] = dist[u] + graph[u][i];
            }      
        }
  
    }
    return max;
}

typedef struct Robot
{
    int x;
    int y;
    int index;
    int preIndex;
    int dis;
}Robot;

int isVisited[100][100];
int indexCount = 0;
Robot robot[10000];

void preBFS(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            isVisited[i][j] = false;
        }
        
    }
}

void createRobot(int x,int y,int preIndex,int dis){
    isVisited[x][y] = true;
    robot[indexCount].x = x;
    robot[indexCount].y = y;
    robot[indexCount].preIndex = preIndex;
    robot[indexCount].dis = dis;
    indexCount++;
}

int BFS(){
    createRobot(a,b,-1,Dijkstra(a,b));
    if (robot[0].dis <= r) return -1;
    Queue* queue = createQueue(10000);
    Enqueue(queue, robot[0].index);
    while (!isEmpty(queue))  
    {
        int u = Dequeue(queue);
        for (int j = 0; j < n; j++)
        {
            if(graph[robot[u].y][j] == 0 && robot[u].y != j) continue;
            int dis = Dijkstra(robot[u].x,j);
            if(dis > r && !isVisited[robot[u].x][j]){
                int adjIndex = indexCount;
                createRobot(robot[u].x,j,u,dis);
                Enqueue(queue,adjIndex);
                if (robot[u].x == c && j == d) 
                {
                    return adjIndex;
                }
                
            }
        }
        for (int i = 0; i < n; i++)
        {
            if(graph[robot[u].x][i] == 0 && robot[u].x != i) continue;
            int dis = Dijkstra(i,robot[u].y);
            if(dis > r && !isVisited[i][robot[u].y]){
                int adjIndex = indexCount;
                createRobot(i,robot[u].y,u,dis);
                Enqueue(queue,adjIndex);
                if (i == c && robot[u].y == d) 
                {
                    return adjIndex;
                }
                
            }
                
        }
        
    }
    return -1;
}

void printMinPath(){
    preBFS();
    int indexTarget = BFS();
    if (indexTarget < 0)
    {
        printf("Khong the!");
        return;
    }
    printf("Lich di chuyen          Khoang cach\n");
    int indexs[10000];
    int i = 0;
    indexs[i] = indexTarget;
    while (indexs[i] != 0)
    {
        indexs[i + 1] = robot[indexs[i]].preIndex;
        i++;
    }
    for (int j = i; j > 0; j--){
        printf("     %d %d                    %d\n",robot[indexs[j]].x,robot[indexs[j]].y,robot[indexs[j]].dis);
    }
    printf("     %d %d                    %d",robot[indexTarget].x,robot[indexTarget].y,robot[indexTarget].dis);
}

int main(){
    createGraph();
    printMinPath();
    return 0;
}