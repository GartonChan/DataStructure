#include <stdio.h>
#include <stdlib.h>

/*
    用队列求解迷宫问题: 求出从入口到出口的路径.
    空白表示通道,阴影(灰色)表示墙.
    所求路径必须是简单路径,即所得的路径上不能重复出现同一通道块

    为了表示迷宫,设置一个数组mg,其中每个元素表示一个方块的状态
    0值表示通道, 1值表示墙, 图示迷宫对应mg如下
*/

#include "SqQueue.cpp"

#define M 10
#define N 10
#define MaxSize 100

int mg[M][N]={
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

/*
    对于迷宫中的每个方块,有上下左右四个相邻方块
    第i行j列的当前方块位置为(i,j)
    现规定上方为方位0,顺时针方向递增编号.
    四个方块的编号(坐标)可以计算得到
    在试探过程,按顺时针方向从0到3查找下一个可走的方块
    直到找到出口块或无路可走位置
    记录每一个方块的前一个方块,走到出口时,由出口倒回入口,
    此时可以得到一条通道.

    解决这个问题,效率最高的是选用队列.
*/

void print(int front);
void print_Stack(int front);
int mgpath(int xi, int yi, int xe, int ye);

// 使用一个队列Qu记录每个走过的方块,整体构成一条路径
struct{
    int i,j;  // 方块的位置
    int pre;  // 记录前一块在队列的下标
}Qu[MaxSize];  // 结构体类型数组
int front = -1, rear = -1;  // 定义队首队尾指针初始化为-1, 向队列外 为空.

// 由于这里是用的队列Qu不是循环队列
// 因此在出队时,不会将出队元素真正从队列中删除
// 因为要利用它输出路径

/*
    
    算法思路:
        1.入口块入队
        2.Qu不为空时循环
            先出队一次(由于不是循环队列,指针往后移一位而出队元素其实还在队列中)
            称此时的这个出队的方块为 当前方块 ,front为该方块在Qu中的下标  -> 最后的Qu就是路径
          (1).如果当前方块是出口,则输出路径并结束.
          (2).否则,每次都按顺时针方向找出当前方块的四个方位中可走的相邻方块
            并将可走的方块插入到Qu中,并且将其中的pre设为
            本搜索路径中上一块方块在Qu中的下标值
            也就是当前方块的front值,
            并将相邻方块对应的mg数组值置-1,以避免重复搜索
          (3).若队列为空仍未找到出口,即不存在路径

    实际上,本算法的思想是从入口方块开始,一层一层向外扩展可走的点
    直到找到出口为止,这个方法就是: 图的广度有限搜索算法
    
*/

int mgpath(int xi, int yi, int xe, int ye){  // 搜索路径(xi,yi) -> (xe, ye)
    int i, j, di;
    int m, n, cnt=1;
    rear++;  //Qu不是循环队列,入队无需作模运算,直接进一即可
    Qu[rear].i = xi;
    Qu[rear].j = yi;
    Qu[rear].pre = -1;  // (xi, yi)入口方块入队
    mg[xi][yi] = -1;  // 赋值-1 避免回过来重复搜索
    while (front<rear)  // 队列非空时循环 
    {
        front++;  // 出队但不删除元素
        i = Qu[front].i;
        j = Qu[front].j;
        if(i == xe && j == ye){
            printf("-front-\t-i-\t-j-\t-pre-\n");
            for(m=0; m<=front; m++){
                printf("  %d\t %d\t %d\t %d\n",m, Qu[m].i, Qu[m].j, Qu[m].pre);
            }
            print_Stack(front);
            print(front);
            return 1;
        }  // 1.将当前方块出队并判断是否为出口方块

        for(di=0; di<4; di++){  // 2.相邻4个方块顺时针依次判定为空后入队
            switch (di)
            {
            case 0:
                i = Qu[front].i-1;
                j = Qu[front].j;
                break;
            case 1:
                i = Qu[front].i;
                j = Qu[front].j+1;
                break;
            case 2:
                i = Qu[front].i+1;
                j = Qu[front].j;
                break;
            case 3:
                i = Qu[front].i;
                j = Qu[front].j-1;
            } 
            if (mg[i][j]==0){  // 配合switch-case将四个相邻方块中可走的方块入队
                rear++;  // 相邻方块插入队列
                Qu[rear].i = i;
                Qu[rear].j = j;
                Qu[rear].pre = front;  // 将队列Qu中该(相邻)方块的pre赋值为路径前一方块(当前方块)的下标
                mg[i][j]=-1;  // 将其赋值为-1,以避免(在其他路径时)重复搜索
            }
        }
        printf("\t < %d >\n\n", cnt++);
        printf("\t--0--\t--1--\t--2--\t--3--\t--4--\t--5--\t--6--\t--7--\t--8--\t--9--\n\n");
        for(m=0; m<M; m++){
            printf("%-d\t", m);
            for(n=0; n<N; n++)
                printf("|%3d|\t", mg[m][n]);
            printf("\n\t------------------------------------------------------------------------------\n");
        }
        printf("\n*******************************************************************************************\n\n\n");
        // if(mg[xe][ye] == -1)
        //     break;
    }
    return 0;
}


void print(int front){
    int m = front, n, ns = 0;  // ns仅用于输出时计数换行
    printf("\n");
    do{
        n = m; 
        m = Qu[m].pre;  // m记录的是当前块, n记录的是当前块的前一块
        Qu[n].pre = -1;  // 沿路径逆向到入口,并同时做标记(-1)以便正向搜索输出
    }while(m != 0);
    printf("迷宫路径如下:\n");
    while(m<=front){
        //正向搜索队列中pre为-1的方块,构成正向路径
        if (Qu[m].pre == -1){  
            ns++;
            printf("\t(%d,%d)", Qu[m].i, Qu[m].j);
            if (ns%5==0)
            printf("\n");
        }
        m++;
    }
    printf("\n");
}
//  这样的处理过程效率不高
//  可以思考用栈实现
//  栈->先进后出,后进先出
    // 但是牺牲了空间来换取效率)

/*
    改-1 变成 入栈保存
    然后输出栈中数据即为正向路径
*/

void print_Stack(int front){
    int n = front, ns = 0;
    int SqStack[30];
    int top=-1;
    printf("\n");
    top++;
    SqStack[top] = front;
    // printf("Qu[front].(i,j):(%d,%d)\n", Qu[front].i, Qu[front].j);
    do{
        top++;
        SqStack[top] = Qu[n].pre;
        n = Qu[n].pre;
    } while (n!=0);
    printf("迷宫路径如下:\n");
    while(top>=0){
        printf("\t(%d,%d)",Qu[SqStack[top]].i, Qu[SqStack[top]].j);
        ns++;
        if(ns%5 == 0)
            printf("\n");
        top--;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    // mgpath(1, 1, 8, 8);
    SqQueue *q;
    ElemType e;
    InitQueue(q);
    enQueue(q, 1);
    enQueue(q, 3);
    enQueue(q, 5);
    enQueue(q, 7);
    enQueue(q, 9);
    DispQueue(q);
    reverse(q);  // 测试队列反转函数
    DispQueue(q);
    mgpath(1, 1, 8, 8);
    return 0;
}
