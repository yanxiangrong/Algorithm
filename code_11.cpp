//
// Created by yan on 2021/5/17.
// 自己设计的栈，队列，基于链表

#include <iostream>


using namespace std;


namespace my {
    typedef __SIZE_TYPE__ SizeType;

    template<typename Type>
    class List {
    private:
        typedef Type ElemType;
        typedef struct ListNode {
            ElemType data{};
            ListNode *prior{};
            ListNode *next{};
        } ListNode, *PListNode;

        PListNode head;
        PListNode tail;
        SizeType nodeCount{};
    public:
        typedef struct iterator {
        private:
            PListNode pData;
        public:
            explicit iterator(PListNode pListNode) : pData(pListNode) {};

            ElemType operator*() {
                return pData->data;
            }

            iterator operator++() {
                pData = pData->next;
                return iterator(pData);
            }

            iterator operator--() {
                pData = pData->prior;
                return iterator(pData);
            }

            bool operator==(iterator &iterator1) {
                return pData == iterator1.pData;
            }

            bool operator!=(iterator &iterator1) {
                return pData != iterator1.pData;
            }
        } iterator;

        List();

        virtual ~List();

        void push_front(const Type &x);

        void push_back(const Type &x);

        void insertAfterNode(ListNode &&node, const Type &x);

        void pop_front();

        void pop_back();

        SizeType size() {
            return this->nodeCount;
        }

        bool empty() {
            return this->head == this->tail;
        }

        void clear();

        Type front();

        Type back();

        iterator begin() {
            return iterator(this->head->next);
        }

        iterator end() {
            return iterator(this->tail->next);
        }
    };

    template<typename Type>
    List<Type>::List() {
        this->head = new List::ListNode();
        this->head->prior = nullptr;
        this->head->next = nullptr;

        this->tail = this->head;
        this->nodeCount = 0;
    }

    template<typename Type>
    void List<Type>::push_back(const Type &x) {
        auto newNode = new List::ListNode;
        newNode->data = x;
        newNode->next = nullptr;
        newNode->prior = this->tail;
        this->tail->next = newNode;
        this->tail = newNode;
        ++this->nodeCount;
    }

    template<typename Type>
    void List<Type>::push_front(const Type &x) {
        insertAfterNode(this->head, x);
    }

    template<typename Type>
    void List<Type>::pop_front() {
        List::PListNode delNode = this->head;
        this->head = delNode->next;
        delete delNode;
        --this->nodeCount;
    }

    template<typename Type>
    void List<Type>::pop_back() {
        List::PListNode delNode = this->tail;
        delNode->prior->next = nullptr;
        this->tail = delNode->prior;
        delete delNode;
        --this->nodeCount;
    }

    template<typename Type>
    void List<Type>::insertAfterNode(List::ListNode &&node, const Type &x) {
        auto newNode = new List::ListNode;
        newNode->data = x;
        newNode->next = node.next;
        newNode->prior = node;

        node.next->prior = newNode;
        node.next = newNode;
        ++this->nodeCount;
    }

    template<typename Type>
    void List<Type>::clear() {
        while (not empty()) {
            pop_back();
            --this->nodeCount;
        }
    }

    template<typename Type>
    Type List<Type>::front() {
        return this->head->next->data;
    }

    template<typename Type>
    Type List<Type>::back() {
        return this->tail->data;
    }

    template<typename Type>
    List<Type>::~List() {
        clear();
        delete this->head;
    }


    template<typename Type>
    class Queue {
    private:
        List<Type> data;
    public:
        typedef typename List<Type>::iterator iterator;

        Queue() = default;

        virtual ~Queue() = default;

        SizeType size() {
            return this->data.size();
        }

        void push(const Type &x) {
            this->data.push_back(x);
        }

        void pop() {
            this->data.pop_front();
        }

        bool empty() {
            return this->data.empty();
        }

        Type front() {
            return this->data.front();
        }

        Type back() {
            return this->data.back();
        }

        iterator begin() {
            return data.begin();
        }

        iterator end() {
            return data.end();
        }

        void clear() {
            data.clear();
        }
    };


    template<class Type>
    class Stack {
    private:
        List<Type> data;
    public:
        typedef typename List<Type>::iterator iterator;

        Stack() = default;

        virtual ~Stack() = default;

        SizeType size() {
            return this->data.size();
        }

        void push(const Type &x) {
            this->data.push_back(x);
        }

        void pop() {
            this->data.pop_back();
        }

        bool empty() {
            return this->data.empty();
        }

        Type top() {
            return this->data.back();
        }

        iterator begin() {
            return data.begin();
        }

        iterator end() {
            return data.end();
        }

        void clear() {
            data.clear();
        }
    };
}

enum BracketType {
    RIGHT, LEFT
};

typedef struct Bracket {
    BracketType type;
    int position;

    explicit Bracket() : type(LEFT), position(0) {}

    explicit Bracket(char ch, int p) : type(ch == '(' ? LEFT : RIGHT), position(p) {}

    bool operator==(const Bracket &bracket) const {
        return this->type == bracket.type;
    }

    bool operator!=(const Bracket &bracket) const {
        return this->type != bracket.type;
    }

} Bracket;

bool isMatch(Bracket a, Bracket b) {
    return a.type == LEFT and b.type == RIGHT;
}

int main() {
    my::Stack<int> stack;
    my::Queue<int> queue;
    for (int i = 0; i < 10; ++i) {
        stack.push(i);
        queue.push(i);
    }

    cout << "Stack Size: " << stack.size() << endl;
    cout << "Queue Size: " << queue.size() << endl;

    cout << "Stack: ";
    for (auto &&i : stack) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "Queue: ";
    for (auto &&i : queue) {
        cout << i << ' ';
    }
    cout << endl;

    cout << "Stack pop: ";
    while (not stack.empty()) {
        cout << stack.top() << ' ';
        stack.pop();
    }
    cout << endl;
    cout << "Queue pop: ";
    while (not queue.empty()) {
        cout << queue.front() << ' ';
        queue.pop();
    }
    cout << endl;


    return 0;
}