/*
实现string常见的操作：
（1）构造、赋值:
（2）基本操作：size(), empty(),  push_back(), pop_back(), insert(), erase(), clear();
（3）string特有操作：substr(), append(), replace(), find()系列函数, compare()
*/
#include <iostream>
#include <string>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

void myStringTest()
{
	string str1 = "hello world";
    // 1. 属性
    int size = str1.size();

    // 2. 添加
    str1.push_back('!');  //在尾部添加字符
    str1.append("!!!");                                   //在尾部添加子串
    str1 += "!!";

    // 3. 修改
	auto ret = str1.insert(str1.begin() + 5, '@');       //返回的是指向插入元素的迭代器
	auto ret1 = str1.insert(6, "#");                     //参数为下标的，插入的是字符串，返回的是插入之后str1的引用,记住字符串下标是从0开始的
	auto ret2 = str1.erase(str1.begin() + 5);            //接受迭代器版本的，返回删除元素之后的迭代器
	auto ret3 = str1.erase(5, 1);                       //接受下标参数的，,接受删除长度，返回删除元素之后的引用
	str1.replace(5, 1, "###");                            //(pos, len, str)形式
	str1.replace(str1.begin() + 5, str1.begin() + 7, "aaa");  //(iterator1, iterator2, string)形式

    // 4. 子串
    string str2 = str1.substr(0, 5);                //从0开始，长度为5的子串，若5缺失，则默认到末尾
	
	// 5. 比较
	str1.compare(str2);

	/*
	find系列函数：
	(1) s.find(args)          //查找s中第一次出现的位置,并返回子串在主串中第一个字符的下标
	(2) s.rfind(args)         //查找最后一个...
	(3) s.find_first_of(args) //在s中查找args中任何一个字符的第一次出现的位置，
	(4) s.find_last_of(args)  //在s中查找args中任何一个字符最后一次出现的位置。
	(5) s.find_first_not_of(args)   //在s中查找第一个不在args中的字符
	(6) s.find_last_not_of(args)    //查找最后一个不在args中的字符
	*/
	auto pos = str1.find("hello");
	string numbers("01234556789");
	string name("r2d2");
	auto pos1 = name.find_first_of(numbers);
}

int main(){
    myStringTest();
    cout<<"done"<<endl;
}