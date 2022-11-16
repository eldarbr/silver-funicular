//3	int	[0; 100]	Подсчет количества нечетных чисел в узлах, имеющих ровно два поддерева

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char red[] = "\x1b[31;1m";
char normal[] = "\x1b[39;49m";

struct Node {
    int data; Node* left; Node* right; 
};

struct Trunk
{
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

void ShowTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }
    ShowTrunks(p->prev);
    cout << p->str;
}


void PrintTree(Node* root, Trunk* prev, bool isLeft)
{
    if (root == NULL) {
        return;
    }
    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);
    PrintTree(root->right, trunk, true);
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
    ShowTrunks(trunk);
    cout << " " << root->data << endl;
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    PrintTree(root->left, trunk, false);
}


void PrintTree(Node* p, int level) {
    if (p) {
        PrintTree(p->left, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->data << endl;
        PrintTree(p->right, level + 1);
    }
}

Node* AddNode(int data, Node* Tree) {
    if (Tree == NULL) {
        Tree = new Node;
        Tree->data = data;
        Tree->left = NULL;
        Tree->right = NULL;
    }
    if (data < Tree->data) {
        if (Tree->left != NULL) AddNode(data, Tree->left);
        else {
            Tree->left = new Node;
            Tree->left->data = data;
            Tree->left->left = NULL;
            Tree->left->right = NULL;
        }
    }
    if (data > Tree->data) {
        if (Tree->right != NULL) AddNode(data, Tree->right);
        else {
            Tree->right = new Node;
            Tree->right->data = data;
            Tree->right->left = NULL;
            Tree->right->right = NULL;
        }
    }
    return Tree;
}

void SearchInTree(Node* Tree, int key) {
    bool found = 0;
    Node* now = Tree;
    while (now && !found) {
        if (key == now->data) found = true;
        else if (key > now->data) now = now->right;
        else now = now->left;
    }
    if (found) cout << "Узел с ключом " << key << " существует!\n";
    else cout << "Узла с ключом " << key << " НЕ существует!\n";
}

void DelTree(Node* Tree) {
    if (Tree != NULL) {
        DelTree(Tree->right);
        DelTree(Tree->left);
        delete Tree;
    }
}

int FindHeight(Node* Tree) {
    if (Tree != NULL) {
        return 1 + max(FindHeight(Tree->left), FindHeight(Tree->right));
    }
    else {
        return 0;
    }
}

int NumOfNodes(Node* Tree) {
    if (Tree != NULL) {
        return 1 + NumOfNodes(Tree->left) + NumOfNodes(Tree->right);
    }
    else {
        return 0;
    }
}

int DopFun(Node* Tree) {
    if (Tree != NULL) {
        return Tree->data % 2 == 1 + DopFun(Tree->left) + DopFun(Tree->right);
    }
    else {
        return 0;
    }
}


int GetVariant() {
    int variant;
    cin >> variant;

    while (variant != 1 && variant != 2 && variant != 3 && variant != 4 && variant != 5 && variant != 6 && variant != 7 && variant != 8 && variant != 9) {
        cout << "Некорректное значение. Введите снова\n> ";
        cin >> variant;
    }
    return variant;
}

void MenuRealization() {
    setlocale(LC_ALL, "rus");
    Node* Tree = new Node;
    Tree = NULL;
    int variant;
    do {
        if (Tree == NULL) {
            system("cls");
            cout << red << "\tДерево не создано!\n" << normal
                << "Что вы хотите сделать?\n"
                << "1. Создать дерево из n элементов\n"
                << "2. Выйти из программы\n"
                << "> ";
            variant = GetVariant();
            switch (variant)
            {
            case 1:
                int n;
                cout << "Введите количество узлов создаваемого дерева\n> ";
                cin >> n;
                int* arr = new int[n];
                cout << "\nВведите " << red << n << normal << " целочисленных чисел\n> ";
                for (int i = 0; i < n; i++) {
                    cin >> arr[i];
                    Tree = AddNode(arr[i], Tree);
                }
                break;
            }
        }
        else {
            bool treeView = 0;
            system("cls");
            cout << "\tДерево создано!\n";
            PrintTree(Tree, NULL, false);

            cout << "\nЧто вы хотите сделать?\n"
                << "1. Вывести дерево на экран\n"
                << "2. Добавить новый узел\n"
                << "3. Удалить узел\n"
                << "4. Узнать, существует ли в дереве узел с искомым полем данных\n"
                << "5. Найти высоту дерева\n"
                << "6. Найти количество узлов в дереве\n"
                << "7. Найти количество нечетных чисел в узлах, имеющих ровно два поддерева\n"
                << "8. Удалить дерево\n"
                << "9. Выйти из программы\n"
                << "> ";
            variant = GetVariant();
            switch (variant)
            {
            case 1:
                PrintTree(Tree, NULL, false);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 2:
                cout << "\nВведите новый узел\n> ";
                int unit;
                cin >> unit;
                Tree = AddNode(unit, Tree);
                break;
            case 3:     //Доделать удаление узла
                break;
            case 4:
                cout << "\nУзел с каким полем данных вы хотите найти?\n> ";
                int key;
                cin >> key;
                SearchInTree(Tree, key);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 5:
                cout << "\nВысота дерева: " << FindHeight(Tree);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 6:
                cout << "\nКоличество узлов в дереве: " << NumOfNodes(Tree);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 7:
                cout << "\nKоличество нечетных чисел в узлах, имеющих ровно два поддерева: " << DopFun(Tree);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 8:
                DelTree(Tree);
                break;
            }
        }
    } while (Tree==NULL && variant != 2 || Tree!=NULL && variant != 9);
}




int main(){ 
    MenuRealization(); 
}
