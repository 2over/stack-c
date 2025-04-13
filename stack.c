#include <stdio.h>
#include <stdlib.h>

// 栈帧结构体，假设所有函数的栈帧都一样，都仅包含3个布局变量
typedef struct Frame {
    struct Frame* pre; // 指向上一个栈帧
    int local1;
    int local2;
    int local3;
} frame;

// 堆栈
typedef struct Stack {
    frame* base; //栈底
    frame* top; // 栈顶
    int size; //堆栈大小
}stack;

void initStack(stack* stack); //初始化
void push(stack* mystack, frame* nextFrame);
void pop(stack* mystack);
void iterate(stack *mystack);
int main(int argc, char const *argv[]) {
    // 定义一个堆栈
    stack* mystack = (stack*)malloc(sizeof(struct Stack));
    printf("sizeof(struct Frame) = %lu\n", sizeof(struct Frame));

    // 初始化堆栈
    initStack(mystack);

    // 压入第1个栈帧
    frame* myframe = (frame*)malloc(sizeof(struct Frame));
    printf("当前栈帧起始地址是: %p\n", myframe);
    myframe->local1 = 1;
    myframe->local2 = 2;
    myframe->local3 = 3;
    push(mystack, myframe);

    // 压入第2个栈帧
    myframe = (frame*)malloc(sizeof(struct Frame));
    printf("当前栈帧起始地址是: %p\n", myframe);
    myframe->local1 = 5;
    myframe->local2 = 6;
    myframe->local3 = 7;
    push(mystack, myframe);

    // 压入第3个栈帧
    myframe = (frame*)malloc(sizeof(struct Frame));
    printf("当前栈帧起始地址是: %p\n", myframe);
    myframe->local1 = 8;
    myframe->local2 = 9;
    myframe->local3 = 10;
    push(mystack, myframe);

    // 遍历堆栈
    iterate(mystack);

    // 出栈
    pop(mystack);
    iterate(mystack);

    pop(mystack);
    iterate(mystack);

    pop(mystack);
    iterate(mystack);

    pop(mystack);

    return 0;
}
// 初始化堆栈
void initStack(stack *stack) {
    stack->base = NULL;
    stack->top = NULL;
    stack->size = 0;
}
// 压栈
void push(stack* mystack, frame *nextFrame) {
    // 如果当前堆栈为空，则将栈顶和栈底同时指向第一个栈帧
    if (mystack->size == 0) {
        mystack->base = nextFrame;
        mystack->top = nextFrame;
    }

    nextFrame->pre = mystack->top; // 当前栈帧的上一个栈帧是栈顶
    mystack->top = nextFrame; // 栈顶变成了当前栈帧

    mystack->size++;// 将堆栈数量加1
}

// 出栈
void pop(stack* mystack) {
    int size = mystack->size;
    if (size == 0) {
        printf("%s\n", "当前堆栈为空,不能出栈");
        return ;
    }

    frame *currentFrame = mystack->top; // 获取当前堆栈顶部栈帧
    mystack->top = mystack->top->pre; // 将当前栈顶指向上一个栈帧

    // 释放栈顶栈帧
    free(currentFrame);
    mystack->size--;
    printf("成功弹出一个栈顶栈帧\n\n");
}

// 遍历堆栈
void iterate(stack* mystack) {
    if (mystack->size == 0) {
        printf("%s\n", "当前堆栈为空，遍历终止");
        return;
    }

    int size = mystack->size;
    printf("*****************************当前堆栈共有 %d 个栈帧*****************************\n",size);
    frame *currentFrame = mystack->top;
    while (size > 0) {
        printf("当前是第 %d 个栈帧\n", size);
        printf("    local1 = %d\]n", currentFrame->local1);
        printf("    local2 = %d\]n", currentFrame->local2);
        printf("    local3 = %d\]n", currentFrame->local3);

        currentFrame = currentFrame->pre;
        size--;
    }
}

