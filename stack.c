#include <stdio.h>
#include <stdlib.h>

// ջ֡�ṹ�壬�������к�����ջ֡��һ������������3�����ֱ���
typedef struct Frame {
    struct Frame* pre; // ָ����һ��ջ֡
    int local1;
    int local2;
    int local3;
} frame;

// ��ջ
typedef struct Stack {
    frame* base; //ջ��
    frame* top; // ջ��
    int size; //��ջ��С
}stack;

void initStack(stack* stack); //��ʼ��
void push(stack* mystack, frame* nextFrame);
void pop(stack* mystack);
void iterate(stack *mystack);
int main(int argc, char const *argv[]) {
    // ����һ����ջ
    stack* mystack = (stack*)malloc(sizeof(struct Stack));
    printf("sizeof(struct Frame) = %lu\n", sizeof(struct Frame));

    // ��ʼ����ջ
    initStack(mystack);

    // ѹ���1��ջ֡
    frame* myframe = (frame*)malloc(sizeof(struct Frame));
    printf("��ǰջ֡��ʼ��ַ��: %p\n", myframe);
    myframe->local1 = 1;
    myframe->local2 = 2;
    myframe->local3 = 3;
    push(mystack, myframe);

    // ѹ���2��ջ֡
    myframe = (frame*)malloc(sizeof(struct Frame));
    printf("��ǰջ֡��ʼ��ַ��: %p\n", myframe);
    myframe->local1 = 5;
    myframe->local2 = 6;
    myframe->local3 = 7;
    push(mystack, myframe);

    // ѹ���3��ջ֡
    myframe = (frame*)malloc(sizeof(struct Frame));
    printf("��ǰջ֡��ʼ��ַ��: %p\n", myframe);
    myframe->local1 = 8;
    myframe->local2 = 9;
    myframe->local3 = 10;
    push(mystack, myframe);

    // ������ջ
    iterate(mystack);

    // ��ջ
    pop(mystack);
    iterate(mystack);

    pop(mystack);
    iterate(mystack);

    pop(mystack);
    iterate(mystack);

    pop(mystack);

    return 0;
}
// ��ʼ����ջ
void initStack(stack *stack) {
    stack->base = NULL;
    stack->top = NULL;
    stack->size = 0;
}
// ѹջ
void push(stack* mystack, frame *nextFrame) {
    // �����ǰ��ջΪ�գ���ջ����ջ��ͬʱָ���һ��ջ֡
    if (mystack->size == 0) {
        mystack->base = nextFrame;
        mystack->top = nextFrame;
    }

    nextFrame->pre = mystack->top; // ��ǰջ֡����һ��ջ֡��ջ��
    mystack->top = nextFrame; // ջ������˵�ǰջ֡

    mystack->size++;// ����ջ������1
}

// ��ջ
void pop(stack* mystack) {
    int size = mystack->size;
    if (size == 0) {
        printf("%s\n", "��ǰ��ջΪ��,���ܳ�ջ");
        return ;
    }

    frame *currentFrame = mystack->top; // ��ȡ��ǰ��ջ����ջ֡
    mystack->top = mystack->top->pre; // ����ǰջ��ָ����һ��ջ֡

    // �ͷ�ջ��ջ֡
    free(currentFrame);
    mystack->size--;
    printf("�ɹ�����һ��ջ��ջ֡\n\n");
}

// ������ջ
void iterate(stack* mystack) {
    if (mystack->size == 0) {
        printf("%s\n", "��ǰ��ջΪ�գ�������ֹ");
        return;
    }

    int size = mystack->size;
    printf("*****************************��ǰ��ջ���� %d ��ջ֡*****************************\n",size);
    frame *currentFrame = mystack->top;
    while (size > 0) {
        printf("��ǰ�ǵ� %d ��ջ֡\n", size);
        printf("    local1 = %d\]n", currentFrame->local1);
        printf("    local2 = %d\]n", currentFrame->local2);
        printf("    local3 = %d\]n", currentFrame->local3);

        currentFrame = currentFrame->pre;
        size--;
    }
}

