#include <iostream>

using namespace std;

struct Tree {
    int id;
    char ticker[7];

    int balance; //Баланс текущей вершины
    Tree* left;
    Tree* right;
};


Tree* CreateLeaf(int id, const char* ticker) {
    Tree* leaf = new Tree;
    leaf->id = id;
    strcpy_s(leaf->ticker, ticker);
    leaf->left = NULL;
    leaf->right = NULL;
    leaf->balance = 0;
    return leaf;
}

Tree* FindMin(Tree* root) {
    if (root == NULL) return NULL;

    if (root->left == NULL) return root;

    return FindMin(root->left);
}

bool CheckDuplicate(Tree* root, int id) {
    if (root == NULL) {
        return false;
    }
    if (root->id == id) {
        return true;
    }
    return CheckDuplicate(root->left, id) || CheckDuplicate(root->right, id);
}

void ViewTree_RNL(Tree* leaf, int level, int& sum) { //Right-Node-Left - обход в порядке убывания
    if (leaf) {
        ViewTree_RNL(leaf->right, level + 1, sum);

        for (int i = 0; i < level * 10; i++) {
            cout << ' ';
        }
        cout << "[" << leaf->id << "] " << leaf->ticker << " \n\n";
        sum += leaf->id;

        ViewTree_RNL(leaf->left, level + 1, sum);
    }
}

void ViewTree_NLR(Tree* leaf, int level) { //Node-Left-Right обход - прямой обход дерева
    if (leaf == NULL) return;

    for (int i = 0; i < level * 10; i++) cout << " ";

    cout << "[" << leaf->id << "] " << leaf->ticker << endl << endl;

    ViewTree_NLR(leaf->left, level + 1);
    ViewTree_NLR(leaf->right, level + 1);
}

void ViewTree_LRN(Tree* leaf, int level) { //Left-Right-Node обход - обратный обход дерева
    if (leaf == NULL) return;

    ViewTree_LRN(leaf->left, level + 1);
    ViewTree_LRN(leaf->right, level + 1);

    for (int i = 0; i < level * 10; i++) cout << " ";

    cout << "[" << leaf->id << "] " << leaf->ticker << endl << endl;
}

Tree* SearchLeaf(Tree* root, int id) {
    if (root == NULL || root->id == id) return root;

    if (id < root->id) return SearchLeaf(root->left, id); // Если ключ меньше, ключа корня, то идем влево
    
    else return SearchLeaf(root->right, id); // Иначе вправо
}

int FindNearestKey(Tree* root, int avg) {
    int nearest = root->id;
    int diff = abs(root->id - avg);

    if (root->left != NULL) {
        int left_nearest = FindNearestKey(root->left, avg);
        int left_diff = abs(left_nearest - avg);
        if (left_diff < diff) {
            nearest = left_nearest;
            diff = left_diff;
        }
    }

    if (abs(root->id - avg) < diff) {
        nearest = root->id;
        diff = abs(root->id - avg);
    }

    if (root->right != NULL) {
        int right_nearest = FindNearestKey(root->right, avg);
        int right_diff = abs(right_nearest - avg);
        if (right_diff < diff) {
            nearest = right_nearest;
            diff = right_diff;
        }
    }

    return nearest;
}

Tree* DeleteLeaf(Tree* root, int id) {
    if (root == NULL) return root;

    if (id < root->id)
        root->left = DeleteLeaf(root->left, id);
    else if (id > root->id)
        root->right = DeleteLeaf(root->right, id);
    else {
        // Если нет потомков
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        // Если есть только один потомок
        else if (root->left == NULL) { 
            Tree* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL) {
            Tree* temp = root;
            root = root->left;
            delete temp;
        }
        // Если есть два потомка
        else {
            Tree* temp = FindMin(root->right); //Ищем минимальный узел в правом поддереве
            root->id = temp->id; // Заменяем id удаляемого узла на id минимального узел
            char* temp_ticker = temp->ticker; 
            strcpy_s(root->ticker, temp_ticker); // Заменяем ticker удаляемого узла на ticker минимального узел
            root->right = DeleteLeaf(root->right, temp->id); // Рекурсивно удаляем  минимальный узел из правого поддерева
        }
    }
    return root;
}

void DeleteTree(Tree* root) {
    if (root != NULL) {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
    }
}


//Балансировка дерева AVL

int Max(int leftHeight, int rightHeight) {
    if (leftHeight > rightHeight) return leftHeight;
    else return rightHeight;
}

int GetHeight(Tree* leaf) { //Вычисляет высоту дерева
    if (leaf == NULL) { //Если дерево пусто, то возвращаем 0
        return 0;
    }
    int leftHeight = GetHeight(leaf->left); //Высота левого поддерева
    int rightHeight = GetHeight(leaf->right); //Высота правого поддерева
    
    return 1 + Max(leftHeight, rightHeight); //Возращаем большую высоту из поддеревьев, прибавляя к этому еще 1 (текущий узел)
}

void SetBalance(Tree* (&leaf)) {
    if (leaf != NULL) {
        leaf->balance = GetHeight(leaf->right) - GetHeight(leaf->left);
    }
}

