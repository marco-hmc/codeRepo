#include <iostream>
#include <vector>
#include <algorithm> //sort函数、交并补函数
#include <iterator> //求交并补使用到的迭代器
using namespace std;

//打印容器vector
void print_vector(vector<int> v){
    if(v.size()>0){
        cout<<"{";  
        for(int i=0;i<int(v.size());i++){  
            cout<<v[i]<<",";  
        }  
        cout<<"\b}";  
    }
    else{
        cout<<"{}";
    }
}

//容器vector中元素的去重
vector<int> unique_element_in_vector(vector<int> v){
    vector<int>::iterator vector_iterator;
    sort(v.begin(),v.end());
    vector_iterator = unique(v.begin(),v.end());
    if(vector_iterator != v.end()){
        v.erase(vector_iterator,v.end());
    }
    return v;
}

//两个vector求交集
vector<int> vectors_intersection(vector<int> v1,vector<int> v2){
    vector<int> v;
    sort(v1.begin(),v1.end());   
    sort(v2.begin(),v2.end());   
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));//求交集 
    return v;
}

//两个vector求并集
vector<int> vectors_set_union(vector<int> v1,vector<int> v2){
    vector<int> v;
    sort(v1.begin(),v1.end());   
    sort(v2.begin(),v2.end());   
    set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));//求交集 
    return v;
}

//判断vector的某一元素是否存在
bool is_element_in_vector(vector<int> v,int element){
    vector<int>::iterator it;
    it=find(v.begin(),v.end(),element);
    if (it!=v.end()){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    vector<int> v1,v2,v;
    v1.push_back(22);v1.push_back(22);v1.push_back(23);v2.push_back(23);v2.push_back(24);
    cout<<"v1是否存在1这个元素？"<<is_element_in_vector(v1,1)<<endl;
    cout<<"对v1去重：";
    v1=unique_element_in_vector(v1);
    print_vector(v1);
    cout<<endl;
    cout<<"求v1与v2的交集：";
    v=vectors_intersection(v1,v2);
    print_vector(v);
    cout<<endl;
    cout<<"求v1与v2的并集：";
    v=vectors_set_union(v1,v2);
    print_vector(v);
    return 0;
}
