#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Range {
public:
    struct RangeValue {
        double value;
        bool bounded;

        bool operator<(const RangeValue& other) const {
            if (value == other.value) {
                if (bounded == other.bounded) {
                    return false;
                } else {
                    return bounded < other.bounded;
                }
            } else {
                return value < other.value;
            }
        }

        bool operator<=(const RangeValue& other) const {
            return *this < other || *this == other;
        }

        bool operator>(const RangeValue& other) const {
            if (value == other.value) {
                if (bounded == other.bounded) {
                    return false;
                } else {
                    return bounded > other.bounded;
                }
            } else {
                return value > other.value;
            }
        }
        bool operator>=(const RangeValue& other) const {
            return *this > other || *this == other;
        }

        bool operator==(const RangeValue& other) const {
            if (value == other.value) {
                if (bounded == other.bounded) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    };

    RangeValue min;
    RangeValue max;
    Range() = default;
    Range(double minVal, bool minBounded, double maxVal, bool maxBounded) : min{ minVal,minBounded }, max{ maxVal, maxBounded } {};

    bool isValid() const {
        if (min < max) return true;
        if (min == max && min.bounded) return true;
        return false;
    }

    void intersectWith(const Range& other) {
        auto isOverlap = [](const Range& a, const Range& b) {
            if (a.max < b.min || b.max < a.min) {
                return false;
            } else {
                return true;
            }
            };
        if (!isValid() || !other.isValid() || !isOverlap(*this, other)) {
            min = { 0, false };
            max = { 0, false };
            return;
        }

        if (min < other.min) {
            min = other.min;
        }
        if (max > other.max) {
            max = other.max;
        }
        if (min > max) {
            std::swap(min, max);
        }
    }
};

class RangeSet {
public:
    RangeSet() = default;
    RangeSet(double min, bool minBounded, double max, bool maxBounded) {
        Range r{ min, minBounded, max, maxBounded };
        if (r.isValid()) {
            ranges.push_back(r);
        }
    }

    void unionWith(const RangeSet& other) {
        for (const auto& range : other.ranges) {
            ranges.push_back(range);
        }
    }


    void mergeRanges() {
        std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
            return a.min < b.min;
        });

        std::vector<Range> mergedRanges;
        Range currentRange = ranges[0];

        for (int i = 1; i < ranges.size(); i++) {
            if (currentRange.max >= ranges[i].min) {
                currentRange.max = std::max(currentRange.max, ranges[i].max);
            } else {
                mergedRanges.push_back(currentRange);
                currentRange = ranges[i];
            }
        }

        mergedRanges.push_back(currentRange);
        ranges = mergedRanges;
    }

    void intersectWith(const RangeSet& other) {
        std::vector<Range> result;
        const Range otherIntersection = other.getIntersection();
        for (auto r : ranges) {
            r.intersectWith(otherIntersection);
            if (r.isValid()) {
                result.push_back(r);
            }
        }
        ranges = result;
    }

    Range getIntersection() const {
        if (ranges.empty()) {
            return Range(0, false, 0, false);
        }
        Range intersection = ranges[0];
        for (int i = 1; i < ranges.size(); i++) {
            intersection.intersectWith(ranges[i]);
        }
        return intersection;
    }

    void print_ranges() {
        for (auto r : ranges) {
            std::cout << r.min.value << " " << r.min.bounded << " " << r.max.value << " " << r.max.bounded << std::endl;
        }
        std::cout << "-----------" << std::endl;
    }

private:
    std::vector<Range> ranges;
};


int main() {
    // RangeSet range({ 1,true, 5,false });
    // range.intersectWith({ 2,true, 4,false });
    // range.print_ranges();

    RangeSet range2({ 1, true, 3,false });
    range2.unionWith({ 2,true, 4,false });
    range2.print_ranges();

    RangeSet range3;
    range3.unionWith({ 6,true, 10,false });
    range3.unionWith({ 1,true, 3, false });
    range3.intersectWith({ 6,true, 7,false });
    range3.print_ranges();
    range3.unionWith({ 1,true, 3, false });
    range3.intersectWith(range2);
    range3.print_ranges();

    RangeSet range4;
    range4.intersectWith({ 1,true, 10,false });
    range4.unionWith({ 6,true, 10,false });
    range4.intersectWith({ 6,true, 7,false });
    range4.print_ranges();

    RangeSet range5;
    range5.unionWith({ 6,true, 10,false });
    range5.print_ranges();
    range5.intersectWith(RangeSet());
    range5.print_ranges();
    range5.unionWith(RangeSet());
    range5.print_ranges();

    return 0;
}
