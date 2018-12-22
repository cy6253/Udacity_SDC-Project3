#include<stdio.h>
#define WIDTH 15
#define HEIGHT 3
#define ano_num 10
#define Goal_x 0
#define Goal_y 1
typedef struct
{
    int x,y;
    char *state;
}Vehicle;

typedef struct
{
    int x,y;
}Delta;

int costfunc(char(*grid)[3],Vehicle candidate,int x, int y);
void printgrid(char (*grid)[3]);
Vehicle transition(char(*grid)[3],Vehicle ego, Vehicle ano[], Delta del[], char **s);
int cmp(int *arr);

int main()
{
    int i,j;
    
    char grid[WIDTH][HEIGHT];
    for(i=0;i<WIDTH;i++)
    {
        for(j=0;j<HEIGHT;j++)
        {
            grid[i][j]='_';
        }
    }
    grid[Goal_x][Goal_y]='G';
    
    char *state[]={"LCL","KL","LCR"};
    Vehicle ego={WIDTH-1,1,state[1]};
    Vehicle ano[ano_num]={{7,0,state[1]},{6,2,state[1]},{4,1,state[1]},{2,2,state[1]},{1,0,state[1]}
					 ,{12,0,state[1]},{10,2,state[1]},{8,1,state[1]},{0,0,state[1]},{5,0,state[1]}};
    Delta del[3]={{-1,-1},{-1,0},{-1,1}};
    
    while(1)
    {
        grid[ego.x][ego.y]='^';
        for(j=0;j<ano_num;j++)
        {
            grid[ano[j].x][ano[j].y]='#';
        }
        printgrid(grid);
        if(ego.x==Goal_x&&ego.y==Goal_y)
        {
            printf("You reach the goal!\n");
            break;
        }
        printf("\n");
        grid[ego.x][ego.y]='_';
        printf("before : %s\n",ego.state);
        ego=transition(grid,ego,ano,del,state);
        printf("after :  %s\n",ego.state);
    }
    
    return 0;
}

int cmp(int *arr)
{
    int temp=arr[0];
    int i,result=0;
    for(i=1;i<3;i++)
    {
        if(temp>arr[i])
        {
            temp=arr[i];
            result=i;
        }
    }
    return result;
}

int costfunc(char(*grid)[3], Vehicle candidate, int x, int y)
{
    int i;
    if(grid[candidate.x][candidate.y]!='#')
    {
        return (candidate.x - x);
    }
    else
    {
        return 100;
    }
    
}
Vehicle transition(char(*grid)[3], Vehicle ego, Vehicle ano[], Delta del[], char **s)
{
    int i,j,result;
    Vehicle candidate[3]={ego,ego,ego};
    int cost[3]={100,100,100};
    int weight[3]={2,1,3};
    
    if(ego.y==0)//Left lane
	{
		for(j=1;j<3;j++)
		{
			candidate[j].x+=del[j].x;
			candidate[j].y+=del[j].y;
			cost[j]=costfunc(grid,candidate[j],Goal_x,Goal_y);
			candidate[j].state=*(s+j);
		}
	}
    else if(ego.y==1)//Center lane
    {
        for(j=0;j<3;j++)
        {
            candidate[j].x+=del[j].x;
            candidate[j].y+=del[j].y;
            cost[j]=costfunc(grid,candidate[j],Goal_x,Goal_y);
            candidate[j].state=*(s+j);
        }
    }
    else//Right lane
    {
        for(j=0;j<2;j++)
        {
            candidate[j].x+=del[j].x;
            candidate[j].y+=del[j].y;
            cost[j]=costfunc(grid,candidate[j],Goal_x,Goal_y);
            candidate[j].state=*(s+j);
        }
    }
    
    for(i=0;i<3;i++)
    {
        cost[i]*=weight[i];
		printf("cost %d : %d\n",i+1,cost[i]);
    }
    result=cmp(cost);
    return candidate[result];
}
void printgrid(char (*grid)[3])
{
    int i,j;
    for(i=0;i<WIDTH;i++)
    {
        for(j=0;j<HEIGHT;j++)
        {
            printf("%3c",grid[i][j]);
        }
        printf("\n");
    }
}

