#ifndef __SMART_PTR_H__
#define __SMART_PTR_H__

namespace smart_ptr {

class ref_count
{
public:
    ref_count() : m_strong_ref_count(1), m_weak_ref_count(0)
    {
    }

    ~ref_count()
    {
    }

    // increment use count
    int inc_ref()
    {
        return ++m_strong_ref_count;
    }

    // increment weak reference count
    int inc_weak_ref()
    {
        return ++m_weak_ref_count;
    }

    // decrement use count
    int dec_ref()
    {
        int nRs = 0;
        if (m_strong_ref_count > 0) {
            nRs = --m_strong_ref_count;
        }
        return nRs;
    }

    // decrement weak reference count
    int dec_weak_ref()
    {
        int nRs = 0;
        if (m_weak_ref_count > 0) {
            nRs = --m_weak_ref_count;
        }
        return nRs;
    }

    // return use count
    int get_ref_count() const
    {
        return m_strong_ref_count;
    }

    // return true if _Uses == 0
    bool expired() const
    {
        return (get_ref_count() == 0);
    }

    int get_weak_ref_count() const
    {
        return m_weak_ref_count;
    }

private:
    int m_strong_ref_count;
    int m_weak_ref_count;
};

#if defined(WIN32) || defined(_WIN32)
template <class T> class _NoAddRefReleaseOnComPtr : public T {
private:
    virtual unsigned long __stdcall AddRef(void) = 0;
    virtual unsigned long __stdcall Release(void) = 0;
};
#endif  // defined(WIN32) || defined(_WIN32)

// base class for strong_ptr and weak_ptr
template<class T, bool is_strong, typename mem_mgr>
class base_ptr
{
public:
    explicit base_ptr(T *p=0) : m_counter(0), m_ptr(p)
    {
        if (m_ptr) {
            if (is_strong) {
                // allocate a new ref_count
                m_counter = new ref_count;
            }
        }
    }

    base_ptr(const base_ptr& rhs) : m_counter(0), m_ptr(0)
    {
        acquire(rhs);
    }

    template<class Q, bool b, typename mem_mgr2>
    base_ptr(const base_ptr<Q, b, mem_mgr2> &rhs) : m_counter(0), m_ptr(0)
    {
        acquire(rhs);
    }

    virtual ~base_ptr()
    {
        release();
    }

    operator T*()   const throw()   { return m_ptr; }
    T& operator*()  const throw()   { return *m_ptr; }
#if defined(WIN32) || defined(_WIN32)
    _NoAddRefReleaseOnComPtr<T>* operator->() const throw() { return (_NoAddRefReleaseOnComPtr<T>*)m_ptr; }
#else
    T* operator->() const throw()   { return m_ptr; }
#endif  // defined(WIN32) || defined(_WIN32)
    T* get()        const throw()   { return m_ptr; }

    bool unique() const throw()
    { return (m_counter ? (1 == m_counter->get_ref_count()) : true); }

    void reset(T *p=0)
    {
        base_ptr<T, is_strong, mem_mgr> ptr(p);
        reset(ptr);
    }

    template <class Q, bool b, typename mem_mgr2>
    void reset(const base_ptr<Q, b, mem_mgr2> &rhs)
    {
        if ((void *)this != (void *)&rhs) {
            release();
            acquire(rhs);
        }
    }

    int use_count(void) const
    {
        int nRs = 0;
        if (m_counter) {
            nRs = m_counter->get_ref_count();
        }
        return nRs;
    }

    // swap pointers
    template <class Q, bool b, typename mem_mgr2>
    void swap(base_ptr<Q, b, mem_mgr2> & rhs)
    {
        private_swap(m_counter, rhs.m_counter);
        private_swap(m_ptr, rhs.m_ptr);
    }

    base_ptr& operator=(const base_ptr &rhs)
    {
        reset(rhs);
        return *this;
    }

    template <class Q, bool b, typename mem_mgr2>
    base_ptr& operator=(const base_ptr<Q, b, mem_mgr2> &rhs)
    {
        reset(rhs);
        return *this;
    }

protected:
    ref_count *m_counter;
    T * m_ptr;

    template <typename TP1, typename TP2>
    static void private_swap(TP1 &obj1, TP2 &obj2)
    {
        TP1 tmp = obj1;
        obj1 = static_cast<TP1>(obj2);
        obj2 = static_cast<TP2>(tmp);
    }

    template <class Q, bool b, typename mem_mgr2>
    void acquire(const base_ptr<Q, b, mem_mgr2> & rhs) throw()
    {
        if (rhs.m_counter && rhs.m_counter->get_ref_count()) {
            m_counter = rhs.m_counter;
            if (is_strong) {
                m_counter->inc_ref();
            } else {
                m_counter->inc_weak_ref();
            }
            m_ptr = static_cast<T*>(rhs.m_ptr);
        }
    }

