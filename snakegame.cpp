#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

using namespace std;

int length = 6,score = 0;

char grid[26][40],bodychar='0';
int food[2];
bool over;

struct snake
{
    int num,pos[2],dir;
};

snake snake[1040];

struct game
{
    int update();
    int randomspawn();
    int algo();
    float shortest(float x,float y, float z);
    float greatest(float x,float y, float z);
    float dis(int x, int y);
};

game execute;

int main()
{
    system("MODE CON COLS=40 LINES=28");
    for(int i=0;i<length;i++)
    {
        snake[i].pos[0] = 13;
        snake[i].pos[1] = 30;
    }
    over = true;
    execute.update();
    return 0;
}

int game::update()
{
    int direc[2],temp;
    snake[0].dir=1;
    execute.randomspawn();
    while(over=true)
    {
        //Update Direction and Location of Head
        execute.algo();
        temp = snake[0].dir;
        if(kbhit()==1)
        {
            direc[0] = getch();
            direc[1] = getch();
            switch(direc[1])
            {
                case 72:
                    snake[0].dir = 1;
                    if(temp == 3)
                    {
                        snake[0].dir = 3;
                    }
                    break;
                case 75:
                    snake[0].dir = 4;
                    if(temp == 2)
                    {
                        snake[0].dir = 2;
                    }
                    break;
                case 77:
                    snake[0].dir = 2;
                    if(temp == 4)
                    {
                        snake[0].dir = 4;
                    }
                    break;
                case 80:
                    snake[0].dir = 3;
                    if(temp == 1)
                    {
                        snake[0].dir = 1;
                    }
                    break;
            }
        }
        if(snake[0].dir==1)
        {
            snake[0].pos[0] -=1;
            if(snake[0].pos[0]<=0){snake[0].pos[0]=24;}
        }
        else if(snake[0].dir==2)
        {
            snake[0].pos[1] +=1;
            if(snake[0].pos[1]>=39){snake[0].pos[1]=1;}
        }
        else if(snake[0].dir==3)
        {
            snake[0].pos[0] +=1;
            if(snake[0].pos[0]>=25){snake[0].pos[0]=1;}
        }
        else if(snake[0].dir==4)
        {
            snake[0].pos[1] -=1;
            if(snake[0].pos[1]<=0){snake[0].pos[1]=38;}
        }
        //Check if touched food or self
        if(snake[0].pos[0]==food[0]&&snake[0].pos[1]==food[1])
        {
            score+=100;
            length=length+1;
            execute.randomspawn();
        }
        for(int i=1;i<length+1;i++)
        {
            if(snake[0].pos[0]==snake[i].pos[0]&&snake[0].pos[1]==snake[i].pos[1])
            {
                printf("\n    GAME OVER \n    Your score was: %i\n", score);
                return 0;
            }
        }
        //Update Location and direction of Body
        for(int i=length;i>0;i--)
        {
           snake[i].pos[0] = snake[i-1].pos[0];
           snake[i].pos[1] = snake[i-1].pos[1];
           snake[i].dir = snake[i-1].dir;
           snake[i].num = i;
        }
        //update Character Values of Grid
        for(int i=0;i<26;i++)
        {
            for(int j=0;j<40;j++)
            {
                grid[i][j] = ' ';
            }
        }

        for(int i=0;i<length+1;i++)
        {
            grid[snake[i].pos[0]][snake[i].pos[1]] = bodychar;
        }
        grid[food[0]][food[1]] = '*';

        //Border
        for(int i=0;i<26;i++)
        {
            for(int j=0;j<40;j++)
            {
                if(i==0||i==25)
                {
                    grid[i][j] = '-';
                }
                if(j==0||j==39)
                {
                    grid[i][j] = '|';
                }
            }
        }
        grid[0][0]=' ';
        grid[0][39]=' ';
        grid[25][0]=' ';
        grid[25][39]='\0';
        printf("%s \nScore: %i Distance: %0.1f Direction: %i\n\r", grid , score , dis(snake[0].pos[0],snake[0].pos[1]), snake[0].dir);
        Sleep(7);
    }
}

