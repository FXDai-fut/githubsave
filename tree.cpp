//模拟多叉树的初始化和增删改查
#include<iostream>
using namespace std;

//结点:next指向的是同一树高的下一个节点，data是当前节点的值
template<typename T>
struct listcode {
	T data;
	listcode* next;
	listcode(T d) :data(d), next(NULL) {}
};

//多叉树结点:childhead指向最左边的子节点，T data记录的是当前节点值
template<typename T>
struct treecode {
	T data;
	listcode <treecode<T>*>* childhead;
	treecode() {
		childhead = NULL;
	}
	void Addchild(treecode<T>* node) {
		listcode <treecode<T>*>* childnode = new listcode<treecode<T>*>(node);
		if (childhead == NULL) {
			childhead = childnode;
		}
		else {
			childnode->next = childhead;
			childhead = childnode;
		}
	}
};

//多叉树类:nodes:结构体数组，用于存储每个结点及结点数量，root指首结点，链表用于记录结点之间的关系
template<typename T>
class tree {
private:
	treecode<T>* nodes;
	treecode<T>* root;
public:
	tree();
	tree(int maxcode);
	~tree();
	treecode<T>* getcode(int id);
	void setroot(int rootid);
	void addchildcode(int parentid, int childid);
	void assigndata(int id, T data);
	void print(treecode<T>* node);
};

//无参构造
template<typename T>
tree<T>::tree() {
	nodes = new treecode<T>[10001];//老是忘了加<T>
}

//有参构造
template<typename T>
tree<T>::tree(int maxcode) {
	nodes = new treecode<T>[maxcode];
}

//析构
template<typename T>
tree<T>::~tree() {
	delete[] nodes;
}

//根据索引获取结点
template<typename T>
treecode<T>* tree<T>::getcode(int id) {
	return &nodes[id];
}

//首结点地址赋值给root
template<typename T>
void tree<T>::setroot(int rootid) {
	root = getcode(rootid);
}

//根据所获得的结点id，建立两个结点的关系
template<typename T>
void tree<T>::addchildcode(int parentid, int childid) {
	treecode<T>* facode = getcode(parentid);//这里的节点应该是树节点而不是链表节点，因为addchild是树节点的成员函数
	treecode<T>* childcode = getcode(childid);
	facode->Addchild(childcode);
}

//结点值修改
template<typename T>
void tree<T>::assigndata(int id, T data) {
	getcode(id)->data = data;
}

//输出整棵树
template<typename T>
void tree<T>::print(treecode<T>* node) {
	if (node == NULL) {
		node = root;
	}
	cout << node->data;
	listcode <treecode<char>*>* tmp = node->childhead;
	while (tmp) {
		print(tmp->data);
		tmp = tmp->next;
	}
}

int main() {
	tree<char> T(9);//这里出现的T我其实没明白—>实例化的对象名称
	T.setroot(0);
	T.assigndata(0, 'a');
	T.assigndata(1, 'b');
	T.assigndata(2, 'c');
	T.assigndata(3, 'd');
	T.assigndata(4, 'e');
	T.assigndata(5, 'f');
	T.assigndata(6, 'g');
	T.assigndata(7, 'h');
	T.assigndata(8, 'i');
	T.addchildcode(0, 2);
	T.addchildcode(0, 1);
	T.addchildcode(1, 3);
	T.addchildcode(2, 5);
	T.addchildcode(2, 4);
	T.addchildcode(3, 8);
	T.addchildcode(3, 7);
	T.addchildcode(3, 6);
	T.print(0);
	return 0;
}