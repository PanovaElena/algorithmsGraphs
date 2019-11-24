#pragma once
#include <vector>
#include <algorithm>

template <class T>  // T is enumerable type
class UnionFind {

protected:

    // returns if there is not element in divided set
    const T defaultValue;

public:

    UnionFind(T defaultValue) : defaultValue(defaultValue) {}

    // make new set {x}
    virtual void make(const T& x) = 0;

    // find set with x and return name(x)
    virtual T find(const T& x) = 0;

    // unite set1 and set2, x = name(set1), y = name(set2)
    virtual void unite(const T& x, const T& y) = 0;

    T getDefaultValue() const {
        return defaultValue;
    }

};


template <class T>
class UnionFindByArray : public UnionFind<T> {

protected:

    std::vector<T> data;

public:

    UnionFindByArray(size_t n) :
        UnionFind(n), data(n, defaultValue) {}

    void make(const T& x) override {
        data[x] = x;
    }

    T find(const T& x) override {
        return data[x];
    }

    void unite(const T& x, const T& y) override {
        T z = std::min(x, y);
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == x || data[i] == y) {
                data[i] = z;
            }
        }
    }

};


template <class T>
class UnionFindByRanks : public UnionFindByArray<T> {

protected:

    // rank = (height of subtree) + 1
    std::vector<size_t> rank;

public:

    UnionFindByRanks(size_t n) : UnionFindByArray(n),
        rank(n, 0) {}

    // O(1)
    void make(const T& x) override {
        data[x] = x;
        rank[x] = 1;
    }

    // O(log(n))
    T find(const T& x) override {
        if (data[x] == defaultValue)
            return defaultValue;

        T y = x;
        while (y != data[y]) {
            y = data[y];
        }

        return y;
    }

    // O(1)
    void unite(const T& x, const T& y) override {
        if (rank[x] > rank[y]) {
            data[y] = x;
        }
        else if (rank[x] < rank[y]) {
            data[x] = y;
        }
        else if (rank[x] == rank[y]) {
            data[y] = x;
            rank[x]++;
        }
    }

};


template <class T>
class UnionFindByRanksWithPathCompressing : public UnionFindByRanks<T> {

public:

    UnionFindByRanksWithPathCompressing(size_t n) : UnionFindByRanks(n) {}

    // O(superlog(n))
    T find(const T& x) override {
        if (data[x] == defaultValue)
            return defaultValue;

        if (x != data[x]) {
            data[x] = find(data[x]);
        }

        return data[x];
    }

};