// ht[]存放哈夫曼树，对于有n个叶子结点的哈夫曼树,总共有 2n-1个 结点
/*
    构造叶子结点和非叶子结点
        1.叶子结点(下标从0~n-1)，指针域赋初值-1
        2.非叶子结点(下表从n~2n-2)中找一个根结点，并在叶子结点中找最小和次小作为左右子树？
*/

#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
#include "HT.h"
#include "../../More C/Pointer/str.c"


void CreateHT(HTNode ht[], int n){
    int i, k;
    int lnode, rnode;
    double min1, min2;
    for (i=0; i<2*n-1; i++)
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1;  // 对所有结点的指针域都赋初值-1

    for (i=n; i<2*n-1; i++){  // 开始构造， 先扫描非叶子结点当中的最小、次小结点
        min1 = min2 = 32767;  // 记录最小、次小结点的权值
        lnode = rnode = -1;  // 记录最小、次小结点在数组中的下标
        for (k=0; k<=i-1; k++){  // k的范围: 0 ~ i-1，在未构造的二叉树结点中寻找根结点
            if (ht[k].parent==-1){  // 判断该结点是否未构造
                if(ht[k].weight<min1){  // 小于最小，则赋予最小
                    min2 = min1;
                    rnode = lnode;
                    min1 = ht[k].weight;
                    lnode = k;
                }
                else if(ht[k].weight<min2){  // 小于次小，则赋予次小
                    min2 = ht[k].weight;
                    rnode = k;
                }
            }
        }  
        ht[i].weight = ht[lnode].weight + ht[rnode].weight;
        ht[i].lchild = lnode;  // ht[i]成为双亲结点，直至所有非叶子节点都处理完毕，此时HT构造完毕
        ht[i].rchild = rnode;
        ht[lnode].parent = ht[rnode].parent = i;
    }
}

/*
    哈夫曼编码
        对当前叶子结点ht[i]
        1. 将对应的结点哈夫曼编码的hcd[i]的start置初值n  // 由于是从叶子结点到根结点，所以从末尾开始添加
        2. 找其双亲结点ht[f]
            若当前节点i为左孩子，则cd添0
            若为右孩子，则cd添1
            并将start-1，进入上一层
        3. 双亲结点重复上述操作，直至双亲结点到达根结点，最后让start指向哈夫曼最开始字符
*/
void CreateHCode(HTNode ht[], HCode hcd[], int n){  // 得到叶子结点的哈夫曼编码
    int i, f, c;  // c为叶子结点在数组Ht的下标, f为双亲结点指针
    HCode hc;
    for (i=0; i<n; i++){
        hc.start = n;
        c = i;
        f = ht[i].parent;
        while(f != -1){
            if(ht[f].lchild == c)
                hc.cd[hc.start--] = '0';
            else
                hc.cd[hc.start--] = '1';
            c = f;
            f = ht[f].parent;  // 循环继续
        }
        hc.start++;  // 指向最哈夫曼编码开始字符
        hcd[i] = hc;
    }
}

void DispHCode(HTNode ht[], HCode hcd[], int n){
    int i, k;
    double sum = 0, m = 0;
    int j;
    printf("输出哈夫曼编码：\n");
    for (i=0; i<n; i++){
        j = 0;
        printf("\t%c:\t", ht[i].data);  // 打印结点
        for(k=hcd[i].start; k<=n; k++){  // 输出该结点的hcd
            printf("%c", hcd[i].cd[k]);
            j++;
        }
        m += ht[i].weight;
        sum += ht[i].weight * j;  // 此时的j是输出的hcd的长度，可以作为该结点的度
        printf("\n");
    }
    printf("\n 平均长度=%lf\n", 1.0*sum/m);
}


int main(int argc, char const *argv[])
{
    
    int n = 8, i;
    // char *str[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    // printf("%s", str[2]);
    char str[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    double fnum[] = {0.07, 0.19, 0.02, 0.06, 0.32, 0.03, 0.21, 0.1};
    HTNode ht[M];
    HCode hcd[N];
    for(i=0; i<n; i++){
        // strcpy(&(ht[i].data), str[i]);  // ht[i].data -> char 类型 ， str[i] -> char* 类型
        ht[i].data = str[i];
        ht[i].weight = fnum[i];
    }
    printf("\n");
    CreateHT(ht, n);
    CreateHCode(ht, hcd, n);
    DispHCode(ht, hcd, n);
    printf("\n");
    return 0;
}
