#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct Node {
    int data;
    Node* head;
    Node* tail;
};

Node* createList(int length) {
    Node* curr = nullptr, * next = nullptr;
    for (int i = 0; i < length; ++i) {
        curr = new Node;
        curr->tail = next;
        if (next != nullptr)
            next->head = curr;
        next = curr;
    }
    curr->head = nullptr;
    return curr;
}

int lengthList(Node* curr) {
    int length = 0;
    while (curr) {
        length += 1;
        curr = curr->tail;
    }
    return length;
}

void outputList(Node* curr) {
    int length = lengthList(curr);
    for (int i = 0; i < length; ++i) {
        cout << curr->data << " ";
        curr = curr->tail;
    }
}

Node* listItem(Node* curr, int index) {
    int length = lengthList(curr);
    //int length = 10;
    for (int i = 0; i < length; ++i) {
        if (index == i) {
            return curr;
        }
        curr = curr->tail;
    }
    return nullptr;
}

void listInsertItem(Node*& curr, int index, int insertItem) {
    Node* localCurr = curr;
    Node* newNode = new Node;
    if (index == 0) {
        curr->head = newNode;
        curr = curr->head;
        curr->head = nullptr;
        curr->tail = localCurr;
        localCurr = curr;
    }
    else if (index == lengthList(localCurr)) {
        curr = listItem(localCurr, index - 1);
        Node* beforeNewNode = curr;
        curr->tail = newNode;
        curr = curr->tail;
        curr->head = beforeNewNode;
        curr->tail = nullptr;
    }
    else {
        curr = listItem(localCurr, index - 1);
        Node* beforeNewNode = curr;
        Node* afterNewNode = curr->tail;
        curr->tail = newNode;
        curr = curr->tail;
        curr->head = beforeNewNode;
        curr->tail = afterNewNode;
        curr = curr->tail;
        curr->head = newNode;
        curr = curr->head;
    }
    curr->data = insertItem;
    curr = listItem(localCurr, 0);
}

void arrayInsertItem(int*& array, int& lengthArray, int index, int insertItem)
{
    int* newArray = new int[lengthArray + 1];
    for (int i = 0; i < index; ++i)
        newArray[i] = array[i];
    newArray[index] = insertItem;

    for (int i = index + 1; i < lengthArray + 1; ++i)
        newArray[i] = array[i - 1];
    lengthArray += 1;

    delete[] array;
    array = newArray;
}

bool swapItem(Node*& curr, int index1, int index2)
{
    Node* adr1 = 0;
    Node* adr2 = 0;
    if (index1 > index2)
    {
        int temp = index1;
        index1 = index2;
        index2 = temp;
    }
    adr1 = listItem(curr, index1);
    adr2 = listItem(curr, index2);
    if (adr1 == adr2 || !adr1 || !adr2)
        return 1;
    Node* temp = 0;
    if (adr1->tail == adr2)
    {
        if (adr2->tail)
            adr2->tail->head = adr1;
        if (adr1->head)
            adr1->head->tail = adr2;
        adr1->tail = adr2->tail;
        adr2->head = adr1->head;
        adr2->tail = adr1;
        adr1->head = adr2;
        if (adr1 == curr)
            curr = adr2;
        return 0;
    }

    if (adr1->tail)
        adr1->tail->head = adr2;
    if (adr2->tail)
        adr2->tail->head = adr1;
    if (adr1->head)
        adr1->head->tail = adr2;
    if (adr2->head)
        adr2->head->tail = adr1;
    temp = adr1->tail;
    adr1->tail = adr2->tail;
    adr2->tail = temp;
    temp = adr1->head;
    adr1->head = adr2->head;
    adr2->head = temp;
    if (adr1 == curr)
        curr = adr2;
    else if (adr2 == curr)
        curr = adr1;
    return 0;
}
void listDeleteItem(Node*& curr, int index) {
    Node* localCurr = curr;
    if (index == 0) {
        Node* Temp = curr;
        curr = curr->tail;
        curr->head = nullptr;
        delete Temp;
    }
    else if (index == lengthList(localCurr) - 1) {
        curr = listItem(localCurr, index);
        Node* Temp = curr;
        curr = curr->head;
        curr->tail = nullptr;
        delete Temp;
        curr = listItem(localCurr, 0);
    }
    else {
        curr = listItem(localCurr, index);
        Node* Temp = curr;
        curr = curr->head;
        curr->tail = curr->tail->tail;
        curr = curr->tail;
        curr->head = curr->head->head;
        delete Temp;
        curr = listItem(localCurr, 0);
    }
}

