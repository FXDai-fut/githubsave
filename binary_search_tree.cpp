//模拟二叉搜索树的初始化和增删改查
#include<iostream>
using namespace std;

//结构体：单个树结点及初始化
template<typename T>
struct TreeNode {
	T val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() :val(0), left(NULL), right(NULL) {}
	TreeNode(T x) :val(x), left(NULL), right(NULL) {}
};

//二叉搜索树类
template<typename T>
class BinarySearchTree {
private:
	TreeNode<T>* root;
	TreeNode<T>* insertNode(TreeNode<T>* node, T value);
	TreeNode<T>* removeNode(TreeNode<T>* node, T value);
	bool searchNode(TreeNode<T>* node, T value);
	void inorder(TreeNode<T>* node);

//二叉搜索树类：外部调用
public:
	BinarySearchTree() :root(NULL) {}
	~BinarySearchTree();

	void inordertravel() {
		inorder(root);
		cout << endl;
	}

	void insert(T value) {
		root = insertNode(root, value);
	}

	void remove(T value) {
		root = removeNode(root, value);
	}

	bool search(T value) {
		return searchNode(root, value);
	}
};

//析构函数
template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	while (root) {
		remove(root->val);
	}
}

//结点插入
template<typename T>
TreeNode<T>* BinarySearchTree<T>::insertNode(TreeNode<T>* node, T value) {
	if (node == NULL) {
		TreeNode<T>* nownode = new TreeNode<T>(value);//这里忘了写模板了
		return nownode;
	}
	if (node->val > value) {
		node->left = insertNode(node->left, value);
	}
	if (node->val < value) {
		node->right = insertNode(node->right, value);
	}
	return node;//我写的是return NULL，正确答案是return node
}

//结点删除
template<typename T>
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* node, T value) {
	if (node == NULL) {
		return NULL;
	}
	if (node->val > value) {
		node->left = removeNode(node->left, value);//需要用node->left承接，我先不写，看看为什么需要
	}
	if (node->val < value) {
		node->right = removeNode(node->right, value);
	}
	if (node->val == value) {
		if (node->left == NULL && node->right == NULL) {
			delete node;
			return NULL;
		}
		else if (node->right == NULL) {//else if的好处是一步一步往下走
			TreeNode<T>* leftchild = node->left;
			delete node;
			return leftchild;
		}
		else if (node->left == NULL) {
			TreeNode<T>* rightchild = node->right;
			delete node;
			return rightchild;
		}
		else if (node->left && node->right) {
			TreeNode<T>* tmp = node->right;
			while (tmp->left) {
				tmp = tmp->left;
			}
			node->val = tmp->val;
			node->right = removeNode(node->right, tmp->val);
		}
	}
	return node;
}

//根据value查找结点是否存在
template<typename T>
bool BinarySearchTree<T>::searchNode(TreeNode<T>* node, T value) {
	if (node == NULL) {
		return false;
	}
	if (node->val > value) {
		return searchNode(node->left, value);//我不需要一个变量去承接返回的值，直接return就好了
	}
	if (node->val < value) {
		return searchNode(node->right, value);
	}
	return true;
}

//中序遍历
template<typename T>
void BinarySearchTree<T>::inorder(TreeNode<T>* node) {
	if (node) {
		inorder(node->left);
		cout << node->val << ',';
		inorder(node->right);
	}
}

//测试
int main() {
	BinarySearchTree<int> bst;
	bst.insert(50);
	bst.insert(30);
	bst.insert(70);
	bst.insert(40);
	bst.insert(80);
	bst.insert(60);
	bst.insert(100);

	bst.inordertravel();
	cout << bst.search(100) << endl;
	cout << bst.search(50) << endl;

	bst.remove(70);
	bst.inordertravel();

	bst.insert(65);
	bst.inordertravel();

	return 0;
}