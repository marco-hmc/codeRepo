#### (28)实现一个队列,并且使它支持多线程,队列有什么应用场景(阿里三面)
```C++
//评测题目: 
class FIFOQueue
{
vector<int> vec(initCap,0);
int start=0,end=0;
condition_variable cv;
mutex m;
bool flag=false;// isFull
  bool enqueue(int v) {
  	unique_lock<mutex></mutex> lk(m);
    while(flag==true) cv.wait(lk);
        end=(end+1)%initCap;
        vec[end]=v;
        cv.notifyall();
        return true;
    }
  }
  int dequeue() {
  unique_lock<mutex></mutex> lk(m);
  	if(start!=end){
    	int val = vec[start];
    	start=(start+1)%initCap;
        flag=false;
    	cv.notifyall();
        return val;
    }else{
    	flag=false;
    	cv.notifyall();
    	return -1;
  	}
  }
}
```