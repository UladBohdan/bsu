#ifndef VECTOREX_H
#define VECTOREX_H

template <class T> class vectorex : public vector<T>
{
public:
    vectorex();
    vectorex(int);
    vectorex(T*, int);
    vectorex(const vector<T>&);
    vectorex(const vectorex<T>&);
    void push_front(T);
    ~vectorex();
};

template <class T> vectorex<T>::vectorex() : vector<T>() { }

template <class T> vectorex<T>::vectorex(int n) : vector<T>(n) { }

template <class T> vectorex<T>::vectorex(T* a, int n) : vector<T>(a,n) { }

template <class T> vectorex<T>::vectorex(const vector<T> &a) : vector<T>(a) { }

template <class T> vectorex<T>::vectorex(const vectorex<T> &a)
{
    this->sz=a.sz;
    T* x = new T[logsz(this->sz)];
    for (int i=0; i<this->sz; i++)
        x[i]=a[i];
    this->start=x;
}

template <class T> void vectorex<T>::push_front(T a)
{
    if (!(this->sz&(this->sz-1)))
    {
        for (int i=this->sz; i>0; i--)
            *(this->start+i)=*(this->start+i-1);
        *(this->start)=a;
        this->sz++;
    }
    else
    {
        T* x = new T[this->sz<<1];
        x[0]=a;
        for (int i=0; i<this->sz; i++)
            x[i+1]=*(this->start+i);
        this->sz++;
        delete[] this->start;
        this->start=x;
    }
}

template <class T> vectorex<T>::~vectorex() { }

#endif // VECTOREX_H
