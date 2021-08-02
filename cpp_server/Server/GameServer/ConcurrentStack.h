#pragma once
#include <mutex>

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
        ++_popCount;

        Node* oldHead = _head;

        while (oldHead && _head.compare_exchange_weak(oldHead, oldHead->next) == false)
        {
            oldHead = _head;
        }

        if (oldHead == nulltptr)
        {
            --_popCount;
            return false;
        }

        // Exception 고려x
        value = oldHead->data;

        TryDelete(oldHead);  // -> ABA문제를 해결하기 위한 하나의 방법

        // 잠시 삭제 보류
        // 왜냐면 멀티쓰레딩 환경에서 이미 다른 쓰레드가 oldHead를 해제했을 때 내가 다시 해제하는 이상한 상황이 발생할 수 있기 때문
        // C#, Java 같이 GC가 있으면 사실 여기서 끝
        // 이를 해결하는 여러 알고리즘이 논문으로도 나오고 있고, 특허까지 등록되기도 한다.
        // delete oldHead;

        return true;

    }
    
    // 함수 호출 순서 -> 매우 중요
    // 1) 데이터 분리 -> 그렇기 때문에 다른 쓰레드에서 삭제하는 oldHead와 나의 oldHead는 같아질 수 없음
    // 2) Count 체크
    // 3) 나 혼자면 삭제
    void TryDelete(Node* oldHead)
    {
        // 나 외에 누가 있는가?
        if (_popCount == 1) // 나만 존재하는 경우
        {
            // 이왕 혼자인거, 삭제 예약된 다른 데이터들도 삭제해보자
            Node* node = _pendingList.exchange(nullptr);  // 원래있던 값은 node에 넣고 nullptr로 밀어버림


            if (--_popCount == 0)
            {
                // 끼어든 애가 없음 -> 삭제 진행
                // 이제와서 끼어들어도, 어차피 데이터는 분리해둔 상태
                DeleteNodes(node);
            }
            else if (node)
            {
                // 누가 끼어들었으니 다시 갖다놓자
                ChainPendingNodeList(node);
            }

            // 내 데이터는 삭제
            delete oldHead;
        }
        else // 다른 쓰레드도 pop하고 있는 상황
        {
            // 누가 있네? 그럼 지금 삭제하지 않고, 삭제 예약만
            // oldHead를 획득까지는 했지만 누가 삭제 시도를 하고 있기 때문에 다시 반납
            ChainPendingNode(oldHead);
            --_popCount;
        }
    }

    void ChainPendingNodeList(Node* first, Node* last)
    {
        last->next = _pendingList;

        while (_pendingList.compare_exchange_weak(last->next, first) == false)
        {

        }
    }

    void chainPendingNodeList(Node* node)
    {
        Node* last = node;
        while (last->next)
            last = last->next;

        ChainPendingNodeList(node, last);
    }

    void ChainPendingNode(Node* node)
    {
        ChainPendingNodeList(node, node);
    }

    static void DeleteNodes(Node* node) // 이 노드로 시작하는 리스트를 모두 삭제
    {
        while (node)
        {
            Node* next = node->next;
            delete node; 
            node = next; 
        }
    }

private:
    atomic<Node*>   _head;

    atomic<uint32>  _popCount = 0; // Pop을 실행중인 쓰레드 개수
    atomic<Node*>   _pendingList; // 삭제 되어야 할 노드들 (첫 번째 노드)
};
