#include <iostream>
#include <vector>

// 抽象基类 Filter
class Filter {
public:
    virtual std::vector<int> process(const std::vector<int>& input) = 0;
};

// 具体过滤器类 FilterA
class FilterA : public Filter {
public:
    std::vector<int> process(const std::vector<int>& input) override {
        std::vector<int> output;
        for (int num : input) {
            // 过滤器A的处理逻辑
            output.push_back(num * 2);
        }
        return output;
    }
};

// 具体过滤器类 FilterB
class FilterB : public Filter {
public:
    std::vector<int> process(const std::vector<int>& input) override {
        std::vector<int> output;
        for (int num : input) {
            // 过滤器B的处理逻辑
            output.push_back(num + 1);
        }
        return output;
    }
};

// Pipeline 类
class Pipeline {
private:
    std::vector<Filter*> filters;

public:
    void addFilter(Filter* filter) {
        filters.push_back(filter);
    }

    std::vector<int> process(const std::vector<int>& input) {
        std::vector<int> output = input;
        for (Filter* filter : filters) {
            output = filter->process(output);
        }
        return output;
    }
};

int main() {
    // 创建过滤器实例
    FilterA filterA;
    FilterB filterB;

    // 创建管道实例并添加过滤器
    Pipeline pipeline;
    pipeline.addFilter(&filterA);
    pipeline.addFilter(&filterB);

    // 输入数据
    std::vector<int> input = { 1, 2, 3, 4, 5 };

    // 处理数据
    std::vector<int> output = pipeline.process(input);

    // 输出结果
    for (int num : output) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
