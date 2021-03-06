//完成下面的栈类QStack，使用其中的双队列实现入栈、出栈等基本运算
#include "StackADT.cpp"
#include "AQueue.cpp"
#include <iostream>

const int defaultSize = 1024;

template <typename E>
class QStack :public Stack<E>{
private:
    int maxSize; //栈的容量
    AQueue<E> QA;
    AQueue<E> QB; //基于数组实现的队列
public:
    QStack(int size = defaultSize) : QA(size), QB(size) //初始化队列
    {
        maxSize = size;
    }
    ~QStack() {}

    //完成下列函数的代码
    void clear() {
        QA.clear();
        QB.clear();
    }

    void push(const E &it) {
        //哪个队列不为空就插入到哪个队列里
        assert(length() < maxSize);
        if(QB.length()) QB.enqueue(it);
        else QA.enqueue(it);
    }

    E pop() {
    //把有元素的那个队列转移到另一个队列中，只剩下最后一个元素，再弹出这个元素
        assert(QA.length() || QB.length()); //如果QA，QB都为空则报错
        if (QA.length()){
            while(QA.length() > 1)
                QB.enqueue(QA.dequeue());
            return QA.dequeue();
        }else{
            while(QB.length() > 1)
                QA.enqueue(QB.dequeue());
            return QB.dequeue();
        }
    }

    //去掉了引用和常成员函数限制，因为 
    //1)Queue中的元素会被弹出，返回引用会有风险 
    //2)对QA和QB进行了enqueue和dequeue操作，不满足常成员函数的条件
    const E topValue() {
        assert(QA.length() || QB.length()); //如果QA，QB都为空则报错
        E it;
        //把一个Queue里的元素都倒到另一个Queue里，其中输出最后一个元素
        if (QA.length()){
            while(QA.length() > 1)
                QB.enqueue(QA.dequeue());
            it = QA.dequeue();
            QB.enqueue(it);
        }else{
            while(QB.length() > 1)
                QA.enqueue(QB.dequeue());
            it = QB.dequeue();
            QA.enqueue(it);
        }
        return it;
    }

    virtual int length() const {
        return QA.length() + QB.length();
    }
};