int game::randomspawn()
{
    bool flag1,flag2;
    srand (time(NULL) );
    flag2=false;
    flag1=true;
    while(flag2==false)
    {
        flag2=false;
        flag1=true;
        food[0] = rand()%24 + 1;
        food[1] = rand()%38 + 1;
        for(int i=0;i<length+1;i++)
        {
            if(snake[i].pos[0]==food[0]&&snake[i].pos[1]==food[1])
            {
                flag1=false;
            }
        }
        if(flag1==true)
        {
            flag2==true;
            break;
        }
    }
    return 0;
}

int game::algo()
{
    int x,y,xn,xp,yn,yp,blocks[3];
    y  = snake[0].pos[0];
    yn = snake[0].pos[0] - 1;
    yp = snake[0].pos[0] + 1;
    x  = snake[0].pos[1];
    xn = snake[0].pos[1] - 1;
    xp = snake[0].pos[1] + 1;

    float dist[4];
    dist[0] = dis(yn,x);
    dist[1] = dis(y,xp);
    dist[2] = dis(yp,x);
    dist[3] = dis(y,xn);

        if(snake[0].dir==1&&grid[yn][x]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==yn&&snake[i].pos[1]==x)
            {

                if(snake[i].dir==2){snake[0].dir=4;}
                else if(snake[i].dir==4){snake[0].dir=2;}
                else if(snake[i].dir==1){snake[0].dir=4;}
                else if(snake[i].dir==3){snake[0].dir=2;}
            }
        }
    }
    else if(snake[0].dir==3&&grid[yp][x]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==yp&&snake[i].pos[1]==x)
            {
                if(snake[i].dir==2){snake[0].dir=4;}
                else if(snake[i].dir==4){snake[0].dir=2;}
                else if(snake[i].dir==1){snake[0].dir=2;}
                else if(snake[i].dir==3){snake[0].dir=4;}
            }
        }
    }
    else if(snake[0].dir==2&&grid[y][xp]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==y&&snake[i].pos[1]==xp)
            {
                if(snake[i].dir==3){snake[0].dir=1;}
                else if(snake[i].dir==1){snake[0].dir=3;}
                else if(snake[i].dir==2){snake[0].dir=1;}
                else if(snake[i].dir==4){snake[0].dir=3;}
            }
        }
    }
    else if(snake[0].dir==4&&grid[y][xn]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==y&&snake[i].pos[1]==xn)
            {
                if(snake[i].dir==3){snake[0].dir=1;}
                else if(snake[i].dir==1){snake[0].dir=3;}
                else if(snake[i].dir==2){snake[0].dir=3;}
                else if(snake[i].dir==4){snake[0].dir=1;}
            }
        }
    }
