#include <stdio.h>
#include <stdlib.h>
#include "1.h"

int main(int argc, char const *argv[])
{
    long_int num;
    init(num);
    input_long_int(num);
    display(num);
    return 0;
}

void init(long_int &num)
{
    int i;
    for (i=0; i<maxN/set_num; i++)
        num.data[i] = 0;
    num.rear = 0;
    num.sign = 0;
}

int find_last(long_int num)
{
    return num.rear;
}

void insert_element(long_int &num, int data)
{
    num.data[num.rear] = data;   // 0 ~ rear-1 表头到尾指针处 存储的是 长整数高到低位数据, 即运算时顺序要倒过来
    num.rear += 1;
    
}

void input_long_int(long_int &num)
{
    int data;
    char ch = ',';
    printf("Enter a long integer: ");
    while(ch == ','){
        scanf("%d%c", &data, &ch);
        // printf("insert %d\n", data);
        insert_element(num, data);
    }
}

void display(long_int num)
{
    for (int i=0; i<num.rear; i++){
        if (i!=0)
            printf(",");
        printf("%d", num.data[i]);
    }
    printf("\n");
}

