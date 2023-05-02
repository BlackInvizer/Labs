#include <iostream>
#include <stdio.h>
#include <io.h>
#include < string.h >
#include<limits>

using namespace std;

#pragma warning(disable:4996)



struct InfoDesk {
    int Number;
    char Type[128];
    char Destination[128];
    int Hour;
    int Minute;
};


bool InputFlight(InfoDesk* ID) {

    cout << "\nInput Number: " << endl;
    cin >> ID->Number;

    cout << "Input Type: " << endl;
    cin >> ID->Type;

    cout << "Input Destination: " << endl;
    cin >> ID->Destination;

    cout << "Input departure hour: " << endl;
    cin >> ID->Hour;
    if (ID->Hour > 23 || ID->Hour < 0) {
        cout << "Incorrect data";
        return false;
    }  

    cout << "Input departure minute: " << endl;
    cin >> ID->Minute;
    if (ID->Minute > 60 || ID->Minute < 0) {
        cout << "Incorrect data";
        return false;
    }

    return true;
}

void ShowFlight(InfoDesk* ID) {
    cout << "\nNumber: " << ID->Number << endl;
    cout << "Type: " << ID->Type << endl;
    cout << "Destination: " << ID->Destination << endl;
    printf( "Time: %02d:%02d\n\n", ID->Hour, ID->Minute);
}

void QSortByDestination(InfoDesk* ID, int total) { //QuickSort
    if (total <= 1) {
        return;
    }
    int left = 0;
    int right = total - 1;
    InfoDesk* mid = &(ID[(left + right) / 2]);
    while (left <= right) {
        while (strcmp(ID[left].Destination, mid->Destination) < 0)
            left++;
        while (strcmp(ID[right].Destination, mid->Destination) > 0)
            right--;
        if (left <= right) {

            InfoDesk tmp = ID[left];
            ID[left] = ID[right];
            ID[right] = tmp;
            left++;
            right--;
        }
    }
    QSortByDestination(ID, right);
    QSortByDestination(ID + left, total - left);
}

void DirectSortByTime(InfoDesk* ID, int total) { //Сортировка методом прямого выбора

    for (int i = 0; i < total - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < total; j++) {
            InfoDesk* IDj = &(ID[j]);
            InfoDesk* IDm = &(ID[min_i]);
            if (IDj->Hour < IDm->Hour || (IDj->Hour == IDm->Hour && IDj->Minute < IDm->Minute)) {
                min_i = j;
            }
        }
        InfoDesk tmp = ID[i];
        ID[i] = ID[min_i];
        ID[min_i] = tmp;
    }
}

void BSearchByDestination(InfoDesk* ID, int total, char Dest[128]) { // Бинарный поиск
    if (total == 0)
        return;

    int left = 0;
    int right = total - 1;
    int middle;
    while (left < right) {
        middle = (left + right) / 2;
        if (strcmp(ID[middle].Destination, Dest) < 0)
            left = middle + 1;
        else
            right = middle;
    }

    if (strcmp(ID[left].Destination, Dest) != 0) {
        cout << "Destination not found" << endl;
        return;
    }

    while (left > 0 && strcmp(ID[left - 1].Destination, Dest) == 0) { //Линейный поиск
        left--;
    }
    while (right < total - 1 && strcmp(ID[right + 1].Destination, Dest) == 0) {
        right++;
    }
    DirectSortByTime(ID + left, right - left + 1);

    for (int i = left; i <= right; i++) {
        ShowFlight(&ID[i]);
    }
}

void Showmenu() {
    cout << "\t1 : create file" << endl;
    cout << "\t2 : add flight" << endl;
    cout << "\t3 : view flight" << endl;
    cout << "\t4 : search search by destination" << endl;
    cout << "\t5 : exit" << endl;
    cout << "\tMake choice: ";
}

void CreateFile(const char* fileName) {
    FILE* f = fopen(fileName, "wb");
    if (f == NULL) {
        cout << "cannot create file" << endl;
    }
    else {
        cout << "\nFile successfully created\n" << endl;
        fclose(f);
    }
}

void AddFlight(const char* fileName) {

    InfoDesk ID;
    if (!InputFlight(&ID)) {
        return;
    }

    FILE* f = fopen(fileName, "rb");
    if (f == NULL) {
        cout << "\ncannot open file" << endl;
    }

    else {
        int desk = fileno(f);
        long l = filelength(desk);
        int total = l / sizeof(InfoDesk);

        InfoDesk* Bubble = new InfoDesk[total + 1];
        fread(Bubble, sizeof(InfoDesk), total, f);
        Bubble[total] = ID;
        fclose(f);

        f = fopen(fileName, "wb");
        if (f == NULL) {
            cout << "\ncannot write to file" << endl;
            
        }
        else {
            QSortByDestination(Bubble, total + 1);
            fwrite(Bubble, sizeof(InfoDesk), total + 1, f);
            cout << "\nFlight successfully added!\n" << endl;
            fclose(f);
        }
        delete[] Bubble;
    }
}

void ViewFlight(int IDNumber, const char* fileName) {
    FILE* f = fopen(fileName, "rb");
    if (f == NULL) {
        cout << "\ncannot open file" << endl;
    }
    else {
        int desk = fileno(f);
        long l = filelength(desk);
        int total = l / sizeof(InfoDesk);
        if (IDNumber > total || IDNumber < 1) {
            cout << "Flight doesnt exist\n" << endl;
        }
        else {
            fseek(f, (IDNumber - 1) * sizeof(InfoDesk), 0);
            InfoDesk ID;
            fread(&ID, sizeof(InfoDesk), 1, f);
            ShowFlight(&ID);
        }
        fclose(f);
    }
}

void SearchFlight(const char* fileName) {
    char dest[128];
    cout << "specify destination: ";
    cin >> dest;

    FILE* f = fopen(fileName, "rb");
    if (f == NULL) {
        cout << "\ncannot open file" << endl;
    }

    else {
        int desk = fileno(f);
        long l = filelength(desk);
        int total = l / sizeof(InfoDesk);

        InfoDesk* Bubble = new InfoDesk[total];
        fread(Bubble, sizeof(InfoDesk), total, f);
        fclose(f);
        BSearchByDestination(Bubble, total, dest);
        delete[] Bubble;
    }
}

int main()
{
    const char* FileName = "D:\\University\\OAiP\\Sem 2\\Laba2\\InfoDesk.dat";

    bool exit = false;
    while (!exit)
    {
        Showmenu();
        char c;
        cin >> c;
        switch (c) {
        case '1':
            CreateFile(FileName); break;
        case '2':
            AddFlight(FileName); break;
        case '3':
            int Number;
            cout << "\nChoose the flight number: ";
            cin >> Number;
            ViewFlight(Number, FileName); break;
        case '4':
            SearchFlight(FileName); break;
        case '5':
            exit = true; break;
        default:
            cout << "\nWrong choice\n" << endl;
        }
    }

    return 0;
}