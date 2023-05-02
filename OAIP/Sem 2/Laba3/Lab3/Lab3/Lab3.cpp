#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct Stack {
    int number;

    Stack* next;
};

void Push(Stack** top, int number)
{
    Stack* b = new Stack;
    b->number = number;
    b->next = (*top);
    (*top) = b;
}

void Pop(Stack** top)
{
    Stack* temp;
    temp = *top;
    *top = (*top)->next;
    delete temp;
    
}

void Split(Stack** All, Stack** Odd, Stack** Even) {
    //while (*All != NULL) {
        Stack* current = *All;
        *All = (*All)->next;
        if (current->number % 2 == 0) {
            current->next = *Even;
            *Even = current;
        }
        else {
            current->next = *Odd;
            *Odd = current;
        }
    //}
}

int main()
{
    Stack* All = NULL;
    Stack* Odd = NULL;
    Stack* Even = NULL;

    srand(time(NULL));
    for (int i = 0; i < 15; i++) {
        Push(&All, rand() % 200 - 100);
    }
    
    cout << "values:\n";
    while (All != NULL) {
        cout << All->number << endl;
        Split(&All, &Odd, &Even);
    }
    


    cout << "---------------------------------\n";

    cout << "Even: |";
    while (Even != NULL) {
        cout << Even->number << "|";
        Pop(&Even);
    }

    cout << "\n---------------------------------\n";

    cout << "Odd: |";
    while (Odd != NULL) {
        cout << Odd->number << "|";
        Pop(&Odd);
    }

    cout << "\n---------------------------------\n";

    return 0;
}