    // decrement the count, delete if it is 0
    void release(void)
    {
        if (m_counter) {
            if (is_strong) {
                if (0 == m_counter->dec_ref()) {
                    mem_mgr::deallocate(m_ptr);
                    m_ptr = 0;
                }
            } else {
                m_counter->dec_weak_ref();
            }
            if (0 == m_counter->get_ref_count() && 0==m_counter->get_weak_ref_count()) {
                delete m_counter;
            }
            m_counter = 0;
        }
        if (m_ptr) {
            m_ptr = 0;
        }
    }

    template<class Q, bool b, typename mem_mgr2> friend class base_ptr;
};

template<class T, bool bx, class Q, bool by, typename mem_mgr1, typename mem_mgr2>
bool operator<(const base_ptr<T, bx, mem_mgr1> &lhs, const base_ptr<Q, by, mem_mgr2> &rhs)
{
    // test if left pointer < right pointer
    return lhs.get() < rhs.get();
}

template <class T, typename mem_mgr> class weak_ptr;

template<typename T>
class std_mem_mgr {
public:
    static void deallocate(T *p) { delete p; }
    static T * allocate(void) { return new T(); }
    template<typename A1> static T * allocate(A1 const &a1) { return new T(a1); }
    template<typename A1, typename A2> static T * allocate(A1 const &a1, A2 const &a2) { return new T(a1, a2); }
    template<typename A1, typename A2, typename A3> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3) { return new T(a1, a2, a3); }
    template<typename A1, typename A2, typename A3, typename A4> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4) { return new T(a1, a2, a3, a4); }
    template<typename A1, typename A2, typename A3, typename A4, typename A5> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5) { return new T(a1, a2, a3, a4, a5); }
    template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5, A6 const &a6) { return new T(a1, a2, a3, a4, a5, a6); }
};

template <class T, typename mem_mgr=std_mem_mgr<T> >
class strong_ptr : public base_ptr<T, true, mem_mgr>
{
    typedef base_ptr<T, true, mem_mgr> baseClass;
public:
    explicit strong_ptr(T* p = 0) : baseClass(p)
    {
    }

    strong_ptr(const strong_ptr& rhs) : baseClass(rhs)
    {
    }

    template<class Q, typename mem_mgr2>
    strong_ptr(const strong_ptr<Q, mem_mgr2> &rhs) : baseClass(rhs)
    {
    }

    // construct strong_ptr object that owns resource *rhs
    template<class Q, typename mem_mgr2>
    explicit strong_ptr(const weak_ptr<Q, mem_mgr2> &rhs) : baseClass(rhs)
    {
    }

    ~strong_ptr()
    {
    }

    strong_ptr& operator=(const strong_ptr &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }

    template <class Q, typename mem_mgr2>
    strong_ptr& operator=(const strong_ptr<Q, mem_mgr2> &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }

    template <class Q, typename mem_mgr2>
    strong_ptr& operator=(const weak_ptr<Q, mem_mgr2> &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }
};


template <class T, typename mem_mgr=std_mem_mgr<T> >
class weak_ptr : public base_ptr<T, false, mem_mgr>
{
    typedef base_ptr<T, false, mem_mgr> baseClass;
public:
    // construct empty weak_ptr object
    weak_ptr()
    {
    }

    // construct weak_ptr object for resource owned by rhs
    template<class Q, typename mem_mgr2>
    weak_ptr(const strong_ptr<Q, mem_mgr2> &rhs) : baseClass(rhs)
    {
    }

    // construct weak_ptr object for resource pointed to by rhs
    weak_ptr(const weak_ptr &rhs) : baseClass(rhs)
    {
    }

    // construct weak_ptr object for resource pointed to by rhs
    template<class Q, typename mem_mgr2>
    weak_ptr(const weak_ptr<Q, mem_mgr2> &rhs) : baseClass(rhs)
    {
    }

    ~weak_ptr()
    {
    }

    weak_ptr& operator=(const weak_ptr &rhs)
    {
        baseClass::operator =(rhs);
        return *this;
    }

    template <class Q, typename mem_mgr2>
    weak_ptr& operator=(const weak_ptr<Q, mem_mgr2> &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }

    template <class Q, typename mem_mgr2>
    weak_ptr& operator=(const strong_ptr<Q, mem_mgr2> &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }

    // return true if resource no longer exists
    bool expired() const
    {
        return baseClass::m_counter ? baseClass::m_counter->expired() : true;
    }

    // convert to strong_ptr
    strong_ptr<T, mem_mgr> lock() const
    {
        return strong_ptr<T, mem_mgr>(*this);
    }

private:
    operator T*()   const throw();
    T& operator*()  const throw();
    T* operator->() const throw();
    T* get()        const throw();
};


