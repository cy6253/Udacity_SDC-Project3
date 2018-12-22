#include <stdio.h>

typedef struct
{
    int x;
    int y;
    int g;
    int h;
    int f;//f=g+h
    int cost;//1
}check;

typedef struct
{
    int x;
    int y;
}Delta;

int cmp(int *arr);
check F_val(int grid[][6],int heuristic[][6], check x);
void Astar(int grid[][6],int heuristic[][6], int route[][6]);

int main()
{
    int grid[5][6]={
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,0,0,1,0}
    };
    int heuristic[5][6]={
        {9,8,7,6,5,4},
        {8,7,6,5,4,3},
        {7,6,5,4,3,2},
        {6,5,4,3,2,1},
        {5,4,3,2,1,0}
    };
    int route[5][6]={
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    Astar(grid,heuristic,route);
    return 0;
}

int cmp(int *arr)
{
    int temp=arr[0];
    int i,result=0;
    for(i=1;i<4;i++)
    {
        if(temp>arr[i])
        {
            result=i;
        }
    }
    return result;
}
void Astar(int grid[][6],int heuristic[][6], int route[][6])
{
    check a;
    a.x=0;
    a.y=0;
    a.g=0;
    a.h=heuristic[a.x][a.y];
    a.f=a.g+a.h;
    int count=1;

    while(a.h!=0)
    {
        grid[a.x][a.y]=1;
        route[a.x][a.y]=count++;
        a=F_val(grid,heuristic,a);
        route[a.x][a.y]=count;
    }
    
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<6;j++)
        {
            printf("%2d",route[i][j]);
        }
        printf("\n");
    }
}
check F_val(int grid[][6],int heuristic[][6], check x)
{
    Delta del[4]={{-1,0},{0,1},{1,0},{0,-1}};//up right down left
    check a[4],t;
    int i,result;
    int arr[4]={100,100,100,100};
    for(i=0;i<4;i++)
    {
        t.x = x.x + del[i].x;
        t.y = x.y + del[i].y;
        t.g = x.g;
        if(t.x>=0&&t.x<=5&&t.y>=0&&t.y<=6&&grid[t.x][t.y]==0)
        {
            a[i].x=t.x;
            a[i].y=t.y;
            a[i].g=t.g+1;
            a[i].h=heuristic[t.x][t.y];
            a[i].f=a[i].g+a[i].h;
            arr[i]=a[i].f;
        }
    }
    result=cmp(arr);
    t=a[result];
    return t;
}

