#define maxN 100
#define set_num 4
typedef struct sqlist
{
    int data[maxN/set_num];
    int rear;  // 记录最低位的指针
    int sign;  // 符号标志
}long_int;

void init(long_int &num);
int find_top(long_int num);  // return top
void insert_element(long_int &num, int data);
void input_long_int(long_int &num);
void display(long_int num);
