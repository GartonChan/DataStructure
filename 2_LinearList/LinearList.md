/* 

    线性表： 
        具有相同特性的数据元素的一个有限序列。
        序列中所含元素个数 -> 线性表的长度 n （ >= 0 ）
        一般表示为：(a1, a2, ..., ai, ai+1, ..., an) 
        表头、表尾元素


    线性表的基本运算：
        1.初始化 InitList(&L)  ：构造空表

        2.销毁 DestroyList(&L)  ： 释放空间

        3.ListEmpty(L)  : True \ False

        4.ListLength(L)

        5.DispList(L) : 不为空时，顺序显示各结点的值域

        6.GetElem(L, i, &e)  : 通过 引用形参e 返回 L 中 第i个 元素的值，成功返回1, 不存在返回0

        7.LocateElem(L, e)  : 返回 L 中 第一个 与 e相等的元素的位序。 若不存在返回0

            6 和 7 要区分开来
            
        8.ListInsert(&L, i, e)  : i >= 1 && i <= ( ListLength(L)+1 )  i范围是1 ～ len+1 保证插入元素在第i个位置。

        9.ListDelete(&L, i, &e)  : 删除第i个元素 并且通过引用变量e返回， 同时 len = len - 1


    集合A和集合B 作 并集 得到 集合C 的 算法：
        1.初始化LC

        2.LA 通过 遍历LA(for循环中对LA: GetElem) 复制(对LC: ListInsert)到LC

        3.再通过遍历LB筛选出不存在LC即不存在LA的元素
        (for循环中嵌一条if判断，对LB: GetElem 再对LC: LocateElem)并复制到LC(对LC: ListInsert)

*/