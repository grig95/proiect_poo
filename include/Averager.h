#ifndef OOP_AVERAGER_H
#define OOP_AVERAGER_H


template <typename T>  class Averager {
private:
    T sum;
    unsigned int count=0;
public:
    Averager();
    Averager(Averager<T> const& avg);
    Averager<T>& operator=(Averager<T> const& avg);
    ~Averager();

    void clear();
    void add(T const&  t);
    T getAverage();
};

#endif //OOP_AVERAGER_H
