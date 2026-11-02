#include<iostream>
using namespace std;

#define eleType int

//模拟单向链表的初始化和增删改查

//单个结点
struct listcode {
    eleType data;
    listcode* next;
    listcode(eleType val) :data(val), next(NULL) {}
};

//单向链表类模板：整条链表
class linkedlist {
private:
    listcode* head;
    int size;
public:
    linkedlist() :head(NULL), size(0) {}//初始化列表，无参
    ~linkedlist();
    void linked_insert(int i, eleType val);
    void linked_delete(int i);
    listcode* linked_find(eleType val);
    listcode* linked_get(int i);
    void linked_update(int i, eleType val);
    void print();
    eleType linked_sum();//新增接口，求和
    void linked_append(eleType val);
    void linked_ascinsert(eleType val);
};

//析构函数
linkedlist::~linkedlist() {
    listcode* curr = head;
    while (curr != NULL) {
        listcode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//结点插入
void linkedlist::linked_insert(int i, eleType val) {
    if (i<0 || i>size) {
        throw std::out_of_range("Invalied position");
    }
    listcode* newcode = new listcode(val);
    if (i == 0) {
        newcode->next = head;
        head = newcode;
    }
    else {
        listcode* curr = head;
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        newcode->next = curr->next;
        curr->next = newcode;
    }
    size++;
};

//结点删除
void linkedlist::linked_delete(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalied position");
    }
    if (i == 0) {
        listcode* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        listcode* curr = head;
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        listcode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }
    size--;
}

//结点元素查找
listcode* linkedlist::linked_find(eleType val) {
    listcode* curr = head;
    while (curr && curr->data != val) {
        curr = curr->next;
    }
    return curr;
}

//获取第i个结点
listcode* linkedlist::linked_get(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalied position");
    }
    listcode* curr = head;
    for (int j = 0; j < i; j++) {
        curr = curr->next;
    }
    return curr;
}

//结点元素修改
void linkedlist::linked_update(int i, eleType val) {
    linked_get(i)->data = val;
}

void linkedlist::print() {
    listcode* curr = head;
    while (curr) {
        cout << curr->data;
        curr = curr->next;
        if (curr) {
            cout << " ";
        }
        else {
            cout << endl;
        }
    }
    cout << endl;
}

//整条链表值求和
eleType linkedlist::linked_sum() {
    eleType ret = 0;
    listcode* curr = head;
    while (curr != NULL) {
        ret += curr->data;
        curr = curr->next;
    }
    return ret;
}

//尾插
void linkedlist::linked_append(eleType val) {
    linked_insert(size, val);
}

//额外的接口，习题：链表有序
void linkedlist::linked_ascinsert(eleType val) {
    //不够严谨，万一是空的链表也要做一个插入操作。
    if (size == 0) {
        linked_insert(size, val);
        return;
    }
    listcode* curr = head;
    for (int i = 0; i < size; i++) {
        if (val <= curr->data) {
            linked_insert(i, val);
            return;
        }
        curr = curr->next;
    }
    linked_insert(size, val);
}

//测试
int main() {
    //斐波那契数列
    linkedlist f;
    f.linked_insert(0, 1);
    f.linked_insert(1, 1);
    f.linked_insert(2, 1);
    for (int i = 3; i < 40; i++) {
        listcode* a = f.linked_get(i - 2);
        listcode* b = f.linked_get(i - 1);
        f.linked_insert(i, a->data + b->data);
    }
    f.print();
    //int n;
    //cin >> n;
    //while (n--) {
    //    int v;
    //    cin >> v;
    //    cout << f.linked_get(v)->data;
    //}
    return 0;
}