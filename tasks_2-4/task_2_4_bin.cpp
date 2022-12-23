/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

Задача 2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).
*/

#include <iostream>
#include <queue>
#include <vector>

template<class T>
struct BinTreeNode {
    BinTreeNode(const T &element) : data(element), left(nullptr), right(nullptr) {};

    T data;
    BinTreeNode *left = nullptr;
    BinTreeNode *right = nullptr;
};

template<class T>
class BinTree {
public:
    BinTree() : buff(nullptr) {}

    ~BinTree() {
        std::queue<BinTreeNode<T> *> deletionQueue;
        deletionQueue.push(buff);
        while (!deletionQueue.empty()) {
            BinTreeNode<T> *current = deletionQueue.front();
            if (current->left) {
                deletionQueue.push(current->left);
            }
            if (current->right) {
                deletionQueue.push(current->right);
            }
            delete current;
            deletionQueue.pop();
        }
    }

    void add(const T &element) {
        if (buff == nullptr) {
            buff = new BinTreeNode(element);
        } else {
            BinTreeNode<T> *treeNode = buff;
            while (true) {
                if (treeNode->data <= element) {
                    if (treeNode->right == nullptr) {
                        treeNode->right = new BinTreeNode(element);
                        break;
                    }
                    treeNode = treeNode->right;
                } else {
                    if (treeNode->left == nullptr) {
                        treeNode->left = new BinTreeNode(element);
                        break;
                    }
                    treeNode = treeNode->left;
                }
            }
        }
    }


    std::queue<T> extractAll() {
        std::queue<T> tempQueue;
        if (!buff) {
            return tempQueue;
        }
        std::queue<BinTreeNode<T> *> binNodeQueue;
        binNodeQueue.push(buff);
        while (!binNodeQueue.empty()) {
            BinTreeNode<T> *node = binNodeQueue.front();
            binNodeQueue.pop();
            tempQueue.push(node->data);
            if (node->left) {
                binNodeQueue.push(node->left);
            }
            if (node->right) {
                binNodeQueue.push(node->right);
            }
        }
        return tempQueue;
    }

private:
    BinTreeNode<T> *buff = nullptr;
};


int main() {
    size_t count = 0;
    std::cin >> count;
    BinTree<int> binTree;
    int element = 0;
    for (size_t i = 0; i < count; i++) {
        std::cin >> element;
        binTree.add(element);
    }
    std::queue<int> queue = binTree.extractAll();
    while (!queue.empty()) {
        std::cout << queue.front() << ' ';
        queue.pop();
    }
    return 0;
}
