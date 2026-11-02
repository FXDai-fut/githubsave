//模拟哈希的初始化和增删改查
#include<iostream>
using namespace std;

//哈希结点：键值对
template<typename KeyType,typename ValueType>
class Hashnode {
public:
	KeyType key;
	ValueType value;
	Hashnode* next;

	//这里可以直接初始化函数，最好写成const&是因为keytype类型不知道，防止拷贝过大
	Hashnode(const KeyType& key, const ValueType& value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

//哈希桶类
template<typename KeyType, typename ValueType>
class HashTable {
private:
	int size;
	Hashnode<KeyType,ValueType>** table;//这里忘记添加类模板参数了
	
	int hash(const KeyType& key) const{//这里我没有加const修饰函数，按理说这个hash是不应该被修改的
		int hashkey;
		hashkey = key % size;
		if(hashkey < 0) {//不需要循环，一般余数会小于除数，加一次就好
			hashkey = hashkey + size;
		}
		return hashkey;
	}
public:
	HashTable(int size=1000);//默认构造尺寸为1000的哈希表
	~HashTable();
	//增
	void insert(const KeyType& key, const ValueType& value);//插入键值对需要值，但是删除键值对不需要值，这里一下子没想通
	//删
	void remove(const KeyType& key);
	//查
	bool find(const KeyType& key, ValueType& value)const;//查找指定值应该返回bool以确定是否找到此值，且函数不可被修改，要const。find的value可被修改，不需要const修饰。查找不需要修改参数，所以函数最好加上const
	//改
	void operator[](const KeyType& key);
};

//构造函数
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int size) {
	this->size = size;
	this->table = new Hashnode<KeyType, ValueType>* [size];//这里一定强调this吗？还是说习惯
	for (int i = 0;i < size;i++) {
		table[i] = nullptr;
	}
}

//析构函数
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
	for (int i = 0;i < size;i++) {
		if (table[i]) {
			Hashnode<KeyType, ValueType>* curr = table[i];
			/*while (curr) {
				curr = curr->next;
				delete table[i];这样写有严重的bug，永远只删第一个
			}*/
			while (curr) {
				Hashnode<KeyType, ValueType>* temp = curr->next;
				delete curr;
				curr = temp;
			}//一个类，理应有析构函数，但是在这里，hashtable的析构函数顺带把hashnode给析构掉了，不存在泄露，所以hashnode其实可以写成结构体
		}
	}
	delete[] table;
}

//元素插入
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
	int index = hash(key);
	Hashnode<KeyType, ValueType>* newnode = new Hashnode<KeyType, ValueType>(key,value);
	if (table[index]==nullptr) {
		table[index] = newnode;
	}
	else {
		newnode->next = table[index];
		table[index] = newnode;
	}
}

//元素删除
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key) {//我这个写法就是可以不执行后面的，但有个弊端，如果多次添加重复键值对，删不干净，因为while不执行了
	int index = hash(key);
	/*if (table[index]) {
		Hashnode<KeyType, ValueType>* curr = table[index];
		if (curr->key == key) {
			table[index] = table[index]->next;
			delete curr;
			return;
		}
		while (curr->next && curr->next->key != key) {
			curr = curr->next;
		}
		Hashnode<KeyType, ValueType>* temp = curr->next;
		curr->next = temp->next;
		delete temp;
	}*/
	if (table[index]) {
		if (table[index]->key == key) {
			Hashnode<KeyType, ValueType>* next = table[index]->next;
			delete table[index];
			table[index] = next;
		}
		else {
			Hashnode<KeyType, ValueType>* curr = table[index];
			while (curr->next && curr->next->key != key) {
				curr = curr->next;
			}
			if (curr->next) {
				Hashnode<KeyType, ValueType>* next = curr->next->next;
				delete curr->next;
				curr->next = next;
			}
		}
	}
}

//值查找
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::find(const KeyType& key, ValueType& value) const {
	int index = hash(key);
	if (table[index]) {
		if (table[index]->key == key) {
			value = table[index]->value;
			return true;
		}
		else {
			Hashnode<KeyType, ValueType>* curr = table[index];
			while (curr->next && curr->next->key != key) {
				curr = curr->next;
			}
			if (curr->next) {
				value = curr->next->value;
				return true;
			}
		}
	}
	return false;
}

//哈希计数器：
template<typename KeyType>
class Hashcounter {
private:
	int *counter;//计数器：存放数值的地方
	int counterindex;//计数器索引
	int countersize;//计数器大小
	HashTable<KeyType,int>* hash;//哈希表

public:
	Hashcounter(int size=256);
	~Hashcounter();
	void reset();
	int add(const KeyType& key);
	int sub(const KeyType& key);
	int get(const KeyType& key);
};

//计数器构造
template<typename KeyType>
Hashcounter<KeyType>::Hashcounter(int size) {
	this->countersize = size;
	this->counter = new int[countersize];//new后面写的是类型，类型！！！
	this->counterindex = 0;
	hash = NULL;//这句话也很重要别忘了	
	reset();
}

//计数器析构
template<typename KeyType>
Hashcounter<KeyType>::~Hashcounter() {
	delete []counter;//new的是数组，delete的肯定也是数组，[]得加
	//delete之前是不是得检查一下hash是不是空的，万一double free呢？
	if (hash) {
		delete hash;
		hash = NULL;
	}
}

//计数器析构
template<typename KeyType>
void Hashcounter<KeyType>::reset() {
	if (hash) {
		delete hash;
		hash = NULL;
	}
	hash = new HashTable<KeyType,int>(countersize);//没有设置哈希表长度，但其实不设置也行。
	counterindex = 0;
	for (int i = 0;i < countersize;i++) {
		counter[i] = 0;
	}
}

//查找元素：计数器数值+1
template<typename KeyType>
int Hashcounter<KeyType>::add(const KeyType& key) {
	int idx;//这里万一有重复值，这里跟find有关，因为如果find到了，就把key节点的值value赋值给了idx
	if (!hash->find(key, idx)) {
		idx = counterindex++;
		hash->insert(key, idx);
	}
	return ++counter[idx];
}

//元素删除：计数器数值-1
template<typename KeyType>
int Hashcounter<KeyType>::sub(const KeyType& key) {
	int idx;
	if (hash->find(key, idx)) {
		return --counter[idx];
	}
	return 0;
}

template<typename KeyType>
int Hashcounter<KeyType>::get(const KeyType& key) {
	int idx;
	if (hash->find(key, idx)) {//hash是指针不是结构体，调用函数得用箭头
		return counter[idx];
	}
	return 0;
}

//测试
int main() {
	Hashcounter<long long> hc;
	hc.add(14);
	hc.add(14);
	hc.add(14);
	hc.add(14);
	hc.add(14);
	hc.sub(14);
	cout << hc.get(14) << endl;
    return 0;
}

/*测试用例
	HashTable<int, char> h(10000);
	h.insert(1, 'a');
	h.insert(2, 'b');
	h.insert(3, 'c');
	h.insert(41012012, 'd');

	char val;
	if (!h.find(43, val)) {
		cout << "43 not found!" << endl;
	}
	if (h.find(41012012, val)) {
		cout << "41012012 found, value is " << val << endl;
	}*/