//////////////////////////////////////////////////////////////////////////
//
//   function make_strong_ptr group
//

template <typename T, typename mem_mgr=std_mem_mgr<T> >
class make_strong_ptr
{
public:
    typedef strong_ptr<T, mem_mgr> pointer_type;

    static pointer_type generate(void)
    {
        return pointer_type ( mem_mgr::allocate() );
    }

    template <typename A1>
    static pointer_type generate(A1 const &a1)
    {
        return pointer_type ( mem_mgr::allocate(a1) );
    }

    template <typename A1, typename A2>
    static pointer_type generate(A1 const &a1, A2 const &a2)
    {
        return pointer_type ( mem_mgr::allocate(a1, a2) );
    }

    template <typename A1, typename A2, typename A3>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3)
    {
        return pointer_type ( mem_mgr::allocate(a1, a2, a3) );
    }

    template <typename A1, typename A2, typename A3, typename A4>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4)
    {
        return pointer_type ( mem_mgr::allocate(a1, a2, a3, a4) );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5)
    {
        return pointer_type ( mem_mgr::allocate(a1, a2, a3, a4, a5) );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5, A6 const &a6)
    {
        return pointer_type ( mem_mgr::allocate(a1, a2, a3, a4, a5, a6) );
    }
};

//////////////////////////////////////////////////////////////////////////
// COM pointer support
//

template<typename T>
class com_mem_mgr {
public:
    static void deallocate(T *p) { p->Release(); }
    static T * allocate(T *p) { p->AddRef(); return p; }  // we must hold the AddRef-ed pointer
};

template <typename T>
strong_ptr<T, com_mem_mgr<T> > make_com_strong_ptr(const T *rawPtr) {
    return make_strong_ptr<T, com_mem_mgr<T> >::template generate<T*>(const_cast<T * &>(rawPtr));
}


//////////////////////////////////////////////////////////////////////////
// auto-released array support
//

template<typename T>
class array_mem_mgr {
public:
    static void deallocate(T *p) { delete []p; }
    static T * allocate(int n) { return new T[n]; }
};

template <class T, typename mem_mgr=array_mem_mgr<T> >
class strong_array : public base_ptr<T, true, mem_mgr>
{
    typedef base_ptr<T, true, mem_mgr> baseClass;
public:
    explicit strong_array(T* p = 0) : baseClass(p)
    {
    }

    strong_array(const strong_array& rhs) : baseClass(rhs)
    {
    }

    template<class Q>
    strong_array(const strong_array<Q, mem_mgr> &rhs) : baseClass(rhs)
    {
    }

    ~strong_array()
    {
    }

    const T & operator[](int i) const
    {
        return baseClass::get()[i];
    }

    T & operator[](int i)
    {
        return baseClass::get()[i];
    }

    strong_array& operator=(const strong_array &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }

    template <class Q>
    strong_array& operator=(const strong_array<Q, mem_mgr> &rhs)
    {
        baseClass::operator = (rhs);
        return *this;
    }
private:
    T& operator*()  const throw();
    T* operator->() const throw();
};


//////////////////////////////////////////////////////////////////////////
// define macros

#ifndef EMPTY_NAME_SPACE
#define EMPTY_NAME_SPACE
#endif  // EMPTY_NAME_SPACE

// defining COM smart pointer type
#ifndef DEFINE_COM_STRONG_PTR
#define DEFINE_COM_STRONG_PTR(NAME_SPACE_T, TYPE) \
    typedef smart_ptr::strong_ptr<NAME_SPACE_T::TYPE, smart_ptr::com_mem_mgr<NAME_SPACE_T::TYPE> > TYPE##ComPtr;
#endif  // DEFINE_COM_STRONG_PTR

// defining standard smart pointer type
#ifndef DEFINE_STD_STRONG_PTR
#define DEFINE_STD_STRONG_PTR(NAME_SPACE_T, TYPE) \
    typedef smart_ptr::strong_ptr<NAME_SPACE_T::TYPE, smart_ptr::std_mem_mgr<NAME_SPACE_T::TYPE> > TYPE##StdPtr;
#endif  // DEFINE_STD_STRONG_PTR

// defining array style smart pointer type
#ifndef DEFINE_ARR_STRONG_PTR
#define DEFINE_ARR_STRONG_PTR(NAME_SPACE_T, TYPE) \
    typedef smart_ptr::strong_ptr<NAME_SPACE_T::TYPE, smart_ptr::array_mem_mgr<NAME_SPACE_T::TYPE> > TYPE##ArrPtr;
#endif  // DEFINE_ARR_STRONG_PTR


}; // namespace smart_ptr


#endif // __SMART_PTR_H__
