#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>


template <class T, class Priority>
class PriorityQueue {

protected:

    std::vector<Priority> priorities;

    std::vector<size_t> queueIdentifiers;  // array of queue identificators for every element
    std::vector<T> elements;  // array of elements for every queue identificator

public:

    PriorityQueue(size_t n, Priority defaultPriority) : priorities(n), queueIdentifiers(n), elements(n) {
        for (size_t i = 0; i < n; ++i) {
            queueIdentifiers[i] = i;
            elements[i] = i;
            priorities[i] = defaultPriority;
        }
    }

    virtual void decreasePriority(T elem, Priority pr) = 0;

    virtual Priority getPriority(T elem) const = 0;

    virtual std::pair<T, Priority> exactMin() = 0;

    virtual bool isInQueue(T elem) const = 0;

};


template <class T, class Priority>
class PriorityQueueByArray : public PriorityQueue<T, Priority> {

    std::vector<bool> ifInQueue;

public:

    PriorityQueueByArray(size_t n, Priority defaultPriority) : PriorityQueue(n, defaultPriority),
        ifInQueue(n, true) {}

    void decreasePriority(T elem, Priority pr) override {
        priorities[elem] = pr;
    }

    Priority getPriority(T elem) const override {
        return priorities[elem];
    }

    // O(n)
    std::pair<T, Priority> exactMin() override {
        T argmin = 0;
        Priority min = std::numeric_limits<Priority>::max();

        for (size_t i = 0; i < priorities.size(); i++) {  // O(n)
            if (ifInQueue[i] && priorities[i] < min) {
                argmin = i;
                min = priorities[i];
            }
        }

        ifInQueue[argmin] = false;

        return std::pair<T, Priority>(argmin, min);
    }

    bool isInQueue(T elem) const override {
        return ifInQueue[elem];
    }
};


// 2-heap
template <class T, class Priority>
class PriorityQueueByHeap : public PriorityQueue<T, Priority> {

    const int d = 2;

public:

    PriorityQueueByHeap(size_t n, Priority defaultPriority) : PriorityQueue(n, defaultPriority) {}

    // O(log(n))
    void decreasePriority(T elem, Priority pr) override {
        size_t elemIdent = queueIdentifiers[elem];
        priorities[elemIdent] = pr;
        emersion(elemIdent);
    }

    Priority getPriority(T elem) const override {
        size_t elemIdent = queueIdentifiers[elem];
        return priorities[elemIdent];
    }

    // O(log(n))
    std::pair<T, Priority> exactMin() override {
        std::pair<T, Priority> res(elements[0], priorities[0]);

        if (priorities.size() == 0)
            return std::pair<T, Priority>();

        swap(0, priorities.size() - 1);
        priorities.resize(priorities.size() - 1);
        elements.resize(elements.size() - 1);
        diving(0);

        return res;
    }

    bool isInQueue(T elem) const override {
        return queueIdentifiers[elem] < priorities.size();
    }

private:

    size_t getLeftChild(size_t elem) {
        size_t leftChild = elem * d + 1;
        if (leftChild >= priorities.size())
            return priorities.size();
        return leftChild;
    }

    size_t getRightChild(size_t elem) {
        size_t leftChild = getLeftChild(elem);
        if (leftChild == priorities.size())
            return priorities.size();
        if (leftChild + d - 1 >= priorities.size())
            return priorities.size();
        return leftChild + d - 1;
    }

    size_t getMinChild(size_t elem) {
        size_t leftChild = getLeftChild(elem), rightChild = getRightChild(elem);
        if (leftChild == priorities.size())
            return priorities.size();
        if (rightChild == priorities.size())
            return leftChild;
        Priority min = std::min(priorities[leftChild], priorities[rightChild]);
        return min == priorities[leftChild] ? leftChild : rightChild;
    }

    size_t getParent(size_t elem) {
        if (elem == 0)
            return priorities.size();
        return (elem - 1) / d;
    }

    void swap(size_t elem1, size_t elem2) {
        Priority tmpPr = priorities[elem1];
        priorities[elem1] = priorities[elem2];
        priorities[elem2] = tmpPr;

        T tmpEl = elements[elem1];
        elements[elem1] = elements[elem2];
        elements[elem2] = tmpEl;

        size_t tmpId = queueIdentifiers[elements[elem1]];
        queueIdentifiers[elements[elem1]] = queueIdentifiers[elements[elem2]];
        queueIdentifiers[elements[elem2]] = tmpId;
    }

    void diving(size_t elem) {
        size_t j1 = elem, j2 = getMinChild(elem);
        while (j2 != priorities.size() && priorities[j1] > priorities[j2]) {
            swap(j1, j2);
            j1 = j2;
            j2 = getMinChild(j2);
        }
    }

    void emersion(size_t elem) {
        size_t j1 = elem, j2 = getParent(elem);
        while (j2 != priorities.size() && priorities[j1] < priorities[j2]) {
            swap(j1, j2);
            j1 = j2;
            j2 = getParent(j2);
        }
    }




};