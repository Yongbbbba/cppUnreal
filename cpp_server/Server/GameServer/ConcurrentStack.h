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
        Node* oldHead = _head;
        while (oldHead && _head.compare_exchange_weak(oldHead, oldHead->next) == false)
        {
            oldHead = _head;
        }

        if (oldHead == nulltptr)
            return false;

        // Exception ���x
        value = oldHead->data;

        // ��� ���� ����
        // �ֳĸ� ��Ƽ������ ȯ�濡�� �̹� �ٸ� �����尡 oldHead�� �������� �� ���� �ٽ� �����ϴ� �̻��� ��Ȳ�� �߻��� �� �ֱ� ����
        // C#, Java ���� GC�� ������ ��� ���⼭ ��
        // �̸� �ذ��ϴ� ���� �˰����� �����ε� ������ �ְ�, Ư����� ��ϵǱ⵵ �Ѵ�.
        // delete oldHead;

        return true;

    }

private:
    atomic<Node*> _head;
};
