#include "sequenceStack.cpp"

// 十进制数转化为八进制数
void conversion(){
    SqStack *S;
    int N;
    char e = 0;
    InitStack(S);
    scanf("%d", &N);  // 读取一个十进制数
    while (N){  // 循环除八取余  ->  
        Push(S, N % 8);   // 用栈实现的好处: 连续进栈连续出栈是反过来的
        N = N / 8;
    }
    while (S->top!=-1)  // 从栈顶到栈底遍历依次打印
    {
        Pop(S, e);  // 出栈一个 打印一个
        printf("%d", e);
    }
    printf("\n");
    
}


// 判断表达式中的三种括号是否正确匹配
int correct(char exp[], int n){  // n为表达式中字符个数
    char st[MaxSize];  // 作为栈区存放括号
    int top = -1, i = 0, tag = 1;  // 分别表示栈顶位置, 索引位置, 假设为匹配
    while(i < n && tag){ // 没扫描完成 并且 尚且匹配
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{'){
            top++;
            st[top]=exp[i];
        }// 遇到左括号 则将其进栈
        if(exp[i]==')')
            if(st[top]==')') top--;
            else tag = 0;
        if(exp[i]==']')
            if(st[top]=='[') top--;
            else tag = 0;
        if(exp[i]=='}')
            if(st[top]=='{') top--;
            else tag = 0;
        i++;  // 字符串下标后移一个位置
    }  // 表达式扫描完毕
    if(top>-1) tag=0;  // 栈空才匹配
    return tag;
}


// 常用的表达式:中缀表达式  优先级,括号,计算法则
// 后缀表达式!! 无括号 只有操作数和运算符 解决了优先级问题  全是从左往右

// 算术表达式求值过程:
//   1.算术表达式转换成后缀表达式
//   2.对后缀表达式求值

// 运算符的优先级处理,设立运算符栈

void trans(char str[], char exp[]){
    struct 
    {
        char data[MaxSize];
        int top;
    }op;
    char ch;
    int i = 0, t = 0; // i为str下标, t为exp下标
    op.top = -1;
    ch = str[i];

    while(ch!='\0'){
        switch (ch)
        {
        case '(':
            op.top++;
            op.data[op.top] = ch;
            break;
        case ')':
            while(op.data[op.top]!='('){
                exp[t] = op.data[op.top];
                op.top--;
                t++;
            }
            op.top--;  // 与 ) 匹配的 ( 出栈
            break;
        case '+':
        case '-':
            while (op.top!=-1 && op.data[op.top]!='(')
            {
                exp[t]=op.data[op.top];  // op出栈到exp
                op.top--;
                t++;  // exp下标+1
            }
            op.top++;
            op.data[op.top]=ch;  // ch入栈到op
            break;
        case '*':
        case '/':
            while (op.top!=-1 && ( op.data[op.top]=='*' || op.data[op.top]=='/') )
            {
                exp[t]=op.data[op.top];
                op.top--;  // 运算符出栈
                t++;  // 表达式下标后移
            }
            op.top++;
            op.data[op.top]=ch;
            break;
        default:
            while(ch >= '0' && ch <= '9'){
                exp[t]=ch;
                t++;
                i++;
                ch = str[i];
            }
            i--;
            exp[t]='#';  //O 用#标识数值串结束
            t++;
        }
        i++;
        ch=str[i];
    }
    while(op.top!=-1){
        exp[t]=op.data[op.top];
        op.top--;
        t++;
    }
    exp[t]='\0';
}


float compvalue(char *exp){
    struct 
    {
        float data[MaxSize];
        int top;
    }st;
    float d;
    st.top=-1;
    while (*exp!='\0')
    {
        switch(*exp){
            case '+':
                st.data[st.top-1] = st.data[st.top-1] + st.data[st.top];
                st.top--;
                break;
            case '-':
                st.data[st.top-1] = st.data[st.top-1] - st.data[st.top];
                st.top--;
                break;
            case '*':
                st.data[st.top-1] = st.data[st.top-1] * st.data[st.top];
                st.top--;
                break;
            case '/':
                if(st.data[st.top]!=0){
                    st.data[st.top-1] = st.data[st.top-1] / st.data[st.top];
                    st.top--;
                }else{
                    printf("\n\t除零错误!\n");
                    exit(0);  // 异常退出
                }
                break;
            default:
                d = 0;
                while(*exp >= '0' && *exp <= '9'){
                    // printf("*exp = %c\n", *exp);
                    d = 10*d + *exp -'0';
                    exp++;
                }
                // printf("即将入栈的数字 %.2f\n", d);
                st.top++;
                st.data[st.top]=d;
            }
            exp++;
    }
    return st.data[st.top];
}

int main(int argc, char const *argv[])
{
    char str[]="(56-20)/(4+2)";
    char exp[MaxSize];
    trans(str, exp);
    printf("中缀表达式:%s\n", str);
    printf("后缀表达式:%s\n", exp);
    printf("表达式的值:%.2f\n", compvalue(exp));
    conversion();

    return 0;
}
