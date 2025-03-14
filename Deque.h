#ifndef INC_8_7_58REWRITE_DEQUE_H
#define INC_8_7_58REWRITE_DEQUE_H


template<typename DataType>
class DLNode {
private:
    DLNode* prev;
    DLNode* next;
    DataType data;
public:
    DLNode() : prev(nullptr), next(nullptr), data() {}
    DLNode(const DataType& Data) : prev(nullptr), next(nullptr), data(Data) {}
    DataType& Data() {
        return data;
    }
    DataType Data() const {
        return data;
    }
    DLNode*& Prev() {
        return prev;
    }
    DLNode* Prev() const {
        return prev;
    }
    DLNode*& Next() {
        return next;
    }
    DLNode* Next() const {
        return next;
    }
};

template<typename DataType>
class Deque {
private:
    DLNode<DataType>* Front;
    DLNode<DataType>* Back;
    void destruct() {
        while(!empty()) {
            pop_back();
        }
    }
public:
    Deque() : Front(nullptr), Back(nullptr) {}
    ~Deque() {
        destruct();
    }
    Deque(const Deque<DataType>& deque) : Front(nullptr), Back(nullptr) {
        DLNode<DataType>* curr = deque.Front;
        while(curr != nullptr) {
            push_back(curr->Data());
            curr = curr->Next();
        }
    }
    Deque& operator=(const Deque<DataType>& deque) {
        if(this != &deque) {
            destruct();
            DLNode<DataType>* curr = deque.Front;
            while(curr != nullptr) {
                push_back(curr->Data());
                curr = curr->Next();
            }
        }
        return *this;
    }
    bool empty() const {
        return Front == nullptr;
    }
    void push_front(const DataType& Data) {
        DLNode<DataType>* newDLNode = new DLNode(Data);
        newDLNode->Next() = Front;
        if(empty()) {
            Back = newDLNode;
        } else {
            Front->Prev() = newDLNode;
        }
        Front = newDLNode;
    }
    void push_back(const DataType& Data) {
        DLNode<DataType>* newDLNode = new DLNode(Data);
        newDLNode->Prev() = Back;
        if(empty()) {
            Front = newDLNode;
        } else {
            Back->Next() = newDLNode;
        }
        Back = newDLNode;
    }
    void pop_front() {
        if(!empty()) {
            if(Front == Back) {
                delete Front;
                Front = nullptr;
                Back = nullptr;
            } else {
                DLNode<DataType> *temp = Front;
                Front = Front->Next();
                delete temp;
                Front->Prev() = nullptr;
            }
        }
    }
    void pop_back() {
        if(!empty()) {
            if(Front == Back) {
                delete Back;
                Front = nullptr;
                Back = nullptr;
            } else {
                DLNode<DataType> *temp = Back;
                Back = Back->Prev();
                delete temp;
                Back->Next() = nullptr;
            }
        }
    }
    DataType front() const {
        if(!empty()) {
            return Front->Data();
        }
    }
    DataType back() const {
        if(!empty()) {
            return Back->Data();
        }
    }

    std::ostream& print(std::ostream& os = std::cout) const {
        os << '[';
        DLNode<DataType>* currNode = Front;
        if(currNode != nullptr) {
            os << currNode->Data();
            currNode = currNode->Next();
        }
        while(currNode != nullptr) {
            os << ", " << currNode->Data();
            currNode = currNode->Next();
        }
        os << ']';
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Deque<DataType>& deque) {
        return deque.print(os);
    }
};


#endif
