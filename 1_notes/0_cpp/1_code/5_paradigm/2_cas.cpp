class MyClass {
public:
    MyClass& operator=(MyClass other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(MyClass& first, MyClass& second) {
        // Swap the members of 'first' and 'second'
        std::swap(first.member, second.member);
        // ...
    }

private:
    // Members...
};