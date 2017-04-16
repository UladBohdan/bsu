#ifndef VECTOR_H
#define VECTOR_H

template <class T> class vector
{
protected:
    int sz;
    T* start;
    int logsz(int);
public:
    vector();
    vector(int);
    vector(const T*, int);
    vector(const vector<T> &);
    T* begin();
    T* end();
    void push_back(T);
    void pop_back();
    int size();
    T& operator[](int i);
    vector<T>& operator=(const vector<T>&);
    virtual ~vector();
};

template <class T> vector<T>::vector() : sz(0), start(0) { }

template <class T> vector<T>::vector(int n) : sz(n)
{
    T* x = new T[logsz(n)];
    start=x;
}

template <class T> vector<T>::vector(const T* a, int n) : sz(logsz(n))
{
    T* x = new T[sz];
    for (int i=0; i<n; i++)
        x[i]=a[i];
    start=x;
}

template <class T> vector<T>::vector(const vector<T> &a) : sz(a.sz)
{
    T* x = new T[logsz(sz)];
    for (int i=0; i<sz; i++)
        x[i]=a[i];
    start=x;
}

template <class T> T* vector<T>::begin()
{
    return start;
}

template <class T> T* vector<T>::end()
{
    return (start+sz);
}

template <class T> void vector<T>::push_back(T a)
{
    if (!(sz&(sz-1)))
        *(start+(sz++))=a;
    else
    {
        T* x = new T[sz<<1];
        for (int i=0; i<sz; i++)
            x[i]=*(start+i);
        x[sz]=a;
        sz++;
        delete[] start;
        start=x;
    }
}

template <class T> void vector<T>::pop_back()
{
    sz--;
}

template <class T> int vector<T>::size()
{
    return sz;
}

template <class T> int vector<T>::logsz(int x)
{
    int temp=x-1, ans=0;
    while (temp>0)
    {
        temp>>=1;
        ans++;
    }
    return 1<<ans;
}

template <class T> T& vector<T>::operator[](int i)
{
    return *(start+i);
}

template <class T> vector<T>& vector<T>::operator=(const vector<T> &a)
{
    T* x = new T[logsz(a.sz)];
    sz=a.sz;
    for (int i=0; i<sz; i++)
        x[i]=*(a.start+i);
    start=x;
    return *this;
}

template <class T> vector<T>::~vector()
{
    delete[] start;
}

#endif // VECTOR_H