//mod upper
    if(snake[0].dir==1&&grid[yn][x]==bodychar){if(grid[y][xn]==bodychar){snake[0].dir=2;}else{snake[0].dir=4;}}
    else if(snake[0].dir==2&&grid[y][xp]==bodychar){if(grid[yn][x]==bodychar){snake[0].dir=3;}else{snake[0].dir=1;}}
    else if(snake[0].dir==3&&grid[yp][x]==bodychar){if(grid[y][xn]==bodychar){snake[0].dir=2;}else{snake[0].dir=4;}}
    else if(snake[0].dir==4&&grid[y][xn]==bodychar){if(grid[yn][x]==bodychar){snake[0].dir=3;}else{snake[0].dir=1;}}

    if(snake[0].dir==1)
    {
        if(grid[yn][xn]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yn&&snake[i].pos[1]==xn)
                {
                    if(snake[i].dir==1){snake[0].dir==2;}
                    else if(snake[i].dir==2){snake[0].dir==4;}
                    else if(snake[i].dir==4){snake[0].dir==2;}
                    else if(snake[i].dir==3){snake[0].dir==2;}
                }
            }
        }
        else if(grid[yn][xp]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yn&&snake[i].pos[1]==xp)
                {
                    if(snake[i].dir==1){snake[0].dir==4;}
                    else if(snake[i].dir==2){snake[0].dir==4;}
                    else if(snake[i].dir==4){snake[0].dir==2;}
                    else if(snake[i].dir==3){snake[0].dir==4;}
                }
            }
        }

        if(dist[0]<dist[1]&&dist[0]<dist[3]&&grid[yn][x]!=bodychar){snake[0].dir=1;}
        else if(dist[1]<dist[0]&&dist[1]<dist[3]&&grid[y][xp]!=bodychar){snake[0].dir=2;}
        else if(dist[3]<dist[1]&&dist[3]<dist[0]&&grid[y][xn]!=bodychar){snake[0].dir=4;}
    }

    else if(snake[0].dir==3)
    {
        if(grid[yp][xn]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yp&&snake[i].pos[1]==xn)
                {
                    if(snake[i].dir==1){snake[0].dir==2;}
                    else if(snake[i].dir==2){snake[0].dir==4;}
                    else if(snake[i].dir==4){snake[0].dir==2;}
                    else if(snake[i].dir==3){snake[0].dir==2;}
                }
            }
        }
        else if(grid[yp][xp]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yp&&snake[i].pos[1]==xp)
                {
                    if(snake[i].dir==1){snake[0].dir==4;}
                    else if(snake[i].dir==2){snake[0].dir==4;}
                    else if(snake[i].dir==4){snake[0].dir==2;}
                    else if(snake[i].dir==3){snake[0].dir==4;}
                }
            }
        }
        if(dist[2]<dist[1]&&dist[2]<dist[3]&&grid[yp][x]!=bodychar){snake[0].dir=3;}
        else if(dist[1]<dist[2]&&dist[1]<dist[3]&&grid[y][xp]!=bodychar){snake[0].dir=2;}
        else if(dist[3]<dist[1]&&dist[3]<dist[2]&&grid[y][xn]!=bodychar){snake[0].dir=4;}
    }
    else if(snake[0].dir==2)
    {
        if(grid[yp][xp]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yp&&snake[i].pos[1]==xp)
                {
                    if(snake[i].dir==2){snake[0].dir==3;}
                    else if(snake[i].dir==1){snake[0].dir==3;}
                    else if(snake[i].dir==3){snake[0].dir==1;}
                    else if(snake[i].dir==4){snake[0].dir==3;}
                }
            }
        }
        else if(grid[yn][xp]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yn&&snake[i].pos[1]==xp)
                {
                    if(snake[i].dir==2){snake[0].dir==1;}
                    else if(snake[i].dir==1){snake[0].dir==3;}
                    else if(snake[i].dir==3){snake[0].dir==1;}
                    else if(snake[i].dir==4){snake[0].dir==1;}
                }
            }
        }
        if(dist[1]<dist[0]&&dist[1]<dist[2]&&grid[y][xp]!=bodychar){snake[0].dir=2;}
        else if(dist[0]<dist[2]&&dist[0]<dist[1]&&grid[yn][x]!=bodychar){snake[0].dir=1;}
        else if(dist[2]<dist[0]&&dist[2]<dist[1]&&grid[yp][x]!=bodychar){snake[0].dir=3;}
    }
    else
    {
        if(grid[yp][xn]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yp&&snake[i].pos[1]==xn)
                {
                    if(snake[i].dir==2){snake[0].dir==3;}
                    else if(snake[i].dir==1){snake[0].dir==3;}
                    else if(snake[i].dir==3){snake[0].dir==1;}
                    else if(snake[i].dir==4){snake[0].dir==3;}
                }
            }
        }
        else if(grid[yn][xn]==bodychar)
        {
            for(int i=1;i<length+1;i++)
            {
                if(snake[i].pos[0]==yn&&snake[i].pos[1]==xn)
                {
                    if(snake[i].dir==2){snake[0].dir==1;}
                    else if(snake[i].dir==1){snake[0].dir==3;}
                    else if(snake[i].dir==3){snake[0].dir==1;}
                    else if(snake[i].dir==4){snake[0].dir==1;}
                }
            }
        }
        if(dist[3]<dist[0]&&dist[3]<dist[2]&&grid[y][xn]!=bodychar){snake[0].dir=4;}
        else if(dist[2]<dist[0]&&dist[2]<dist[3]&&grid[yp][x]!=bodychar){snake[0].dir=3;}
        else if(dist[0]<dist[2]&&dist[0]<dist[3]&&grid[yn][x]!=bodychar){snake[0].dir=1;}
    }

    if(snake[0].dir==1&&grid[yn][x]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==yn&&snake[i].pos[1]==x)
            {

                if(snake[i].dir==2){snake[0].dir=4;}
                else if(snake[i].dir==4){snake[0].dir=2;}
                else if(snake[i].dir==1){snake[0].dir=4;}
                else if(snake[i].dir==3){snake[0].dir=2;}
            }
        }
    }
    else if(snake[0].dir==3&&grid[yp][x]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==yp&&snake[i].pos[1]==x)
            {
                if(snake[i].dir==2){snake[0].dir=4;}
                else if(snake[i].dir==4){snake[0].dir=2;}
                else if(snake[i].dir==1){snake[0].dir=2;}
                else if(snake[i].dir==3){snake[0].dir=4;}
            }
        }
    }
    else if(snake[0].dir==2&&grid[y][xp]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==y&&snake[i].pos[1]==xp)
            {
                if(snake[i].dir==3){snake[0].dir=1;}
                else if(snake[i].dir==1){snake[0].dir=3;}
                else if(snake[i].dir==2){snake[0].dir=1;}
                else if(snake[i].dir==4){snake[0].dir=3;}
            }
        }
    }
    else if(snake[0].dir==4&&grid[y][xn]==bodychar)
    {
        for(int i=1;i<length+1;i++)
        {
            if(snake[i].pos[0]==y&&snake[i].pos[1]==xn)
            {
                if(snake[i].dir==3){snake[0].dir=1;}
                else if(snake[i].dir==1){snake[0].dir=3;}
                else if(snake[i].dir==2){snake[0].dir=3;}
                else if(snake[i].dir==4){snake[0].dir=1;}
            }
        }
    }
