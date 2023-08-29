#pragma once

#include <algorithm>
#include <utility>

template <typename It>
class IteratorRange {
public:
    IteratorRange(std::pair<It, It> pair)
            : first_(pair.first)
            , last_(pair.second) {
    }

    IteratorRange(It first_, It last_)
        : first_(first_)
        , last_(last_) {
    }

    It begin() const {
        return first_;
    }

    It end() const {
        return last_;
    }

    size_t size() const {
        return last_ - first_;
    }

private:
    It first_, last_;
};

template <typename Container>
auto Head(Container& c, int top) {
    return IteratorRange(std::begin(c), std::begin(c) + std::min<size_t>(std::max(top, 0), c.size()));
}