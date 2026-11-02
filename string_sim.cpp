//模拟串的初始化和增删改查
#define _CRT_SECURE_NO_WARNINGS//关闭MSVC对scanf/strcpy等函数的安全警告，GCC下无影响
#include<iostream>
#include<cstring>
using namespace std;

class String {
private:
	char* str;//这个手写串的结构是一个一级指针指向的一个数组
	size_t length;
public:
	String();
	String(const char* s);
	~String();
	String(const String& s);
	size_t Getlength();
	char operator[](size_t index)const;
	String& operator=(const String& s);
	bool operator==(const String& s)const;
	bool operator!=(const String& s)const;
	String copy()const;
	String operator+(const String& s)const;
	friend ostream& operator<<(ostream& out, const String& s);

};

//对象无参构造
String::String() {
	length = 0;
	str = new char[1];
	str[0] = '\0';
}

//有参构造
String::String(const char* s) {
	length = strlen(s);
	str = new char[length + 1];
	strcpy(str, s);
}

//析构
String::~String() {
	delete[] str;
}

//拷贝构造
String::String(const String& s) {
	length = s.length;
	str = new char[length + 1];
	strcpy(str, s.str);
}

//获取串长度
size_t String::Getlength() {
	return length;
}

//按索引获取元素
char String::operator[](size_t index)const {
	return str[index];
}

//串赋值
String& String::operator=(const String& s) {//这个成员函数会修改成员变量，所以不需要用const修饰
	if (this != &s) {//这里是做地址判断，所以是s取地址,而不是this解引用，判断是否为同一个对象，对比地址就行
		delete[] str;
		length = s.length;
		str = new char[length + 1];//这里应该开辟length+1个地址，表示字符容量，因为还有个\0
		strcpy(str, s.str);
	}
	return *this;
}

//判断字符串是否相等
bool String::operator==(const String& s)const {
	return strcmp(str, s.str) == 0;//比较两字符串是否相等的函数是strcmp
}

//判断字符串是否不等
bool String::operator!=(const String& s)const {
	return strcmp(str, s.str) != 0;
}

//拷贝
String String::copy()const {//这个是浅拷贝
	String s = *this;//浅拷贝拷贝的是对象，而不是成员变量
	return s;
}

//字符串append
String String::operator+(const String& s)const {
	String results;
	results.length = length + s.length;//this指的是整个对象，解引用可以不写，写了也没关系，成员函数本身就会调用this
	results = new char[length + 1];
	strcpy(results.str, str);
	strcat(results.str, s.str);
	return results;
}

//字符串输出
ostream& operator<<(ostream& out, const String& s) {
	out << s.str;//这里是把s.str这个字符串输入到out里，然后由out返回给ostream，在打印到终端，原理不太清楚，但是要记一下这里
	return out;
}

int main() {
	String s("12345d");
	cout << s + "456" << endl;
	cout << (s == "12345d") << endl;
	cout << (s != "12345d") << endl;
	s = s + "asd";
	String a, b, c;
	a = b = c = s;
	cout << s << endl;
	cout << a << b << c << s << endl;
	String x = s.copy();
	cout << x << endl;
	return 0;
}