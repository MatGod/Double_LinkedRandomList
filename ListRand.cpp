//
// Created by MatGod on 31.08.2020.
//

#include "ListRand.h"

#include <utility>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>

void SerializeString(std::fstream &Stream, const std::string &Str);
std::string DeserializeString(std::fstream& Stream);

void ListRand::Serialize(std::fstream &Stream) {
    auto Node = Head;
    std::map<ListNode*, short> IdxMap;

    for (auto i = 0; Node != nullptr; Node = Node->Next, ++i) {
        IdxMap.insert(std::make_pair(Node, i));
    }

    Stream.write(reinterpret_cast<const char*>(&Count), sizeof(Count));

    Node = Head;
    for (auto i = 0; Node != nullptr; Node = Node->Next, ++i) {
        short RandIdx = Node->Rand != nullptr ?
                IdxMap[Node->Rand] : (short)-1;

        Stream.write(reinterpret_cast<const char*>(&RandIdx), sizeof(RandIdx));

        SerializeString(Stream, Node->Data);
    }
}

void ListRand::Deserialize(std::fstream &Stream) {
    ListNode* Node;
    std::map<ListNode*, short> RandIdxMap;
    std::vector<ListNode*> NodePtrs;

    Stream.read(reinterpret_cast<char*>(&Count), sizeof(Count));

    for (auto i = 0; i != Count; ++i) {
        Node = new ListNode;

        short RandIdx;
        Stream.read(reinterpret_cast<char*>(&RandIdx), sizeof(RandIdx));

        RandIdxMap.insert(std::make_pair(Node, RandIdx));
        NodePtrs.push_back(Node);

        Node->Data = DeserializeString(Stream);
        if (i == 0) {
            Head = Node;
        } else {
            Node->Prev = Tail;
            Tail->Next = Node;
        }
        Tail = Node;
    }

    for (Node = Head; Node != nullptr; Node = Node->Next) {
        short RandIdx = RandIdxMap[Node];
        if (RandIdx > (short)-1) {
            Node->Rand = NodePtrs[RandIdx];
        }
    }
}

void ListRand::PushBack(std::string Str, bool IsRandomLinked, int RandomLinkedElem) {
    auto* Node = new ListNode;
    Node->Data = std::move(Str);
    Node->Prev = Tail;
    Node->Next = nullptr;
    if (Tail != nullptr) {
        Tail->Next = Node;
    } else {
        Head = Node;
    }
    Tail = Node;

    if (IsRandomLinked && RandomLinkedElem <= Count) {
        Node->Rand = this->operator[](RandomLinkedElem);
    }

    ++Count;
}

ListRand::~ListRand() {
    while (Head != Tail) {
        Head = Head->Next;
        delete Head->Prev;
    }
    delete Tail;
}

ListNode *ListRand::operator[](int idx) const {
    ListNode* Node = Head;
    for (auto i = 0; i != idx; ++i) {
        Node = Node->Next;
    }
    return Node;
}

void ListRand::Print() const {
    for (auto Node = Head; Node != nullptr; Node = Node->Next) {
        std::cout << "\"" << Node->Data << "\"";
        if (Node->Rand != nullptr) {
            std::cout << " Random link to \"" << Node->Rand->Data << "\"";
        }
        std::cout << std::endl;
    }
}

void SerializeString(std::fstream& Stream, const std::string& Str) {
    const auto Len = static_cast<int>(Str.size());
    Stream.write(reinterpret_cast<const char*>(&Len), sizeof(Len));
    if (Len > 0) {
        Stream.write(Str.data(), Len);
    }
}

std::string DeserializeString(std::fstream& Stream) {
    int Len;
    Stream.read(reinterpret_cast<char*>(&Len), sizeof(Len));

    char* buffer = (char*)malloc((Len + 1) * sizeof(char));
    if (buffer != nullptr) {
        Stream.read(buffer, Len);
    }
    buffer[Len] = '\0';

    std::string RetVal(buffer);
    free(buffer);

    return RetVal;
}