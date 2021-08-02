#pragma once

template<typename T>
class LockFreeStack
{
    struct Node
    {
        Node(const T& value) : data(value), next(nullptr)
        {

        }

        T data;
        Node* next;
    };

public:
    // 1) 새 노드를 만들고
    // 2) 새 노드의 next = head
    // 3) head = 새 노드

    void Push(const T& value)
    {
        Node* node = new Node(value);
        node->next = _head;
        while (_head.compare_exchange_weak(node->next, node) == false) 
        // 그새 head가 바꼈다면 false가 뜨게 되고, _head = node가 성공할 때까지 루프
        // 만약 경합상황이 심해서 이 루프가 계속 돌게되면 성능이 떨어지게 될 수 있다.
        {
            node->next = _head;
        }
        // 이 사이에 새치기 당하면? 누가 head가 될 것인가? 그래서 이를 atomic하게 처리해야함
        // _head = node;

    } 

    // 1) head 읽기
    // 2) head->next 읽기 
    // 3) head = head->next
    // 4) data 추출해서 반환
    // 5) 추출한 노드 삭제

    bool TryPop(T& value)
    {
        Node* oldHead = _head;
        while (oldHead && _head.compare_exchange_weak(oldHead, oldHead->next) == false)
        {
            oldHead = _head;
        }

        if (oldHead == nulltptr)
            return false;

        // Exception 고려x
        value = oldHead->data;

        // 잠시 삭제 보류
        // 왜냐면 멀티쓰레딩 환경에서 이미 다른 쓰레드가 oldHead를 해제했을 때 내가 다시 해제하는 이상한 상황이 발생할 수 있기 때문
        // C#, Java 같이 GC가 있으면 사실 여기서 끝
        // 이를 해결하는 여러 알고리즘이 논문으로도 나오고 있고, 특허까지 등록되기도 한다.
        // delete oldHead;

        return true;

    }

private:
    atomic<Node*> _head;
};
