#define N 50  // 叶子结点数
#define M 2*N-1   // 二叉树树中的结点总数


// 哈夫曼树的结点
typedef struct{
    char data;  // 结点值
    double weight;  // 权重
    int parent;  // 双亲结点, 结点没用指针,在哈夫曼编码中呈现了不同的作用
    int lchild;  // 左孩子结点
    int rchild;  // 右孩子结点
}HTNode;

// 哈夫曼编码hcd类型定义
typedef struct{
    char cd[N];   // 数组存放哈夫曼编码
    int start;  // 表示起始下标
}HCode;
// 不等长编码  cd[start ~ n]存放结点的哈夫曼编码,start是起始下标

void CreateHT(HTNode ht[], int n);
void CreateHCode(HTNode ht[], HCode hcd[], int n);
void DispHCode(HTNode ht[], HCode hcd[], int n);