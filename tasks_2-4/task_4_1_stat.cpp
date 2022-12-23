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
		return a < b ? -1 : a > b;
	}
};

template <class Key, class Comparator = Comparator<Key>>
class AVLTree {
	struct Node {
		Key key;
		Node *left, *right;
		int8_t h_diff;
		size_t size;
		explicit Node(const Key&);
	};
private:
	Comparator key_comparator;
	Node *root;
	Node *insert_node(Node*, const Key&);
	Node *erase_node(Node*, const Key&);
	Node *rotate_left(Node*);
	Node *rotate_right(Node*);
	Node *balance(Node*);
	Node *remove_min_node(Node*, Node*&);
	int8_t get_node_h_diff(Node*) const;
	void fix_node_fields(Node*);
	size_t get_node_size(Node*) const;
	void delete_node(Node*);
public:
	explicit AVLTree(Comparator key_comparator = Comparator());
	~AVLTree();
	void insert(const Key &);
	Key find_ord_stats(size_t) const;
	void erase(const Key &);
};


template<class Key, class Comparator>
AVLTree<Key, Comparator>::Node::Node(const Key &key): key(key), left(nullptr), right(nullptr), h_diff(1), size(1) {
}

template<class Key, class Comparator>
AVLTree<Key, Comparator>::AVLTree(Comparator key_comparator): key_comparator(key_comparator), root(nullptr) {
}

template<class Key, class Comparator>
void AVLTree<Key, Comparator>::insert(const Key &key) {
	root = insert_node(root, key);
}

template<class Key, class Comparator>
Key AVLTree<Key, Comparator>::find_ord_stats(size_t index) const { //корректность значения index не проверяется
	auto node = root;
	size_t from = 0, to = node->size; //поиск в полуинтервале [from; to)
	size_t node_left_size = get_node_size(node->left);
	while (index != from + node_left_size) {
		if (index < from + node_left_size) { //поиск в левом поддереве current_node
			to -= get_node_size(node->right) + 1;
			node = node->left;
		} else { //поиск в правом поддереве current_node
			from += node_left_size + 1;
			node = node->right;
		}
		node_left_size = get_node_size(node->left);
	}
	return node->key;
}

template<class Key, class Comparator>
void AVLTree<Key, Comparator>::erase(const Key &key) {
	root = erase_node(root, key);
}

template<class Key, class Comparator>
typename AVLTree<Key, Comparator>::Node *AVLTree<Key, Comparator>::insert_node(Node *node, const Key &key) {
	if (node == nullptr) {
		return new Node(key);
	}
	switch (key_comparator(key, node->key)) {
		case -1:
			node->left = insert_node(node->left, key);
			break;
		case 1:
			node->right = insert_node(node->right, key);
			break;
		default:
			return root;
	}
	return balance(node);
}

template<class Key, class Comparator>
typename AVLTree<Key, Comparator>::Node *AVLTree<Key, Comparator>::erase_node(Node *node, const Key &key) {
	if (node == nullptr) {
		return nullptr;
	}
	switch (key_comparator(key, node->key)) {
		case -1:
			node->left = erase_node(node->left, key);
			break;
		case 1:
			node->right = erase_node(node->right, key);
			break;
		default: //case 0: (equals)
			auto left = node->left, right = node->right;
			delete node;
			if (right == nullptr) {
				return left;
			}
			Node *right_min; //здесь будет указатель на минимальный узел правого поддерева удалённого узла node
			right = remove_min_node(right, right_min); //передаём указатель на правое поддерево узла node и ссылку
			right_min->left = left;
			right_min->right = right;
			return balance(right_min);
	}
	return balance(node);
}

template<class Key, class Comparator>
typename AVLTree<Key, Comparator>::Node *AVLTree<Key, Comparator>::balance(Node *node) {
	fix_node_fields(node);
	int8_t balance_factor = get_node_h_diff(node->right) - get_node_h_diff(node->left);
	if (balance_factor == 2) {
		if (get_node_h_diff(node->right->right) < get_node_h_diff(node->right->left)) {
			node->right = rotate_right(node->right);
		}
		return rotate_left(node);
	} else if (balance_factor == -2) {
		if (get_node_h_diff(node->left->left) < get_node_h_diff(node->left->right)) {
			node->left = rotate_left(node->left);
		}
		return rotate_right(node);
	} else {
		return node;
	}
}

template<class Key, class Comparator>
typename AVLTree<Key, Comparator>::Node *AVLTree<Key, Comparator>::rotate_left(Node *node) { //малый левый поворот
	auto right = node->right;
	node->right = right->left;
	right->left = node;
	fix_node_fields(node);
	fix_node_fields(right);
	return right;
}

template<class Key, class Comparator>
typename AVLTree<Key, Comparator>::Node *AVLTree<Key, Comparator>::rotate_right(Node *node) { //малый правый поворот
	auto left = node->left;
	node->left = left->right;
	left->right = node;
	fix_node_fields(node);
	fix_node_fields(left);
	return left;
}

template<class Key, class Comparator>
void AVLTree<Key, Comparator>::fix_node_fields(Node *node) {
	node->h_diff = 1 + std::max(get_node_h_diff(node->left), get_node_h_diff(node->right));
	node->size = 1 + get_node_size(node->left) + get_node_size(node->right);
}

template<class Key, class Comparator>
int8_t AVLTree<Key, Comparator>::get_node_h_diff(Node *node) const {
	if (node == nullptr) {
		return 0;
	}
	return node->h_diff;
}

template<class Key, class Comparator>
size_t AVLTree<Key, Comparator>::get_node_size(Node *node) const {
	if (node == nullptr) {
		return 0;
	}
	return node->size;
}

template<class Key, class Comparator>
AVLTree<Key, Comparator>::~AVLTree() {
	delete_node(root);
}

template<class Key, class Comparator>
void AVLTree<Key, Comparator>::delete_node(Node *node) {
	if (node != nullptr) {
		delete_node(node->left);
		delete_node(node->right);
		delete node;
	}
}

template<class Key, class Comparator>
typename AVLTree<Key, Comparator>::Node *AVLTree<Key, Comparator>::remove_min_node(Node *node, Node *&min) {
	if (node->left == nullptr) {
		min = node; //запоминаем минимальный узел текущего поддерева
		return node->right;
	}
	node->left = remove_min_node(node->left, min);
	return balance(node);
}


int main() {
	int n;
    int k;
	std::cin >> n;

	AVLTree<int> avl_tree;
	int a;
	for(int i = 0; i < n; ++i) {
		std::cin >> a >> k;
		if (a > 0) {
			avl_tree.insert((int) a);
		} else {
			avl_tree.erase((int) -a);
		}
		std::cout << avl_tree.find_ord_stats(k) << std::endl;
	}
	return 0;
}
