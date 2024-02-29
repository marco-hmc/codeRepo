#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
实现string常见的操作：
	（1）构造、赋值:
	（2）基本操作：size(), empty(),  push_back(), pop_back(), insert(), erase(), clear(), swap();
*/

void myVectorTest()
{
    // 1. 初始化
	vector<int> myVec = { 1, 3, 5, 7, 9 };
	vector<int> myVec1 = { 4, 6, 8 };
	cout << "the length of myVec：" << myVec.size() << endl;
	myVec.push_back(0);                                                                 //在尾部添加字符
	cout << "after pushing, myVec is: "  << endl;
	for (auto tmp : myVec)
	{
		cout << tmp << ' ';
	}
	/*
	insert()版本：
		（1）insert(p, t)     //在迭代器p之前创建一个值为t，返回指向新添加的元素的迭代器
		（2）insert(p, b, e)  //将迭代器[b, e）指定的元素插入到p所指位置，返回第一个插入元素的迭代器
		（3）insert(p, il)    //将列表中的元素插入，返回第一个插入元素的迭代器
		                      //关于迭代器确定范围都是左闭右开！！！！
	*/
	auto ret = myVec.insert(myVec.begin() + 1, 2);                                //插入单个元素，返回该元素迭代器
	cout << "after inserting , myVec is : " << endl;
	for (auto tmp : myVec)
	{
		cout << tmp << ' ';
	}
	cout << "返回的迭代器值为：" << *ret << endl;

	auto ret1 = myVec.insert(myVec.begin() + 1, myVec1.begin(), myVec1.end());     //插入系列元素，返回第一个插入元素迭代器
	cout << "after inserting , myVec is : " << endl;
	for (auto tmp : myVec)
	{
		cout << tmp << ' ';
	}
	cout << "返回的迭代器值为：" << *ret1 << endl;
		/*
	insert()版本：
		（1）erase(p)         //删除迭代器p所指元素，返回下一个元素的迭代器
		（2）erase(b, e)      //删除迭代器[b, e) 范围内的元素；
		                      //关于迭代器确定范围都是左闭右开！！！！
	*/
	auto ret2 = myVec.erase(myVec.begin() + 1);                                 //删除单个迭代器指向的元素，
	cout << "after earsing , myVec is : " << endl;
	for (auto tmp : myVec)
	{
		cout << tmp << ' ';
	}
	cout << "返回的迭代器值为：" << *ret2 << endl;

	auto ret3 = myVec.erase(myVec.begin() + 1, myVec.begin() + 4);              //返回迭代器对指向的范围内的元素
	cout << "after earsing , myVec is : " << endl;
	for (auto tmp : myVec)
	{
		cout << tmp << ' ';
	}
	cout << "返回的迭代器值为：" << *ret3 << endl;

	swap(myVec, myVec1);                                                   //交换两个容器的值，其实实质上并不交换
	cout << '\n';
}

int main() {
    myVectorTest();
    cout << "done" << endl;
}