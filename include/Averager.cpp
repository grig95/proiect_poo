#include "Averager.h"

template <typename T> Averager<T>::Averager() : sum() {}

template <typename T> Averager<T>::Averager(Averager<T> const& avg) : sum(avg.sum), count(avg.count) {}

template <typename T> Averager<T>&  Averager<T>::operator=(Averager<T> const& avg) = default;

template <typename T> Averager<T>::~Averager() = default;

template <typename T> void Averager<T>::clear() {
    sum=T();
    count=0;
}

template <typename T> void Averager<T>::add(T const& t) {
    sum+=t;
    count++;
}

template <typename T> T Averager<T>::getAverage() {
    if(count==0)
        return T();
    return sum/count;
}