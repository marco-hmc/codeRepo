``` C++
float data[1024];

template <typename T> T GetValue(int i)
{
    return static_cast<T>(data[i]);
}

float a = GetValue(0);	// 出错了！
int b = GetValue(1);	// 也出错了！
```

为什么会出错呢？你仔细想了想，原来编译器是没办法去根据返回值推断类型的。函数调用的时候，返回值被谁接受还不知道呢。如下修改后，就一切正常了：

``` C++
float a = GetValue<float>(0);
int b = GetValue<int>(1);
```
