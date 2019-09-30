#ifndef CUSTOMCOLLECTION_H
#define CUSTOMCOLLECTION_H

#include <list>
#include <algorithm>
using namespace std;

template <class T> class CustomIterator;

template <class T> class CustomCollection
{
    public:
        CustomCollection();
        ~CustomCollection();
        void add(T* val);
        CustomIterator<T> newIterator();
        void clear();

        friend CustomIterator<T>::CustomIterator(CustomCollection<T>* val);
        friend bool CustomIterator<T>::hasNext();
        friend void CustomIterator<T>::remove();
    protected:

    private:

        list<T*> vec;
};

template <class T> class CustomIterator
{
    public:
        CustomIterator(CustomCollection<T>* val);
        ~CustomIterator();
        void remove();
        T* next();
        bool hasNext();


    protected:

    private:
        CustomCollection<T>* collection;
        typename list<T*>::iterator it;
        bool begin;
};

/**  CustomCollection  **/
template <class T>
CustomCollection<T>::CustomCollection()
{
    //ctor
}

template <class T>
CustomCollection<T>::~CustomCollection()
{
    //dtor
}

template <class T>
void CustomCollection<T>::add(T* val)
{
    vec.push_back(val);
}

template <class T>
CustomIterator<T> CustomCollection<T>::newIterator()
{
    return CustomIterator<T>(this);
}

template <class T>
void CustomCollection<T>::clear()
{
    for_each(vec.begin(),vec.end(),[](T* n){delete n;});
    vec.clear();
}

/**  CustomIterator **/

template <class T>
CustomIterator<T>::CustomIterator(CustomCollection<T>* val):collection(val)
{
    //ctor
    it=collection->vec.begin();
    begin = true;
}

template <class T>
CustomIterator<T>::~CustomIterator()
{
    //dtor
}

template <class T>
T* CustomIterator<T>::next()
{
    if(begin){
        begin = false;
    }else{
        it++;
    }

    return *it;
}

template <class T>
bool CustomIterator<T>::hasNext()
{
    if(collection->vec.empty()) return false;
    if(it==collection->vec.end())return false;

    if(begin){
        return !collection->vec.empty();
    }

    if(std::next(it) != collection->vec.end()){
        return true;
    }else{
        return false;
    }

}

template <class T>
void CustomIterator<T>::remove()
{
    delete *it;
    collection->vec.erase(it);
    if(it != collection->vec.begin()){
        it--;
    }
    if(it == collection->vec.begin()){
        begin = true;
    }
}

#endif // CUSTOMCOLLECTION_H
