#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

template <typename T, template <typename, typename> class Container>
class PmergeMe { 
    public:
        PmergeMe<T, Container>(void);
        PmergeMe<T, Container>(const PmergeMe<T, Container> &src);
        ~PmergeMe<T, Container>(void);
        PmergeMe<T, Container> &operator=(const PmergeMe<T, Container> &src);

        Container<T, std::allocator<T> > sort(const Container<T, std::allocator<T> > &array) const;

};

#include "PmergeMe.tpp"

#endif