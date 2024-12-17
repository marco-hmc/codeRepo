#include <iostream>
#include <memory>
#include <vector>

class Filter {
  public:
    virtual ~Filter() = default;
    virtual std::vector<int> process(const std::vector<int>& input) = 0;
};

class FilterA : public Filter {
  public:
    std::vector<int> process(const std::vector<int>& input) override {
        std::vector<int> output;
        output.reserve(input.size());
        for (int num : input) {
            output.push_back(num * 2);
        }
        return output;
    }
};

class FilterB : public Filter {
  public:
    std::vector<int> process(const std::vector<int>& input) override {
        std::vector<int> output;
        output.reserve(input.size());
        for (int num : input) {
            output.push_back(num + 1);
        }
        return output;
    }
};

class Pipeline {
  private:
    std::vector<std::unique_ptr<Filter>> filters;

  public:
    void addFilter(std::unique_ptr<Filter> filter) {
        filters.push_back(std::move(filter));
    }

    std::vector<int> process(const std::vector<int>& input) {
        std::vector<int> output = input;
        for (const auto& filter : filters) {
            output = filter->process(output);
        }
        return output;
    }
};

int main() {
    auto filterA = std::make_unique<FilterA>();
    auto filterB = std::make_unique<FilterB>();

    Pipeline pipeline;
    pipeline.addFilter(std::move(filterA));
    pipeline.addFilter(std::move(filterB));

    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> output = pipeline.process(input);

    for (int num : output) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    return 0;
}