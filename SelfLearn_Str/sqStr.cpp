#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20

/*
    串的顺序存储有两种方法: 1.紧缩格式  2.非紧缩格式
        关键在于看存储密度的大小(一个内存单元存储几个字符)
*/

// 对于非紧缩格式的顺序串,我们有如下定义:
typedef struct 
{
    char data[MaxSize];
    int length;
}SqString;


void StrAssign(SqString &s, char cstr[]){  // 串是不包含'\0'的
    int i;
    for (i=0; cstr[i]!='\0'; i++)
        s.data[i] = cstr[i];
    s.length = i;
}


void StrCopy(SqString &s, SqString t){  // t -> s
    int i;
    for(i=0; i<t.length; i++)
        s.data[i] = t.data[i];
    s.length = t.length;
}


int StrEqual(SqString s, SqString t){
    int same = 1, i;
    if(s.length != t.length)
        same = 0;
    else
        for (i = 0; i < s.length; i++)
            if(s.data[i] != t.data[i]){
                same = 0;
                break;
            }
    return same;    
}


int StrLength(SqString s){
    return s.length;
}


SqString Concat(SqString s, SqString t){   // 返回连接后的新串str
    SqString str;
    int i;
    str.length = s.length + t.length;
    for(i=0; i<s.length; i++)
        str.data[i] = s.data[i];
    for(i=0; i<t.length; i++)
        str.data[s.length+i] = t.data[i];
    return str;
}


SqString SubStr(SqString s, int i, int j){  // 返回串s从第i个字符起长度为j个字符的新串
    SqString str;
    int k ;
    str.length = 0;
    if(i<=0 || i>s.length || j<0 || j>s.length)
        return str;  // 由于错误返回空串.
    for(k=i-1; k<i+j-1; k++)
        str.data[k-i+1] = s.data[k];
    str.length = j;
    return str;
}


SqString InsertStr(SqString s1, int i, SqString s2){  // 将串s2插入到s1的第i个字符处(s2第1个字符成为第i个字符)
    int j;
    SqString str;
    str.length = 0;
    if(i<=0 || i>s1.length+1)
        return str;  // 由于错误返回空串
    for(j=0; j<i-1; j++)
        str.data[j] = s1.data[j]; // 前i-1个字符
    for(j=0; j<s2.length; j++)
        str.data[i-1+j] = s2.data[j];
    for(j=i-1; j<s1.length; j++)
        str.data[s2.length+j];  // j是s1中的索引位置
    str.length = s1.length + s2.length;
    return str;
}


SqString DelStr(SqString s, int i, int j){  // 删去串s从第i个位置起长度为j个字符的字串并返回新串
    int k;
    SqString str;
    str.length = 0;
    if(i<=0 || i>s.length || i+j>s.length+1)
        return str;  // 由于错误返回空串
    for(k=0; k<i-1; k++)  // s.data[0, 1, ..., i-2] 复制到str
        str.data[k] = s.data[k];
    for(k=i+j-1; k<s.length; k++)  // s.data[i+j-1, ... ,s.length-1]复制到str
        str.data[k-j] = s.length - j;
    str.length = s.length - j;
    return str;
}


SqString RepStr(SqString s, int i, int j, SqString t){  
// 对串s第i个字符开始的j个字符构成的字串用串t(完整的串t)替换,并返回新串
    int k;
    SqString str;
    str.length = 0;
    if(i<=0 || i>s.length || i+j-1>s.length)
        return str;
    for(k=0; k<i-1; k++)  // 复制前i-1个字符
        str.data[k] = s.data[k];
    for(k=0; k<t.length; k++)  // t复制到其后
        str.data[i-1+k] = t.data[k];
    for(k=i-1+j; k<s.length; k++)  // 下标从i-1+j开始用剩下的s部分从j后覆盖
        str.data[k-j+t.length] = s.data[k];  // 即从[i-1+t.length]到[s.length-j+t.length-1]
    return str;
}


void DispStr(SqString s){
    int i;
    if(s.length>0){
        for(i=0; i<s.length; i++)
            printf("%c", s.data[i]);
        printf("\n");
    }
}