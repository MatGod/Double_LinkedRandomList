#include <iostream>
#include <fstream>
#include "ListRand.h"

int main() {
    std::fstream SaveFile;
    SaveFile.open("ListRand.txt");

    ListRand SavedList;
    SavedList.PushBack("1");
    SavedList.PushBack("2");
    SavedList.PushBack("3", true, 0);
    SavedList.PushBack("4");
    SavedList.PushBack("5");
    SavedList[0]->Rand = SavedList[4];

    SavedList.Serialize(SaveFile);

    SaveFile.close();

    std::cout << "Original List:\n";
    SavedList.Print();

    std::fstream ReadFile;
    ReadFile.open("ListRand.txt");

    ListRand RestoredList;

    RestoredList.Deserialize(ReadFile);

    ReadFile.close();

    std::cout << "\nDeserialized list:\n";
    RestoredList.Print();

    return 0;
}
