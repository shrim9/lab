/*#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    vector<vector<int>> maximum = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2}, 
        {4, 3, 3} 
    };
    int n = allocation.size();
    int m = allocation[0].size();
    vector<vector<int>> need(n, vector<int>(m));
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    vector<int> available = {3, 3, 2};
    vector<int> flag(n, 0);
    vector<int> result;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(flag[j] == 0){
                int r = 1;
                for(int k=0; k<m; ++k){
                    if(need[j][k] <= available[k]) continue;
                    else{ 
                        r = 0;
                        break;
                    }
                }
                if(r){
                    flag[j] = 1;
                    for(int k=0; k<m; ++k){
                        available[k] += allocation[j][k];
                    }
                    result.push_back(j);
                }
            }
        }
    }
    int sum = 0;
    for(int i=0; i<n; ++i){
        sum += flag[i];
    }
    if(sum == n){
        cout<<"Safe Sequence is : ";
        for(int i=0; i<n; ++i){
            cout <<"P"<< result[i]+1 << " ";
        }
        cout<<endl;
    }
    else{
        cout<<"Deadlock Detected"<<endl;
    }
    return 0;
}*/

#include <stdio.h>
int main()
{
int n, m, i, j, k;
printf("Enter no of Processes\n");
scanf("%d", &n);
printf("Enter no of Resources\n");
scanf("%d", &m);
int alloc[n][m];
int max[n][m];
printf("Enter Allocation Matrix\n");
for (int i = 0; i < n; i++)
{
for (int j = 0; j < m; j++)
{
scanf("%d", &alloc[i][j]);
}
}
printf("Enter Max Matrix\n");
for (int i = 0; i < n; i++)
{
for (int j = 0; j < m; j++)
{
scanf("%d", &max[i][j]);
}
}
int avail[m];
printf("Enter Available Resources\n");
for (int j = 0; j < m; j++)
{
scanf("%d", &avail[j]);
}
int f[n], ans[n], ind = 0;
for (k = 0; k < n; k++)
{
f[k] = 0;
}
int need[n][m];
for (i = 0; i < n; i++)
{
for (j = 0; j < m; j++)
need[i][j] = max[i][j] - alloc[i][j];
}
int y = 0;
for (k = 0; k < 5; k++)
{
for (i = 0; i < n; i++)
{
if (f[i] == 0)
{
int flag = 0;
for (j = 0; j < m; j++)
{
if (need[i][j] > avail[j])
{
flag = 1;
break;
}
}
if (flag == 0)
{
ans[ind++] = i;
for (y = 0; y < m; y++)
avail[y] += alloc[i][y];
f[i] = 1;
}
}
}
}
int flag = 1;
for (int i = 0; i < n; i++)
{
if (f[i] == 0)
{
flag = 0;
printf("The following system is not safe");
break;
}
}
if (flag == 1)
{
printf("Following is the SAFE Sequence\n");
for (i = 0; i < n - 1; i++)
printf(" P%d ->", ans[i]);
printf(" P%d", ans[n - 1]);
}
return (0);
}