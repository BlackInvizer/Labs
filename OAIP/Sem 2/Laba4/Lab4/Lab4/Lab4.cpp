#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct ListItem {
    int number;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* top;
    ListItem* bottom;
};


void Create(List* list) {
    list->top = list->bottom = NULL;
}

void PushFront(List* list, int num) {
    ListItem* temp = new ListItem;
    temp->number = num;
    temp->prev = NULL;
    temp->next = list->top;

    if (list->top != NULL) {
        list->top->prev = temp;
    }

    list->top = temp;

    if (list->bottom == NULL) {
        list->bottom = temp;
    }
}

void PushBack(List* list, int num) {
    ListItem* temp = new ListItem;
    temp->number = num;
    temp->next = NULL;
    temp->prev = list->bottom;

    if (list->bottom != NULL) {
        list->bottom->next = temp;
    }

    list->bottom = temp;

    if (list->top == NULL) {
        list->top = temp;
    }
    
}

void View(int kod, List* list) {
    if (kod == 0) {
        ListItem* temp = list->top;
        while (temp != NULL) {
            cout << "|" << temp->number;
            temp = temp->next;
        }
        cout << "|" << endl;
    }

    else {
        ListItem* temp = list->bottom;
        while (temp != NULL) {
            cout << "|" << temp->number;
            temp = temp->prev;
        }
        cout << "|" << endl;
    }
}

void PopFront(List* list)
{
    if (list->top == NULL) {
        return;
    }

    ListItem* temp;
    temp = list->top;
    list->top = list->top->next;
    delete temp;

    if (list->top == NULL) {
        list->bottom = NULL;
    }
}

void PopBack(List* list)
{
    if (list->bottom == NULL) {
        return;
    }

    ListItem* temp;
    temp = list->bottom;
    list->bottom = list->bottom->prev;
    delete temp;

    if (list->bottom == NULL) {
        list->top = NULL;
    }
}

void Split(List* All, List* Odd, List* Even) {
    while (All->top != NULL) {
        ListItem* current = All->top;
        All->top = All->top->next;

        if (current->number % 2 == 0) {
            current->prev = Even->bottom;
            current->next = NULL;

            if (Even->bottom != NULL) {
                Even->bottom->next = current;
            }
            else {
                Even->top = current;
            }

            Even->bottom = current;
        
        }
        else {
            current->prev = Odd->bottom;
            current->next = NULL;

            if (Odd->bottom != NULL) {
                Odd->bottom->next = current;
            }
            else {
                Odd->top = current;
            }

            Odd->bottom = current;
        }
    }
    All->bottom = NULL;
}

int main()
{
    List All;
    List Even;
    List Odd;
    int kod;
    int choice;

    srand(time(NULL));

    cout << "Enter:\n" << "0 to fill in the list from the beginning\n1 to fill in the list from the end\n";
    cin >> kod;

    cout << "\nWould you like to fill in the list with random numbers (from -100 till 100)?" << endl << "0 to yes\n1 to no\n";
    cin >> choice;

    Create(&All);
    if (choice == 0) {
        for (int i = 0; i < 10; i++) {
            if(kod == 0) PushBack(&All, rand() % 200 - 100);
            else PushFront(&All, rand() % 200 - 100);
        }
    }
    else {
        cout << endl;
        for (int i = 0; i < 10; i++) {
            int number;
            cin >> number;

            if (kod == 0) PushBack(&All, number);
            else PushFront(&All, number);
        }
    }
    cout << "\nEnter:\n" << "0 to read the list from the beginning\n1 to read the list from the end\n";
    cin >> kod;
    cout << endl;
    View(kod, &All);

    cout << "\nEnter:\n" << "0 to read the list from the beginning\n1 to read the list from the end\n";
    cin >> kod;
    cout << endl;
    View(kod, &All);

    Create(&Even);
    Create(&Odd);

    Split(&All, &Odd, &Even);

    cout << "------------------------------------------\nEven:";
    View(kod, &Even);
    cout << "------------------------------------------\nOdd:";
    View(kod, &Odd);

    while (Even.bottom != NULL) {
        PopBack(&Even);
    }
    while (Odd.bottom != NULL) {
        PopBack(&Odd);
    }

    return 0;
}