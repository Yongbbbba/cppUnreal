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
    // 1) �� ��带 �����
    // 2) �� ����� next = head
    // 3) head = �� ���

    void Push(const T& value)
    {
        Node* node = new Node(value);
        node->next = _head;
        while (_head.compare_exchange_weak(node->next, node) == false) 
        // �׻� head�� �ٲ��ٸ� false�� �߰� �ǰ�, _head = node�� ������ ������ ����
        // ���� ���ջ�Ȳ�� ���ؼ� �� ������ ��� ���ԵǸ� ������ �������� �� �� �ִ�.
        {
            node->next = _head;
        }
        // �� ���̿� ��ġ�� ���ϸ�? ���� head�� �� ���ΰ�? �׷��� �̸� atomic�ϰ� ó���ؾ���
        // _head = node;

    } 

    // 1) head �б�
    // 2) head->next �б� 
    // 3) head = head->next
    // 4) data �����ؼ� ��ȯ
    // 5) ������ ��� ����

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

        // Exception ���x
        value = oldHead->data;

        TryDelete(oldHead);  // -> ABA������ �ذ��ϱ� ���� �ϳ��� ���

        // ��� ���� ����
        // �ֳĸ� ��Ƽ������ ȯ�濡�� �̹� �ٸ� �����尡 oldHead�� �������� �� ���� �ٽ� �����ϴ� �̻��� ��Ȳ�� �߻��� �� �ֱ� ����
        // C#, Java ���� GC�� ������ ��� ���⼭ ��
        // �̸� �ذ��ϴ� ���� �˰����� �����ε� ������ �ְ�, Ư����� ��ϵǱ⵵ �Ѵ�.
        // delete oldHead;

        return true;

    }
    
    // �Լ� ȣ�� ���� -> �ſ� �߿�
    // 1) ������ �и� -> �׷��� ������ �ٸ� �����忡�� �����ϴ� oldHead�� ���� oldHead�� ������ �� ����
    // 2) Count üũ
    // 3) �� ȥ�ڸ� ����
    void TryDelete(Node* oldHead)
    {
        // �� �ܿ� ���� �ִ°�?
        if (_popCount == 1) // ���� �����ϴ� ���
        {
            // �̿� ȥ���ΰ�, ���� ����� �ٸ� �����͵鵵 �����غ���
            Node* node = _pendingList.exchange(nullptr);  // �����ִ� ���� node�� �ְ� nullptr�� �о����


            if (--_popCount == 0)
            {
                // ����� �ְ� ���� -> ���� ����
                // �����ͼ� �����, ������ �����ʹ� �и��ص� ����
                DeleteNodes(node);
            }
            else if (node)
            {
                // ���� ���������� �ٽ� ���ٳ���
                ChainPendingNodeList(node);
            }

            // �� �����ʹ� ����
            delete oldHead;
        }
        else // �ٸ� �����嵵 pop�ϰ� �ִ� ��Ȳ
        {
            // ���� �ֳ�? �׷� ���� �������� �ʰ�, ���� ���ุ
            // oldHead�� ȹ������� ������ ���� ���� �õ��� �ϰ� �ֱ� ������ �ٽ� �ݳ�
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

    static void DeleteNodes(Node* node) // �� ���� �����ϴ� ����Ʈ�� ��� ����
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

    atomic<uint32>  _popCount = 0; // Pop�� �������� ������ ����
    atomic<Node*>   _pendingList; // ���� �Ǿ�� �� ���� (ù ��° ���)
};
