#include "PmergeMe.hpp"

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(void) {
    //
}

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const PmergeMe<T, Container> &src) {
    *this = src;
}

template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::~PmergeMe(void) {

}

template<typename T, template <typename, typename> class Container>
PmergeMe<T, Container> &PmergeMe<T, Container>::operator=(const PmergeMe<T, Container> &src) {
    if (this != &src) {
        *this = src;
    }
    return *this;
}

template <typename T>
bool reserve(T &container, typename T::size_type size) {
    (void)container;
    (void)size;
    return false;
}

template <typename T, template <typename, typename> class Container>
Container<std::pair<T, T>, std::allocator<T> > merge(Container<std::pair<T, T>, std::allocator<T> > left, Container<std::pair<T, T>, std::allocator <T> > right)
{
    Container<std::pair<T, T>, std::allocator<T> > pairs>;
    reserve(pairs, left.size() + right.size());

    while (left.size() && right.size()) {
        if (left[0].first < right[0].first) {
            pairs.push_back(left[0]);
            left.erase(left.begin()); //<----- to pop the first element (front)
        } else {
            pairs.push_back(right[0]);
            right.erase(right.begin()); //<----- to pop the first element (front)
        }
    }

    while (left.size()) {
        pairs.push_back(left[0]);
        left.erase(left.begin()); //<----- to pop the first element (front)
    }

    while (right.size()) {
        pairs.push_back(right[0]);
        right.erase(right.begin()); //<----- to pop the first element (front)
    }
    return pairs;
}