void RightRotate(Tree* (&leaf)) {
    Tree* left = leaf->left;
    Tree* LeftRight = left->right; //Правое поддерево для левого

    left->right = leaf;
    leaf->left = LeftRight;
    leaf = left;

    SetBalance(leaf->right);
    SetBalance(leaf);
}

void LeftRotate(Tree* (&leaf)) {
    Tree* right = leaf->right;
    Tree* RightLeft = right->left; //Левое поддерево для правого

    right->left = leaf;
    leaf->right = RightLeft;
    leaf = right;

    SetBalance(leaf->left);
    SetBalance(leaf);
}

void Insert(Tree* (&root), int id, const char* ticker) {
    if (CheckDuplicate(root, id)) {
        cout << "This ID already exists" << endl;
        return;
    }

    // вставка узла как в обычном бинарном дереве
    if (root == NULL) {
        root = CreateLeaf(id, ticker);
    }
    else if (id < root->id) {
        Insert(root->left, id, ticker);
        if (GetHeight(root->left) - GetHeight(root->right) > 1) {
            if (GetHeight(root->left->left) < GetHeight(root->left->right)) LeftRotate(root->left); //Левый правый поворот
            RightRotate(root);
        }
    }
    else {
        Insert(root->right, id, ticker);
        if (GetHeight(root->right) - GetHeight(root->left) > 1) {
            if (GetHeight(root->right->right) < GetHeight(root->right->left)) RightRotate(root->right); //Правый левый поворот
            LeftRotate(root);
        }
    }

    SetBalance(root);
}





void ShowMenu(int level) {
    if (level == 0) {
        cout << "\t[1] > add new stock" << endl;
        cout << "\t[2] > view tree" << endl;
        cout << "\t[3] > search stock by ID" << endl;
        cout << "\t[4] > delete stock by ID" << endl;
        cout << "\t[5] > individual task" << endl;
        cout << "\t[6] > exit" << endl;
    }
    else {
        cout << "\t[1] > Pre order tree traversal" << endl;
        cout << "\t[2] > In order tree traveral" << endl;
        cout << "\t[3] > Post order tree traversal" << endl;
    }
    cout << "\n\n\tMake choice: ";
    
}


int main()
{
    Tree* root = NULL;
    int id;
    char ticker[7];
    cout << "Input new root ticker: ";
    cin >> ticker;
    cout << "Input new root ID: ";
    cin >> id;
    cout << endl;

    int amount = 1; // Количество нод
    int total = 0; // сумма всех значений нод
    double avg = 0; //Среднее значение всех ключей
    Insert(root, id, ticker);

    while (true) {
        ShowMenu(0);
        int choice;
        cin >> choice;
        cout << "\n\n";

        switch (choice){
        case 0: {
            Insert(root, 1, "GOOG");
            Insert(root, 33, "V");
            Insert(root, 21, "MSFT");
            Insert(root, 45, "META");
            Insert(root, 54, "TSLA");
            Insert(root, 66, "MA");
            Insert(root, 71, "AMD");
            Insert(root, 85, "ADBE");
            Insert(root, 96, "NVDA");
            Insert(root, 101, "NKE");
            Insert(root, 118, "KO");
            Insert(root, 129, "AMZN");
            Insert(root, 133, "BRK.A");
            Insert(root, 145, "WMT");
            amount += 14;

        } break;
        case 1: {
            cout << "\nInput new ticker: ";
            cin >> ticker;
            cout << "Input new ID: ";
            cin >> id;
            cout << endl;
            Insert(root, id, ticker);
            amount++;
            
        } break;
        case 2: {
            cout << "\ntotal nodes: " << amount << "\n";
            cout << "-------------------"<< "\n\n";
            if (amount > 0) {
                ShowMenu(1);
                cin >> choice;
                cout << "\n\n";
                switch (choice) {
                case 1: ViewTree_NLR(root, 1); break;
                case 2: ViewTree_RNL(root, 1, total); break;
                case 3: ViewTree_LRN(root, 1); break;
                }
                
            } 
            else cout << "There are no tree\n\n";
        } break;
        case 3: {
            cout << "\nInput ID, you want to find: ";
            cin >> id;
            Tree* leaf = SearchLeaf(root, id);
            if (leaf == NULL) {
                cout << "Ticker with ID [" << id << "] does not exist\n\n";
            }
            else {
                cout << "[" << leaf->id << "] > " << leaf->ticker<<"\n\n";
            }
            
        } break;
        case 4: {
            cout << "\nInput ID, you want to delete: ";
            cin >> id;
            Tree* leaf = SearchLeaf(root, id);
            if (leaf == NULL) {
                cout << "Ticker with ID [" << id << "] does not exist\n\n";
            }
            else {
                root = DeleteLeaf(root, id);
                cout << "Ticker with ID [" << id << "] successfully deleted\n\n";
                amount--;
            }
        } break;
        case 5: { 
            total = 0;
            ViewTree_RNL(root, 1, total);
            avg = total / amount; //Поправить
            cout << "Average of all keys: " << avg << endl;
            cout << "Nearest key: " << FindNearestKey(root, avg) << endl << endl;

        } break;
        case 6: {
            DeleteTree(root);
            return 0; 
        }
        default: cout << "\nIncorrect choice\n"; break;
        }
    }
    
}