void arrayDeleteItem(int*& array, int& lengthArray, int index)
{
    int* newArray = new int[lengthArray - 1];
    for (int i = 0; i < index; ++i)
        newArray[i] = array[i];

    for (int i = index; i < lengthArray - 1; ++i)
        newArray[i] = array[i + 1];
    lengthArray -= 1;

    delete[] array;
    array = newArray;
}

void deleteList(Node*& curr) {
    Node* next;
    while (curr) {
        next = curr->tail;
        delete curr;
        curr = next;
    }
}

int main() {
    Node* list = nullptr;
    int condition;

    long long listInputTimeA = 0, listInputTimeB = 0, listInsertTime = 0, listDeleteTime = 0, listSwapTime = 0, listOutputItemTime = 0;
    long long arrayInputTimeA = 0, arrayInputTimeB = 0, arrayInsertTime = 0, arrayDeleteTime = 0, arraySwapTime = 0, arrayOutputItemTime = 0;
    long long listSortTime = 0, arraySortTime = 0;

    int sizeList = 0;
    int* array = new int[sizeList];

    while (true) {
        setlocale(0, "");
        cout << "Команды: \n"
            "-- 1) Ввод списка \n"
            "-- 2) Вставка/Удаление/Обмен/Получение элемента \n"
            "-- 3) Вывести список \n"
            "-- 4) ИДЗ \n"
            "-- 0) Выход \n";
        cin >> condition;
        switch (condition) {
        case 0:
            deleteList(list);
            delete[] array;
            exit(-1);
        case 1:
            char firstResponse;
            cout << "Ввести количество элементов(1) или элементы списка(2)?" << "\n";
            cin >> firstResponse;
            if (firstResponse == '1') {
                cout << "Размер списка: " << "\n";
                cin >> sizeList;

                auto arrayBegin = chrono::steady_clock::now();
                array = new int[sizeList];
                for (int i = 0; i < sizeList; ++i) {
                    array[i] = rand() % 100;
                }
                auto arrayEnd = chrono::steady_clock::now();
                arrayInputTimeA = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();

                auto listBegin = chrono::steady_clock::now();
                list = createList(sizeList);
                Node* curr = list;
                for (int i = 0; i < sizeList; ++i) {
                    curr->data = array[i];
                    curr = curr->tail;
                }
                auto listEnd = chrono::steady_clock::now();
                listInputTimeA = chrono::duration_cast<std::chrono::nanoseconds>(listEnd - listBegin).count();
                cout << "Время создания двусвязного списка: " << listInputTimeA << "нс\n";
                cout << "Время создания динамического массива: " << arrayInputTimeA << "нс\n";
            }
            else if (firstResponse == '2') {
                string inputData;
                cout << "Элементы списка: " << "\n";
                cin.ignore();
                getline(cin, inputData);
                string localString;
                sizeList = 1;
                for (int i = 0; i < inputData.size(); ++i) {
                    if (inputData[i] == ' ') {
                        sizeList += 1;
                    }
                }

                auto listBegin = chrono::steady_clock::now();
                list = createList(sizeList);
                Node* curr = list;
                for (int i = 0; i < inputData.size(); ++i) {
                    if (inputData[i] != ' ') {
                        localString.push_back(inputData[i]);
                    }
                    else {
                        curr->data = stoi(localString);
                        curr = curr->tail;
                        localString = "";
                    }
                }
                if (!localString.empty()) {
                    curr->data = stoi(localString);
                }
                auto listEnd = chrono::steady_clock::now();
                listInputTimeB = chrono::duration_cast<std::chrono::nanoseconds>(listEnd - listBegin).count();

                auto arrayBegin = chrono::steady_clock::now();
                array = new int[sizeList];
                localString = "";
                int localIndex = 0;
                for (int i = 0; i < inputData.size(); ++i) {
                    if (inputData[i] != ' ') {
                        localString.push_back(inputData[i]);
                    }
                    else {
                        array[localIndex] = stoi(localString);
                        localString = "";
                        localIndex += 1;
                    }
                }
                if (!localString.empty()) {
                    array[localIndex] = stoi(localString);
                }
                auto arrayEnd = chrono::steady_clock::now();
                arrayInputTimeB = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();
                cout << "Время создания двусвязного списка: " << listInputTimeA << "нс\n";
                cout << "Время создания динамического массива: " << arrayInputTimeA << "нс\n";

            }
            else {
                cout << "Ошибка!" << "\n";
            }
            break;
        case 2:
            if (list != nullptr) {
                Node* curr = list;
                char secondResponse;
                cout << " Что вы хотите сделать?\n"
                    "-- 1) Вставка \n"
                    "-- 2) Удаление \n"
                    "-- 3) Обмен \n"
                    "-- 4) Получение \n";
                cin >> secondResponse;
                cin.ignore();
                if (secondResponse == '1') {
                    cout << "Введите индекс: " << "\n";
                    int index;
                    cin >> index;
                    if (index > lengthList(list) or index < 0) {
                        cout << "Ошибка!" << "\n";
                    }
                    else {
                        int insertItem;
                        cout << "Введите элемент: " << "\n";
                        cin >> insertItem;
                        auto listBegin = chrono::steady_clock::now();
                        listInsertItem(list, index, insertItem);
                        auto listEnd = chrono::steady_clock::now();
                        listInsertTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            listEnd - listBegin).count();

                        auto arrayBegin = chrono::steady_clock::now();
                        arrayInsertItem(array, sizeList, index, insertItem);
                        auto arrayEnd = chrono::steady_clock::now();
                        arrayInsertTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            arrayEnd - arrayBegin).count();
                    }
                    cout << "Время вставки в список: " << listInsertTime << "нс\n";
                    cout << "Время вставки в массив: " << arrayInsertTime << "нс\n";
                }
                else if (secondResponse == '2') {
                    char thirdResponse;
                    cout << "Удаление по индексу(1) или элементу(2)?" << "\n";
                    cin >> thirdResponse;
                    if (thirdResponse == '1') {
                        cout << "Введите индекс: " << "\n";
                        int index;
                        cin >> index;

                        if (index > lengthList(list) - 1 or index < 0) {
                            cout << "Ошибка!" << "\n";
                        }
                        else {
                            auto listBegin = chrono::steady_clock::now();
                            listDeleteItem(list, index);
                            auto listEnd = chrono::steady_clock::now();
                            listDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                listEnd - listBegin).count();

                            auto arrayBegin = chrono::steady_clock::now();
                            arrayDeleteItem(array, sizeList, index);
                            auto arrayEnd = chrono::steady_clock::now();
                            arrayDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                arrayEnd - arrayBegin).count();
                        }
                        cout << "Время удаления из списка: " << listDeleteTime << "нс\n";
                        cout << "Время удаления из массива: " << arrayDeleteTime << "нс\n";
                    }
                    else if (thirdResponse == '2') {
                        cout << "Введите элемент, который необходимо удалить: " << "\n";
                        int element;
                        cin >> element;

                        auto listBegin = chrono::steady_clock::now();
                        curr = list;
                        bool flag = false;
                        int length = lengthList(curr);
                        for (int i = 0; i < length; ++i) {
                            if (element == curr->data) {
                                flag = true;
                                listDeleteItem(list, i);
                                break;
                            }
                            curr = curr->tail;
                        }
                        if (!flag) {
                            cout << "Ошибка!" << "\n";
                        }
                        auto listEnd = chrono::steady_clock::now();
                        listDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            listEnd - listBegin).count();

                        auto arrayBegin = chrono::steady_clock::now();
                        flag = false;
                        for (int i = 0; i < sizeList; ++i) {
                            if (element == array[i]) {
                                flag = true;
                                arrayDeleteItem(array, sizeList, i);
                                break;
                            }
                        }
                        if (!flag) {
                            cout << "Ошибка!" << "\n";
                        }
                        auto arrayEnd = chrono::steady_clock::now();
                        arrayDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            arrayEnd - arrayBegin).count();
                        cout << "Время удаления из списка: " << listDeleteTime << "нс\n";
                        cout << "Время удаления из массива: " << arrayDeleteTime << "нс\n";
                    }
                    else {
                        cout << "Ошибка!" << "\n";
                    }

                }
                else if (secondResponse == '3') {
                    cout << "Введите два индекса : " << "\n";
                    int firstIndex, secondIndex;
                    cin >> firstIndex >> secondIndex;
                    if (firstIndex > lengthList(list) - 1 or firstIndex < 0) {
                        cout << "Ошибка!" << "\n";
                    }
                    else if (secondIndex > lengthList(list) - 1 or secondIndex < 0) {
                        cout << "Ошибка!" << "\n";
                    }
                    else {
                        auto listBegin = chrono::steady_clock::now();
                        swapItem(list, firstIndex, secondIndex);
                        auto listEnd = chrono::steady_clock::now();
                        listSwapTime = chrono::duration_cast<std::chrono::nanoseconds>(listEnd - listBegin).count();

                        auto arrayBegin = chrono::steady_clock::now();
                        swap(array[firstIndex], array[secondIndex]);
                        auto arrayEnd = chrono::steady_clock::now();
                        arraySwapTime = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();
                    }
                    cout << "Время обмена в списке: " << listSwapTime << " нс\n";
                    cout << "Время обмена в массиве: " << arraySwapTime << "нс\n";
                }
                else if (secondResponse == '4') {
                    char thirdResponse;
                    cout << "Получение по индексу(1) или элементу(2)?" << "\n";
                    cin >> thirdResponse;
                    if (thirdResponse == '1') {
                        cout << "Введите индекс: " << "\n";
                        int index;
                        cin >> index;
                        if (index > lengthList(list) - 1 or index < 0) {
                            cout << "Ошибка!" << "\n";
                        }
                        else {
                            auto listBegin = chrono::steady_clock::now();
                            cout << "Элемент в списке: " << listItem(list, index)->data << "\n";
                            auto listEnd = chrono::steady_clock::now();
                            listOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                listEnd - listBegin).count();

                            auto arrayBegin = chrono::steady_clock::now();
                            for (int i = 0; i < sizeList; ++i) {
                                if (index == i) {
                                    cout << "Элемент в массиве:" << array[i] << "\n";
                                    break;
                                }
                            }
                            auto arrayEnd = chrono::steady_clock::now();
                            arrayOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                                arrayEnd - arrayBegin).count();
                            cout << "Время получения элемента в списке: " << listOutputItemTime << "нс\n";
                            cout << "Время получения элемента в массиве: " << arrayOutputItemTime << "нс\n";
                        }

                    }
                    else if (thirdResponse == '2') {
                        cout << "Введите элемент: " << "\n";
                        int element;
                        cin >> element;

                        auto listBegin = chrono::steady_clock::now();
                        curr = list;
                        bool flag = false;
                        int length = lengthList(curr);
                        for (int i = 0; i < length; ++i) {
                            if (element == curr->data) {
                                cout << "Индекс в списке: " << i << "\n";
                                flag = true;
                                break;
                            }
                            curr = curr->tail;
                        }
                        if (!flag) {
                            cout << "Ошибка!" << "\n";
                        }
                        auto listEnd = chrono::steady_clock::now();
                        listOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            listEnd - listBegin).count();

                        auto arrayBegin = chrono::steady_clock::now();
                        flag = false;
                        for (int i = 0; i < sizeList; ++i) {
                            if (element == array[i]) {
                                cout << "Индекс в массиве:" << i << "\n";
                                flag = true;
                                break;
                            }
                        }
                        if (!flag) {
                            cout << "Ошибка!" << "\n";
                        }
                        auto arrayEnd = chrono::steady_clock::now();
                        arrayOutputItemTime = chrono::duration_cast<std::chrono::nanoseconds>(
                            arrayEnd - arrayBegin).count();
                        cout << "Время получения элемента в списке: " << listOutputItemTime << "нс\n";
                        cout << "Время получения элемента в массиве: " << arrayOutputItemTime << "нс\n";
                    }
                    else {
                        cout << "Ошибка!" << "\n";
                    }
                }
                else {
                    cout << "Ошибка!" << "\n";
                }
            }
            else {
                cout << "Ошибка!" << "\n";
            }
            break;
        case 3:
            if (list != nullptr) {
                Node* curr = list;
                cout << "Список: ";
                outputList(curr);

                cout << "\nМассив: ";
                for (int i = 0; i < sizeList; ++i) {
                    cout << array[i] << " ";
                }
                cout << "\n";
            }
            else {
                cout << "Ошибка!" << "\n";
            }
            break;
        case 4:
            if (list != nullptr) {
                auto listBegin = chrono::steady_clock::now();
                Node* curr = list;
                int length = lengthList(curr);
                for (int i = 0; i < length; ++i) {
                    for (int j = 0; j < length - i - 1; ++j) {
                        if (listItem(curr, j)->data > listItem(curr, j + 1)->data) {
                            int buffer = listItem(curr, j + 1)->data;
                            listItem(curr, j + 1)->data = listItem(curr, j)->data;
                            listItem(curr, j)->data = buffer;
                        }
                    }
                }
                auto listEnd = chrono::steady_clock::now();
                listSortTime = chrono::duration_cast<std::chrono::nanoseconds>(
                    listEnd - listBegin).count();

                auto arrayBegin = chrono::steady_clock::now();
                for (int i = 0; i < sizeList; ++i) {
                    for (int j = 0; j < sizeList - i - 1; ++j) {
                        if (array[j] > array[j + 1]) {
                            swap(array[j], array[j + 1]);
                        }
                    }
                }
                auto arrayEnd = chrono::steady_clock::now();
                arraySortTime = chrono::duration_cast<std::chrono::nanoseconds>(
                    arrayEnd - arrayBegin).count();
            }
            cout << "Время сортировки списка: " << listSortTime << "нс\n";
            cout << "Время сортировки массива: " << arraySortTime << "нс\n";
            break;
        default:
            continue;
        }
    }
}