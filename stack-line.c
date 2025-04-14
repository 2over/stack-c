#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��ջ��ʼ��С
#define DEFAULT_SIZE 2
// ��ջ��������
#define EXPAND_FACTORY 1.75

// ջ֡�ṹ�壬�������к�����ջ֡��һ������������3�����ֱ���
typedef struct Frame {
    struct Frame *pre; // ָ����һ��ջ֡
    int local1;
    int local2;
    int local3;
} frame;

// ��ջ
typedef struct Stack {
    frame *base; //ջ��
    frame *top; // ջ��
    int size; //��ջ��С
    int maxSize; // ��ջ����С
} stack;

void initStack(stack *stack); //��ʼ��
void push(stack *mystack, frame *nextFrame);

void pop(stack *mystack);

void iterate(stack *mystack);

void expand(stack *mystack); //����

int main(int argc, char const *argv[]) {
    // ����һ����ջ
    stack *mystack = (stack *) malloc(sizeof(struct Stack));
    // ��ʼ����ջ
    initStack(mystack);

    // ѹ���1��ջ֡
    frame myframe;
    myframe.local1 = 1;
    myframe.local2 = 2;
    myframe.local3 = 3;
    push(mystack, &myframe);

    // ѹ���2��ջ֡
    myframe.local1 = 5;
    myframe.local2 = 6;
    myframe.local3 = 7;
    push(mystack, &myframe);

    // ѹ���3��ջ֡
    myframe.local1 = 8;
    myframe.local2 = 9;
    myframe.local3 = 10;
    push(mystack, &myframe);

    // ѹ���3��ջ֡
    myframe.local1 = 11;
    myframe.local2 = 12;
    myframe.local3 = 13;
    push(mystack, &myframe);

    // ����ջ֡
    iterate(mystack);
    // ��ջ
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

// ��ʼ����ջ
void initStack(stack *stack) {
    stack->size = 0;
    stack->maxSize = DEFAULT_SIZE;

    // ��ʼ����ջ�ռ�
    long address = (long) malloc(sizeof(struct Frame) * DEFAULT_SIZE);
    stack->base = (frame *) address;
    stack->top = (frame *) address;
}

// ѹջ
void push(stack *mystack, frame *nextFrame) {
    // ����
    expand(mystack);

    frame *newFrame;
    frame *top = mystack->top;

    // �����ǰ��ջΪ�գ���ջ����ջ��ͬʱָ���һ��ջ֡
    if (mystack->size == 0) {
        newFrame = top;
    } else {
        newFrame = ++top;
    }

    // frame* newFrame = (frame*)(++top); // ��ջ��ָ����ǰ�ƶ�һ��ջ֡�ľ���
    printf("ѹ���%d��ջ֡, ��ǰջ֡��ʼ��ַ�� %p\n\n", mystack->size + 1, newFrame);
    newFrame->local1 = nextFrame->local1;
    newFrame->local2 = nextFrame->local2;
    newFrame->local3 = nextFrame->local3;

    newFrame->pre = mystack->top; // ��ǰջ֡����һ��ջ֡��ջ��
    mystack->top = newFrame; // ջ������˵�ǰջ֡
    mystack->size++; // ����ջ������1
}

// ��ջ
void pop(stack *mystack) {
    int size = mystack->size;
    if (size == 0) {
        printf("%s\n", "��ǰ��ջΪ��, ���ܳ�ջ");
        return;
    }

    frame *currFrame = mystack->top; // ��ȡ��ǰ��ջ����ջ֡
    mystack->top = mystack->top->pre; // ����ǰջ��ָ����һ��ջ֡

    // �ͷ�ջ��ջ֡
    mystack->size--;
    printf("�ɹ�����һ��ջ��ջ֡\n\n");
}

// ����
void expand(stack *mystack) {
    if (mystack->size == mystack->maxSize) {
        // ����
        int maxSize = mystack->size * EXPAND_FACTORY; //�������ݺ�Ĵ�С
        long address = (long) malloc(sizeof(struct Frame) * maxSize);
        memcpy((void *) address, mystack->base, mystack->size * sizeof(struct Frame));

        // �ض���ջ����ջ��
        mystack->base = (frame *) address;
        mystack->top = (frame *) (address + (mystack->size - 1) * sizeof(struct Frame));

        mystack->maxSize = maxSize;

        // ���¹�����ǰջ֡����һ��ջ֮֡��Ĺ�ϵ
        for (int i = 1; i < mystack->size; i++) {
            frame *currFrame = (frame *) address;
            frame *tmp = (frame *) address;
            frame *nextFrame = ++tmp;// ��ȡ��һ��ջ֡
            nextFrame->pre = currFrame;

            address = (long) nextFrame;
        }

        printf(">>>>>>>>>>>���ݳɹ�, ����Ķ�ջ��ַ�� %p, ���ݺ��ջ֡ջ����ַ�� %p\n", mystack->base, mystack->top);
    }
}

// ������ջ
void iterate(stack *mystack) {
    if (mystack->size == 0) {
        printf("%s\n", "��ǰ��ջΪ��,������ֹ");
        return;
    }

    int size = mystack->size;
    printf("**************** ��ǰ��ջ���� %d ��ջ֡ ****************\n", size);
    frame *currFrame = mystack->top;
    while (size > 0) {
        printf("��ǰ�ǵ� %d ��ջ֡�����ַ�� %p\n", size, currFrame);
        printf(" local1 = %d\n", currFrame->local1);
        printf(" local2 = %d\n", currFrame->local2);
        printf(" local3 = %d\n", currFrame->local3);

        currFrame = currFrame->pre;
        size--;
    }
}