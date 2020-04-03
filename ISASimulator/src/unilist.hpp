#ifndef UNILIST
#define UNILIST

#include <vector>

template <typename T>
class unilist
{
    std::vector<T> list;
public:
    size_t size();
    size_t find(T element);
    bool add(T element);
    bool remove(T element);
};

template <typename T>
size_t unilist<T>::size()
{
    return list.size();
}

template <typename T>
size_t unilist<T>::find(T element)
{
    size_t i;
    for(i = 0; i < list.size(); i++)
        if(list[i] == element) return i;

    return i;
}

template <typename T>
bool unilist<T>::add(T element)
{
    if(find(element) == size())
    {
        list.push_back(element);
        return true;
    } 

    return false;
}

template <typename T>
bool unilist<T>::remove(T element)
{
    size_t i = find(element);

    if(i == size())
        return false;
    else
    {
        list.erase(list.begin()+i);
        return true;
    }
}

#endif