//mod upper
    if(snake[0].dir==1&&grid[yn][x]==bodychar){if(grid[y][xn]==bodychar){snake[0].dir=2;}else{snake[0].dir=4;}}
    else if(snake[0].dir==2&&grid[y][xp]==bodychar){if(grid[yn][x]==bodychar){snake[0].dir=3;}else{snake[0].dir=1;}}
    else if(snake[0].dir==3&&grid[yp][x]==bodychar){if(grid[y][xn]==bodychar){snake[0].dir=2;}else{snake[0].dir=4;}}
    else if(snake[0].dir==4&&grid[y][xn]==bodychar){if(grid[yn][x]==bodychar){snake[0].dir=3;}else{snake[0].dir=1;}}
}

float game::dis(int x,int y)
{
    float distance;
    distance = sqrt(pow(food[0]-x,2) + pow(food[1]-y,2));
    return distance;
}

float game::shortest(float x,float y, float z)
{
    float smallest;
    smallest = x;
    if(y<x||z<x)
    {
        if(y<z){smallest = y;}
        else{smallest = z;}
    }
    return smallest;
}

float game::greatest(float x,float y, float z)
{
    float biggest;
    biggest = x;
    if(y>x||z>x)
    {
        if(y>z){biggest = y;}
        else{biggest = z;}
    }
    return biggest;
}
