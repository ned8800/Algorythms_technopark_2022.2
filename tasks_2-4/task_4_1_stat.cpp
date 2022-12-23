/*
Требование для всех вариантов Задачи 4
Решение должно поддерживать передачу функции сравнения снаружи.

4_2. Порядковые статистики. Дано число N и N строк.
Каждая строка содержит команду добавления или удаления натуральных чисел,
 а также запрос на получение k-ой порядковой статистики.
Команда добавления числа A задается положительным числом A,
 команда удаления числа A задается отрицательным числом “-A”.
Запрос на получение k-ой порядковой статистики задается числом k. 
Требования: скорость выполнения запроса - O(log n).
*/

#include <iostream>

template <class Key>
struct Comparator {
	int operator() (const Key &a, const Key &b) {
		if(a < b) {
			return -1;
		}
		else{
			return a > b;
		}
	}
};

template <class Key, class Comparator = Comparator<Key>>
class AVLTree {
	struct Node {
		Key key;
		Node *left;
		Node *right;
		size_t height;
		size_t nodeSize;
		
		Node(const Key &key): key(key), left(nullptr), right(nullptr), height(1), nodeSize(1) {};
	};

	public:
	AVLTree(Comparator comparator = Comparator()): comparator(comparator), root(nullptr) {}
	~AVLTree() { deleteNode(root);	}

	void insert(const Key &key) {
		root = insertNode(root, key);
	}

	Key FindStatistic(size_t index) const {
		auto treeNode = root;
		size_t from = 0, to = treeNode->nodeSize;
		size_t left_size = getNodeSize(treeNode->left);
		while (index != from + left_size) {
			if (index < from + left_size) { //поиск в левом поддереве
				to -= getNodeSize(treeNode->right) + 1;
				treeNode = treeNode->left;
			} else { // иначе поиск в правом поддереве
				from += left_size + 1;
				treeNode = treeNode->right;
			}
			left_size = getNodeSize(treeNode->left);
		}
		return treeNode->key;
	}
	
	void erase(const Key &key) {
		root = eraseNode(root, key);
	}

	private:
	Node *insertNode(Node *node, const Key &key) {
		if (node == nullptr) {
			return new Node(key);
		}
		switch (comparator(key, node->key)) {
			case -1:
				node->left = insertNode(node->left, key);
				break;
			case 1:
				node->right = insertNode(node->right, key);
				break;
			default:
				return root;
		}
		return balanceTree(node);
	}
 


	Node *eraseNode(Node *node, const Key &key) {
		if (node == nullptr) {
			return nullptr;
		}
		switch (comparator(key, node->key)) {
			case -1:
				node->left = eraseNode(node->left, key);
				break;
			case 1:
				node->right = eraseNode(node->right, key);
				break;
			default:
				auto left = node->left, right = node->right;
				delete node;
				if (right == nullptr) {
					return left;
				}
				Node *right_min;
				right = removeMinNode(right, right_min);
				right_min->left = left;
				right_min->right = right;
				return balanceTree(right_min);
		}
		return balanceTree(node);
	}


	Node *rotateLeft(Node *node) {
		auto right = node->right;
		node->right = right->left;
		right->left = node;
		fixFields(node);
		fixFields(right);
		return right;
	}


	Node *rotateRight(Node *node) {
		auto left = node->left;
		node->left = left->right;
		left->right = node;
		fixFields(node);
		fixFields(left);
		return left;
	}


	Node *balanceTree(Node *node) {
		fixFields(node);
		size_t balanceTree_factor = getNodeHeight(node->right) - getNodeHeight(node->left);
		if (balanceTree_factor == 2) {
			if (getNodeHeight(node->right->right) < getNodeHeight(node->right->left)) {
				node->right = rotateRight(node->right);
			}
			return rotateLeft(node);
		} else if (balanceTree_factor == -2) {
			if (getNodeHeight(node->left->left) < getNodeHeight(node->left->right)) {
				node->left = rotateLeft(node->left);
			}
			return rotateRight(node);
		} else {
			return node;
		}
	}


	Node *removeMinNode(Node *treeNode, Node *&min) {
		if (treeNode->left == nullptr) {
			min = treeNode;
			return treeNode->right;
		}
		treeNode->left = removeMinNode(treeNode->left, min);
		return balanceTree(treeNode);
	}



	size_t getNodeHeight(Node *node) const {
		if (node == nullptr) {
			return 0;
		}
		return node->height;
	}


	void fixFields(Node *node) {
		node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
		node->nodeSize = 1 + getNodeSize(node->left) + getNodeSize(node->right);
	}


	size_t getNodeSize(Node *node) const {
		if (node == nullptr) {
			return 0;
		}
		return node->nodeSize;
	}


	void deleteNode(Node *node) {
		if (node != nullptr) {
			deleteNode(node->left);
			deleteNode(node->right);
			delete node;
		}
	}

	Comparator comparator;
	Node *root;
};


int main() {
	int n;
    int k;
	std::cin >> n;

	AVLTree<int> avlTree;
	int a;
	for(int i = 0; i < n; ++i) {
		std::cin >> a >> k;
		if (a > 0) {
			avlTree.insert((int) a);
		} else {
			avlTree.erase((int) -a);
		}
		std::cout << avlTree.FindStatistic(k) << std::endl;
	}
	return 0;
}
