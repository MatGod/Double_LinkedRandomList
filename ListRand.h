//
// Created by MatGod on 31.08.2020.
//

#ifndef DOUBLE_LINKEDRANDOMLIST_LISTRAND_H
#define DOUBLE_LINKEDRANDOMLIST_LISTRAND_H

#include <string>

class ListNode {
public:
    ListNode* Prev = nullptr;
    ListNode* Next = nullptr;
    ListNode* Rand = nullptr;
    std::string Data;
};

class ListRand {
public:
    ListNode* Head = nullptr;
    ListNode* Tail = nullptr;
    int Count = 0;

    void Serialize(std::fstream& Stream);
    void Deserialize(std::fstream& Stream);
    void PushBack(std::string Str, bool IsRandomLinked = false, int RandomLinkedElem = 0);
    void Print() const;

    ListNode* operator[](int idx) const;

    ~ListRand();
};


#endif //DOUBLE_LINKEDRANDOMLIST_LISTRAND_H
