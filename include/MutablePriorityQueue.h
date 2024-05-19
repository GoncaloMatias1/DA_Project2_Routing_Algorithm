/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

/**
 * @class MutablePriorityQueue
 * @brief A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * @tparam T The type of elements stored in the priority queue. The class T must have:
 * - an accessible field int queueIndex;
 * - operator< defined.
 */
template <class T>
class MutablePriorityQueue {
    std::vector<T *> H; /**< The heap vector storing the elements. */

    /**
     * @brief Heapifies the element at index i upwards.
     * @param i The index of the element to heapify.
     */
    void heapifyUp(unsigned i);

    /**
     * @brief Heapifies the element at index i downwards.
     * @param i The index of the element to heapify.
     */
    void heapifyDown(unsigned i);

    /**
     * @brief Sets the element at index i to x.
     * @param i The index where the element is set.
     * @param x The element to set.
     */
    inline void set(unsigned i, T * x);

public:
    /**
     * @brief Constructs an empty MutablePriorityQueue.
     */
    MutablePriorityQueue();

    /**
     * @brief Inserts an element into the priority queue.
     * @param x The element to insert.
     */
    void insert(T * x);

    /**
     * @brief Extracts the minimum element from the priority queue.
     * @return The minimum element.
     */
    T * extractMin();

    /**
     * @brief Decreases the key of the given element.
     * @param x The element whose key is to be decreased.
     */
    void decreaseKey(T * x);

    /**
     * @brief Checks if the priority queue is empty.
     * @return True if the priority queue is empty, false otherwise.
     */
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */
