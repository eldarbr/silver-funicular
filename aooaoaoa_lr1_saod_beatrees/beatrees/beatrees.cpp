//3	int	[0; 100]	Подсчет количества нечетных чисел в узлах, имеющих ровно два поддерева

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char red[] = "\x1b[31;1m";
char normal[] = "\x1b[39;49m";

struct Node { int data; Node* left; Node* right; };

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

void showTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }
    showTrunks(p->prev);
    cout << p->str;
}


void printTree(Node* root, Trunk* prev, bool isLeft)
{
    if (root == NULL) {
        return;
    }
    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);
    printTree(root->right, trunk, true);
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
    showTrunks(trunk);
    cout << " " << root->data << endl;
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}


void printTree(Node* p, int level) {
    if (p) {
        printTree(p->left, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->data << endl;
        printTree(p->right, level + 1);
    }
}

Node* addNode(int data, Node* Tree) {
    if (Tree == NULL) {
        Tree = new Node;
        Tree->data = data;
        Tree->left = NULL;
        Tree->right = NULL;
    }
    if (data < Tree->data) {
        if (Tree->left != NULL) addNode(data, Tree->left);
        else {
            Tree->left = new Node;
            Tree->left->data = data;
            Tree->left->left = NULL;
            Tree->left->right = NULL;
        }
    }
    if (data > Tree->data) {
        if (Tree->right != NULL) addNode(data, Tree->right);
        else {
            Tree->right = new Node;
            Tree->right->data = data;
            Tree->right->left = NULL;
            Tree->right->right = NULL;
        }
    }
    return Tree;
}

void searchInTree(Node* Tree, int key) {
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

void delTree(Node* Tree) {
    if (Tree != NULL) {
        delTree(Tree->right);
        delTree(Tree->left);
        delete Tree;
    }
}

int findHeight(Node* Tree) { return Tree!=NULL? 1 + max(findHeight(Tree->left), findHeight(Tree->right)):0; }

int numOfNodes(Node* Tree) { return Tree != NULL ? 1 + numOfNodes(Tree->left) + numOfNodes(Tree->right) : 0; }

int dopFun(Node* Tree) { return Tree!=NULL? Tree->data % 2 == 1 + dopFun(Tree->left) + dopFun(Tree->right):0; }


int getVariant() {
    int variant;
    cin >> variant;

    while (variant != 1 && variant != 2 && variant != 3 && variant != 4 && variant != 5 && variant != 6 && variant != 7 && variant != 8 && variant != 9) {
        cout << "Некорректное значение. Введите снова\n> ";
        cin >> variant;
    }
    return variant;
}

void menuRealization() {
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
            variant = getVariant();
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
                    Tree = addNode(arr[i], Tree);
                }
                break;
            }
        }
        else {
            bool treeView = 0;
            system("cls");
            cout << "\tДерево создано!\n";
            printTree(Tree, NULL, false);

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
            variant = getVariant();
            switch (variant)
            {
            case 1:
                printTree(Tree, NULL, false);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 2:
                cout << "\nВведите новый узел\n> ";
                int unit;
                cin >> unit;
                Tree = addNode(unit, Tree);
                break;
            case 3:     //Доделать удаление узла
                break;
            case 4:
                cout << "\nУзел с каким полем данных вы хотите найти?\n> ";
                int key;
                cin >> key;
                searchInTree(Tree, key);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 5:
                cout << "\nВысота дерева: " << findHeight(Tree);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 6:
                cout << "\nКоличество узлов в дереве: " << numOfNodes(Tree);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 7:
                cout << "\nKоличество нечетных чисел в узлах, имеющих ровно два поддерева: " << dopFun(Tree);
                cout << "\nЧтобы вернуться в меню, нажмите любую кнопку\n";
                system("pause");
                break;
            case 8:
                delTree(Tree);
                break;
            }
        }
    } while (Tree==NULL && variant != 2 || Tree!=NULL && variant != 9);
}




int main(){  menuRealization(); }