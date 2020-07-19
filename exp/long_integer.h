#define MaxN 25

typedef struct node
{
    int data;
    struct node *next;  
    struct node *prior;
} Node;  // 双向链表

typedef struct head
{
    int sign;  // 符号标志位
    struct node *next;
    struct node *rear;  // 尾结点
    int node_num;
} Head;

Head *create();
void init(Head *h);
void insert_node_head(Head *h, int data);
void insert_node_rear(Head *h, int data);
Node *find_last(Head *h);
void disp_long_integer(Head *h);
void input_long_integer(Head *h);
int judge_sign(Head *h);
Head *add(Head *h1, Head *h2);
Head *sub(Head *h1, Head *h2);