队列,简称队
是运算受限的线性表(先进先出,后进后出)
其限制为  一端插入. 另一端删除

插入端称为 队尾    操作称为 入队 或 进队
删除端称为 队首    操作称为 出队 或 离队

元素出队后,其后继元素就成为新的队首元素

front == rear 队空条件
而rear == MaxSize-1 是不能作为队满的条件的
因为可能会有元素出队后仍满足这个条件的情况,而此时并不是队满的

为了充分使用数组的存储空间,将数组的前端后端连接起来
形成了一个环形的顺序表,即把存储队列元素的表从逻辑上看成一个环
这称为循环队列
这时候,当指针为MaxSize-1后,再前进一个位置便自动到0,可用取余运算实现:
    队首指针进1 front = (front + 1) % MaxSize
    队尾指针进1 rear = (rear + 1) % MaxSize
    初始化时都置0 front = rear = 0
因此,队满条件为: (rear+1) % MaxSize == front 
    此时必须浪费一个内存空间存放空的front, 否则会有rear == front成立


即 队列的 队空条件: rear == front
    环形队列的队满条件: (rear+1) % MaxSize == front
