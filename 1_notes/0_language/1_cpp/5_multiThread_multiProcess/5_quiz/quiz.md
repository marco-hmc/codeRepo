double check locking

```c++
Foo& getFoo() {
    static std::unique_ptr<Foo> foo = nullptr;
    static std::mutex mtx;

    if (!foo) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!foo) {
            // foo = std::make_unique<Foo>();
            foo.reset(new Foo());
        }
    }
    return *foo;
}

```