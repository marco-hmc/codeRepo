class MyClass:
    def __init__(self, name):
        self.name = name


# 创建一个实例并赋值给变量a
a = MyClass("a")

# 将a赋值给b
b = a

# 通过b修改实例的状态
b.name = "b"

# 打印a的name属性，结果是'b'
print(a.name)
