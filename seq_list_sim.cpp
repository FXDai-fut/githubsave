#include<iostream>
using namespace std;

#define eleType int

struct Sequentialist {
	//eleType a[];这个是静态数组，没法进行扩容，要手动申请内存进行扩容，所以要用动态数组。
	eleType* element;
	int size;
	int capcity;
};

void initializeList(Sequentialist* list, int capcity) {
	list->element = new eleType[capcity];
	list->size = 0;
	list->capcity = capcity;
}

void destorylist(Sequentialist* list) {
	delete[] list->element;
	list->element = NULL;
}

//获取顺序表大小
int sizelist(Sequentialist* list) {
	return list->size;
}

//顺序表判空
bool isEmpty(Sequentialist* list) {
	return list->size == 0;
}

//元素插入
void insert(Sequentialist* list, int index, eleType element) {
	if (index<0 || index >list->size) {
		throw std::invalid_argument("Invalid index");
	}
	//顺序表扩容
	if (list->size == list->capcity) {
		int newcapcity = list->capcity * 2;
		eleType* newelement = new eleType[newcapcity];
		for (int i = 0; i < newcapcity / 2; ++i) {
			newelement[i] = list->element[i];
		}
		delete[] list->element;
		list->element = newelement;
		list->capcity = newcapcity;
	}
	//插入元素
	list->size++;//这一步这样改其实是变相增加了数值，因为编译器以为越了一半的界，那我多一个内存给他访问，就不存在这个问题了
	if (list->size <= list->capcity) {
		for (int i = list->size - 1; i > index; i--) {
			list->element[i] = list->element[i - 1];
		}
		list->element[index] = element;
	}
}

//元素删除
void deleteElement(Sequentialist* list, int index) {
	//这里取>=，因为删除操作不涉及扩容，最后一个元素也是可以被删除的
	if (index < 0 || index >= list->size) {
		throw std::invalid_argument("Invalid index");
	}
	//删除是覆盖操作，操作后一位数覆盖到前一位，如果不减一最后一位越界了
	for (int i = index; i < list->size - 1; i++) {
		list->element[i] = list->element[i + 1];
	}
	//习惯，动态数组只更新元素，不更新数量，记得同步更新size
	list->size--;
}

//元素查找——传索引(下标）
int findElement(Sequentialist* list, eleType element) {
	for (int i = 0; i < list->size; i++) {
		if (element == list->element[i]) return i;
	}
	return -1;//这个记得加，表示没找到元素
}

//元素获取
eleType getElement(Sequentialist* list, int index) {
	//index >= list->size也不行，超范围了
	if (index < 0 || index >= list->size) {
		throw std::invalid_argument("Invalid index");
	}
	return list->element[index];
}

//元素修改
void updateElement(Sequentialist* list, int index, eleType value) {
	if (index<0 || index >list->size) {
		throw std::invalid_argument("Invalid index");
	}
	list->element[index] = value;
}

//测试
int main() {
	Sequentialist mylist;
	initializeList(&mylist, 10);
	for (int i = 0; i < 10; i++) {
		insert(&mylist, i, i * 10);
	}
	for (int i = 0; i < sizelist(&mylist); i++) {
		cout << getElement(&mylist, i) << " ";
	}
	cout << endl;
	deleteElement(&mylist, 5);
	updateElement(&mylist, 1, 1314);
	for (int i = 0; i < sizelist(&mylist); i++) {
		cout << getElement(&mylist, i) << " ";
	}
	cout << endl;
	int idx = findElement(&mylist, 20);
	updateElement(&mylist, idx, 520);
	for (int i = 0; i < sizelist(&mylist); i++) {
		cout << getElement(&mylist, i) << " ";
	}
	destorylist(&mylist);
	return 0;
}