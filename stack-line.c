#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 堆栈初始大小
#define DEFAULT_SIZE 2
// 堆栈扩充因子
#define EXPAND_FACTORY 1.75

// 栈帧结构体，假设所有函数的栈帧都一样，都仅包含3个布局变量
typedef struct Frame {
    struct Frame *pre; // 指向上一个栈帧
    int local1;
    int local2;
    int local3;
} frame;

// 堆栈
typedef struct Stack {
    frame *base; //栈底
    frame *top; // 栈顶
    int size; //堆栈大小
    int maxSize; // 堆栈最大大小
} stack;

void initStack(stack *stack); //初始化
void push(stack *mystack, frame *nextFrame);

void pop(stack *mystack);

void iterate(stack *mystack);

void expand(stack *mystack); //扩容

int main(int argc, char const *argv[]) {
    // 定义一个堆栈
    stack *mystack = (stack *) malloc(sizeof(struct Stack));
    // 初始化堆栈
    initStack(mystack);

    // 压入第1个栈帧
    frame myframe;
    myframe.local1 = 1;
    myframe.local2 = 2;
    myframe.local3 = 3;
    push(mystack, &myframe);

    // 压入第2个栈帧
    myframe.local1 = 5;
    myframe.local2 = 6;
    myframe.local3 = 7;
    push(mystack, &myframe);

    // 压入第3个栈帧
    myframe.local1 = 8;
    myframe.local2 = 9;
    myframe.local3 = 10;
    push(mystack, &myframe);

    // 压入第3个栈帧
    myframe.local1 = 11;
    myframe.local2 = 12;
    myframe.local3 = 13;
    push(mystack, &myframe);

    // 遍历栈帧
    iterate(mystack);
    // 出栈
    pop(mystack);
    iterate(mystack);

    pop(mystack);
    iterate(mystack);

    pop(mystack);
    iterate(mystack);

    pop(mystack);

    free((void *) mystack->base);

    return 0;
}

// 初始化堆栈
void initStack(stack *stack) {
    stack->size = 0;
    stack->maxSize = DEFAULT_SIZE;

    // 初始化堆栈空间
    long address = (long) malloc(sizeof(struct Frame) * DEFAULT_SIZE);
    stack->base = (frame *) address;
    stack->top = (frame *) address;
}

// 压栈
void push(stack *mystack, frame *nextFrame) {
    // 扩容
    expand(mystack);

    frame *newFrame;
    frame *top = mystack->top;

    // 如果当前堆栈为空，则将栈顶和栈底同时指向第一个栈帧
    if (mystack->size == 0) {
        newFrame = top;
    } else {
        newFrame = ++top;
    }

    // frame* newFrame = (frame*)(++top); // 将栈顶指针往前移动一个栈帧的距离
    printf("压入第%d个栈帧, 当前栈帧起始地址是 %p\n\n", mystack->size + 1, newFrame);
    newFrame->local1 = nextFrame->local1;
    newFrame->local2 = nextFrame->local2;
    newFrame->local3 = nextFrame->local3;

    newFrame->pre = mystack->top; // 当前栈帧的上一个栈帧是栈顶
    mystack->top = newFrame; // 栈顶变成了当前栈帧
    mystack->size++; // 将堆栈数量加1
}

// 出栈
void pop(stack *mystack) {
    int size = mystack->size;
    if (size == 0) {
        printf("%s\n", "当前堆栈为空, 不能出栈");
        return;
    }

    frame *currFrame = mystack->top; // 获取当前堆栈顶部栈帧
    mystack->top = mystack->top->pre; // 将当前栈顶指向上一个栈帧

    // 释放栈顶栈帧
    mystack->size--;
    printf("成功弹出一个栈顶栈帧\n\n");
}

// 扩容
void expand(stack *mystack) {
    if (mystack->size == mystack->maxSize) {
        // 扩容
        int maxSize = mystack->size * EXPAND_FACTORY; //计算扩容后的大小
        long address = (long) malloc(sizeof(struct Frame) * maxSize);
        memcpy((void *) address, mystack->base, mystack->size * sizeof(struct Frame));

        // 重定向栈顶和栈底
        mystack->base = (frame *) address;
        mystack->top = (frame *) (address + (mystack->size - 1) * sizeof(struct Frame));

        mystack->maxSize = maxSize;

        // 重新关联当前栈帧与上一个栈帧之间的关系
        for (int i = 1; i < mystack->size; i++) {
            frame *currFrame = (frame *) address;
            frame *tmp = (frame *) address;
            frame *nextFrame = ++tmp;// 获取下一个栈帧
            nextFrame->pre = currFrame;

            address = (long) nextFrame;
        }

        printf(">>>>>>>>>>>扩容成功, 申请的堆栈地址是 %p, 扩容后的栈帧栈顶地址是 %p\n", mystack->base, mystack->top);
    }
}

// 遍历堆栈
void iterate(stack *mystack) {
    if (mystack->size == 0) {
        printf("%s\n", "当前堆栈为空,遍历终止");
        return;
    }

    int size = mystack->size;
    printf("**************** 当前堆栈共有 %d 个栈帧 ****************\n", size);
    frame *currFrame = mystack->top;
    while (size > 0) {
        printf("当前是第 %d 个栈帧，其地址是 %p\n", size, currFrame);
        printf(" local1 = %d\n", currFrame->local1);
        printf(" local2 = %d\n", currFrame->local2);
        printf(" local3 = %d\n", currFrame->local3);

        currFrame = currFrame->pre;
        size--;
    }
}