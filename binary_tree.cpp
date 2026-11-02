//模拟二叉树的初始化和增删改查
#include<iostream>
using namespace std;

//树的单个节点
template <typename T>
struct treenode {
	T val;
	treenode* left;
	treenode* right;
	treenode() :val(0), left(NULL), right(NULL) {};
	treenode(T n) :val(n), left(NULL), right(NULL) {};
};

//二叉树类
template<typename T>
class tree {
private:
	treenode<T>* nodes;
	treenode<T>* root;
	size_t nodesize;//变量名写成nodesize表示节点个数
	treenode<T>* createtree(T a[], int size, int nodeid, T nullnode);//把size_t改成了int
	void visit(treenode<T>* node);//visit传的参数不是整型，要的是一个节点
	void preorder(treenode<T>* node);
	void inorder(treenode<T>* node);
	void postorder(treenode<T>* node);
public:
	tree();
	tree(int maxnode);
	~tree();
	void create(T a[], int nodesize, T nullnode);
	treenode<T>* gettreenode(int nodeid);
	void preordertraval();
	void inordertraval();
	void postordertraval();
};

//无参构造
template<typename T>
tree<T>::tree() {
	nodes = new treenode<T>[10001];//为什么不要*，没懂：这是一维数组不是二维数组
	root = NULL;
	nodesize = 10001;
}

//有参构造
template<typename T>
tree<T>::tree(int maxnode) {
	nodes = new treenode<T>[maxnode];//为什么不要*，没懂。加了*就是二级指针了，nodes的变量类型应该是treenode<T>** nodes;
	root = NULL;
	nodesize = maxnode;
}

//析构
template<typename T>
tree<T>::~tree() {
	delete[] nodes;//delete是先类型后变量名，所以[]得加在前面
}

//获取结点id
template<typename T>
treenode<T>* tree<T>::gettreenode(int nodeid) {
	return &nodes[nodeid];
}

//输出当前节点的值
template<typename T>
void tree<T>::visit(treenode<T>* node) {
	cout << node->val;
}

//建树
template<typename T>
treenode<T>* tree<T>::createtree(T a[], int nodesize, int nodeid, T nullnode) {
	if (nodeid >= nodesize || a[nodeid] == nullnode) {//这里的判断从>变成了>=，这个是防止数组下标越界
		return NULL;
	}
	treenode<T>* nownode = gettreenode(nodeid);
	nownode->val = a[nodeid];
	nownode->left = createtree(a, nodesize, nodeid * 2, nullnode);
	nownode->right = createtree(a, nodesize, nodeid * 2 + 1, nullnode);
	return nownode;//改了下变量名称，得改，因为一开始的node和这类的node重名了
}

//外部调用+参数：建树
template<typename T>
void tree<T>::create(T a[], int nodesize, T nullnode) {
	root = createtree(a, nodesize, 1, nullnode);
}

//外部调用：前序遍历
template<typename T>
void tree<T>::preordertraval() {
	preorder(root);
}

//外部调用：中序遍历
template<typename T>
void tree<T>::inordertraval() {
	inorder(root);
}

//外部调用：后序遍历
template<typename T>
void tree<T>::postordertraval() {
	postorder(root);
}

//前序遍历
template<typename T>
void tree<T>::preorder(treenode<T>* node) {
	if (node) {//没懂，为什么要加这个if：这个是终止条件，如果node是空的，就可以跳出来执行前面递归的步骤了，如果没有这一步就死循环了
		visit(node);
		preorder(node->left);
		preorder(node->right);
	}
}

//中序遍历
template<typename T>
void tree<T>::inorder(treenode<T>* node) {
	if (node) {
		inorder(node->left);
		visit(node);
		inorder(node->right);
	}
}

//后序遍历
template<typename T>
void tree<T>::postorder(treenode<T>* node) {
	if (node) {
		postorder(node->left);
		postorder(node->right);
		visit(node);
	}
}

//测试
int main() {
	const char nullnode = '-';
	char a[15] = {
		nullnode, 'a', 'b', 'c', 'd',
		nullnode, 'e', 'f', 'g', 'h',
		nullnode, nullnode, nullnode, nullnode, 'i'
	};

	tree<char> T(15);
	T.create(a, 15, nullnode);
	T.preordertraval(); cout << endl;
	T.inordertraval(); cout << endl;
	T.postordertraval(); cout << endl;
	return 0;
}