#include <iostream>
using namespace std;

int partition(int a[][2], int start, int end){
    int pivot = a[start][1];
    int count = 0;
    for (int i=start + 1; i<= end; i++){
        if (a[i][1] <= pivot) count++;
    }

    int pivotIndex = start + count;
    swap(a[pivotIndex][1], a[start][1]);
    swap(a[pivotIndex][0], a[start][0]);

    int i = start, j = end;

    while (i<pivotIndex && j >pivotIndex){
        
        while (a[i][1]<=pivot){
            i++;
        }

        while (a[j][1]>pivot){
            j--;
        }

        if (i<pivotIndex && j>pivotIndex){
            swap(a[i][1], a[j][1]);
            swap(a[i][0], a[j][0]);
            i++; j--;
        }
    }
    return pivotIndex;
}

void quicksort(int a[][2], int start, int end){
    if (start >= end) return;
    int p=partition(a, start, end);
    quicksort(a, start, p-1);
    quicksort(a, p+1, end);
}

int main(){
    int n;
    cin >> n;
    int tree[n][2];
    for (int i=0; i<n; i++){
        cin>> tree[i][0]>> tree[i][1];
    }

    quicksort(tree, 0, n-1);

    int dem[n+1] = {0} ; int prufer[n-1];

    for (int i=0; i<n; i++){
        dem[tree[i][0]] ++;
    }

    int min=0, i=0;
    while(i<n){
        if (dem[tree[min][1]]==0){
            prufer[i]=tree[min][0];
            dem[tree[min][1]]++;
            dem[tree[min][0]]--;
            min=-1; i++;
        }
        min++;
    }

//output
    cout<<"\n";
    for (int i=0; i<n-1; i++){
        cout<<prufer[i]<<" ";
    }
    return 0;
}
