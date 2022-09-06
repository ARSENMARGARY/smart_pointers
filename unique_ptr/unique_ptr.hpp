#ifndef SMART_UNIQUE_PTR
#define SMART_UNIQUE_PTR

template <typename T>
class Uniq_ptr
{
public:
    Uniq_ptr(T*);
    Uniq_ptr(const Uniq_ptr&) = delete;
    Uniq_ptr(Uniq_ptr&&);
    Uniq_ptr& operator= (const Uniq_ptr&) = delete;
    Uniq_ptr& operator= (Uniq_ptr&&);
    ~Uniq_ptr();
public:
    T& operator*();
    T* operator->();
public:
    T* release();
private:
    T* m_ptr = nullptr;
};

#endif