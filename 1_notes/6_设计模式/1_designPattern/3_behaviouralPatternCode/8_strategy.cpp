
#include <iostream>
#include <memory>
#include <vector>

// 策略接口
class SortStrategy {
  public:
    virtual ~SortStrategy() = default;
    virtual std::vector<int> sort(const std::vector<int>& dataset) const = 0;
};

// 冒泡排序策略
class BubbleSortStrategy : public SortStrategy {
  public:
    std::vector<int> sort(const std::vector<int>& dataset) const override {
        std::cout << "使用冒泡排序" << std::endl;
        // 实现冒泡排序算法
        std::vector<int> sorted = dataset;
        for (size_t i = 0; i < sorted.size(); ++i) {
            for (size_t j = 0; j < sorted.size() - i - 1; ++j) {
                if (sorted[j] > sorted[j + 1]) {
                    std::swap(sorted[j], sorted[j + 1]);
                }
            }
        }
        return sorted;
    }
};

// 快速排序策略
class QuickSortStrategy : public SortStrategy {
  public:
    std::vector<int> sort(const std::vector<int>& dataset) const override {
        std::cout << "使用快速排序" << std::endl;
        // 实现快速排序算法
        std::vector<int> sorted = dataset;
        quickSort(sorted, 0, sorted.size() - 1);
        return sorted;
    }

  private:
    void quickSort(std::vector<int>& arr, int low, int high) const {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    int partition(std::vector<int>& arr, int low, int high) const {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
};

// 客户端类
class Sorter {
  public:
    Sorter(std::shared_ptr<SortStrategy> sorterSmall,
           std::shared_ptr<SortStrategy> sorterBig)
        : sorterSmall_(sorterSmall), sorterBig_(sorterBig) {}

    std::vector<int> sort(const std::vector<int>& dataset) const {
        if (dataset.size() > 5) {
            return sorterBig_->sort(dataset);
        } else {
            return sorterSmall_->sort(dataset);
        }
    }

  private:
    std::shared_ptr<SortStrategy> sorterSmall_;
    std::shared_ptr<SortStrategy> sorterBig_;
};

int main() {
    std::vector<int> smallDataset = {1, 3, 4, 2};
    std::vector<int> bigDataset = {10, 7, 8, 9, 1, 5, 3, 6, 2, 4};

    auto sorter =
        std::make_shared<Sorter>(std::make_shared<BubbleSortStrategy>(),
                                 std::make_shared<QuickSortStrategy>());

    auto sortedSmall = sorter->sort(smallDataset);  // 输出: 使用冒泡排序
    for (int num : sortedSmall) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    auto sortedBig = sorter->sort(bigDataset);  // 输出: 使用快速排序
    for (int num : sortedBig) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
