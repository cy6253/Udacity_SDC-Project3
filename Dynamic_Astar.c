#include <stdio.h>
typedef struct
{
    int x,y;
}XY;

typedef struct
{
    int x,y;
}Delta;

void optimum_policy(int (*grid)[6], int (*value)[6], char (*policy)[6]);

int main()
{
    int grid[5][6]={
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,0,0,1,0}
    };
    int value[5][6]={
        {99,99,99,99,99,99},
        {99,99,99,99,99,99},
        {99,99,99,99,99,99},
        {99,99,99,99,99,99},
        {99,99,99,99,99,99},
    };
    char policy[5][6]={
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
    };
    optimum_policy(grid,value,policy);
    return 0;
}
void optimum_policy(int (*grid)[6], int (*value)[6], char (*policy)[6])
{
    XY a,b;
    Delta del[4]={{-1,0},{0,1},{1,0},{0,-1}};
    char pd[4]={'U','R','D','L'};
    
    XY goal={5,6};
    value[goal.x-1][goal.y-1]=0;
    policy[goal.x-1][goal.y-1]='G';
    int i,j;
    int t=20;
    
    while(t>0)
    {
        for(a.x=0;a.x<goal.x;a.x++)
        {
            for(a.y=0;a.y<goal.y;a.y++)
            {
                if(grid[a.x][a.y]==0)
                {
                    int i;
                    for(i=0;i<4;i++)
                    {
                        b.x = a.x + del[i].x;
                        b.y = a.y + del[i].y;
                        if(b.x>=0&&b.x<=goal.x&&b.y>=0&&b.y<=goal.y&&grid[b.x][b.y]==0)
                        {
                            int result;
                            result=value[b.x][b.y]+1;
                            if(result<value[a.x][a.y])
                            {
                                value[a.x][a.y]=result;
                                policy[a.x][a.y]=pd[i];
                            }
                        }
                    }
                }
            }
        }
        t--;
    }
    for(i=0;i<5;i++)
    {
        for(j=0;j<6;j++)
        {
            printf("%3c ",policy[i][j]);
        }
        printf("\n");
    }
}

