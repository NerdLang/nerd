#pragma once
#ifdef __AVR__
#include <Arduino.h>
extern void * operator new(size_t size, void * ptr);
namespace nonstd{
  
  template<class T>struct tag{using type=T;};
  template<class Tag>using type_t=typename Tag::type;
  
  using size_t=decltype(sizeof(int));
  
  //move
  
  template<class T>
  T&& move(T&t){return static_cast<T&&>(t);}
  
  //forward
  
  template<class T>
  struct remove_reference:tag<T>{};
  template<class T>
  struct remove_reference<T&>:tag<T>{};
  template<class T>using remove_reference_t=type_t<remove_reference<T>>;
  
  template<class T>
  T&& forward( remove_reference_t<T>& t ) {
  return static_cast<T&&>(t);
  }
  template<class T>
  T&& forward( remove_reference_t<T>&& t ) {
  return static_cast<T&&>(t);
  }
  
  //decay
  
  template<class T>
  struct remove_const:tag<T>{};
  template<class T>
  struct remove_const<T const>:tag<T>{};
  
  template<class T>
  struct remove_volatile:tag<T>{};
  template<class T>
  struct remove_volatile<T volatile>:tag<T>{};
  
  template<class T>
  struct remove_cv:remove_const<type_t<remove_volatile<T>>>{};
  
  
  template<class T>
  struct decay3:remove_cv<T>{};
  template<class R, class...Args>
  struct decay3<R(Args...)>:tag<R(*)(Args...)>{};
  template<class T>
  struct decay2:decay3<T>{};
  template<class T, size_t  N>
  struct decay2<T[N]>:tag<T*>{};
  
  template<class T>
  struct decay:decay2<remove_reference_t<T>>{};
  
  template<class T>
  using decay_t=type_t<decay<T>>;
  
  //is_convertible
  
  template<class T>
  T declval(); // no implementation
  
  template<class T, T t>
  struct integral_constant{
  static constexpr T value=t;
  constexpr integral_constant() {};
  constexpr operator T()const{ return value; }
  constexpr T operator()()const{ return value; }
  };
  template<bool b>
  using bool_t=integral_constant<bool, b>;
  using true_type=bool_t<true>;
  using false_type=bool_t<false>;
  
  template<class...>struct voider:tag<void>{};
  template<class...Ts>using void_t=type_t<voider<Ts...>>;
  
  namespace details {
  template<template<class...>class Z, class, class...Ts>
  struct can_apply:false_type{};
  template<template<class...>class Z, class...Ts>
  struct can_apply<Z, void_t<Z<Ts...>>, Ts...>:true_type{};
  }
  template<template<class...>class Z, class...Ts>
  using can_apply = details::can_apply<Z, void, Ts...>;
  
  namespace details {
  template<class From, class To>
  using try_convert = decltype( To{declval<From>()} );
  }
  template<class From, class To>
  struct is_convertible : can_apply< details::try_convert, From, To > {};
  template<>
  struct is_convertible<void,void>:true_type{};
  
  //enable_if
  
  template<bool, class=void>
  struct enable_if {};
  template<class T>
  struct enable_if<true, T>:tag<T>{};
  template<bool b, class T=void>
  using enable_if_t=type_t<enable_if<b,T>>;
  
  //res_of
  
  namespace details {
  template<class G, class...Args>
  using invoke_t = decltype( declval<G>()(declval<Args>()...) );
  
  template<class Sig,class=void>
  struct res_of {};
  template<class G, class...Args>
  struct res_of<G(Args...), void_t<invoke_t<G, Args...>>>:
  tag<invoke_t<G, Args...>>
  {};
  }
  template<class Sig>
  using res_of = details::res_of<Sig>;
  template<class Sig>
  using res_of_t=type_t<res_of<Sig>>;
  
  //aligned_storage
  
  template<size_t size, size_t align>
  struct alignas(align) aligned_storage_t {
  char buff[size];
  };
  
  //is_same
  
  template<class A, class B>
  struct is_same:false_type{};
  template<class A>
  struct is_same<A,A>:true_type{};
  
  template<class Sig, size_t sz, size_t algn>
  struct small_task;
  
  template<class R, class...Args, size_t sz, size_t algn>
  struct small_task<R(Args...), sz, algn>{
    struct vtable_t {
      void(*mover)(void* src, void* dest);
      void(*destroyer)(void*);
      R(*invoke)(void const* t, Args&&...args);
      template<class T>
      static vtable_t const* get() {
        static const vtable_t table = {
          [](void* src, void*dest) {
            new(dest) T(move(*static_cast<T*>(src)));
          },
          [](void* t){ static_cast<T*>(t)->~T(); },
          [](void const* t, Args&&...args)->R {
            return (*static_cast<T const*>(t))(forward<Args>(args)...);
          }
        };
        return &table;
      }
    };
    vtable_t const* table = nullptr;
    aligned_storage_t<sz, algn> data;
    template<class F,
      class dF=decay_t<F>,
      enable_if_t<!is_same<dF, small_task>{}>* = nullptr,
      enable_if_t<is_convertible< res_of_t<dF&(Args...)>, R >{}>* = nullptr
    >
    small_task( F&& f ):
      table( vtable_t::template get<dF>() )
    {
      static_assert( sizeof(dF) <= sz, "object too large" );
      static_assert( alignof(dF) <= algn, "object too aligned" );
      new(&data) dF(forward<F>(f));
    }
    ~small_task() {
      if (table)
        table->destroyer(&data);
    }
    small_task(const small_task& o):
      table(o.table)
    {
      data = o.data;
    }
    small_task(small_task&& o):
      table(o.table)
    {
      if (table)
        table->mover(&o.data, &data);
    }
    small_task(){}
    small_task& operator=(const small_task& o){
      this->~small_task();
      new(this) small_task( move(o) );
      return *this;
    }
    small_task& operator=(small_task&& o){
      this->~small_task();
      new(this) small_task( move(o) );
      return *this;
    }
    explicit operator bool()const{return table;}
    R operator()(Args...args)const{
      return table->invoke(&data, forward<Args>(args)...);
    }
  };

  template<class R, class...Args, size_t sz, size_t algn>
  inline bool operator==(const small_task<R(Args...), sz, algn>& __f, nullptr_t)
  { return !static_cast<bool>(__f); }

  /// @overload
  template<class R, class...Args, size_t sz, size_t algn>
  inline bool  operator==(nullptr_t, const small_task<R(Args...), sz, algn>& __f)
  { return !static_cast<bool>(__f); }

  template<class R, class...Args, size_t sz, size_t algn>
  inline bool operator!=(const small_task<R(Args...), sz, algn>& __f, nullptr_t)
  { return static_cast<bool>(__f); }

  /// @overload
  template<class R, class...Args, size_t sz, size_t algn>
  inline bool operator!=(nullptr_t, const small_task<R(Args...), sz, algn>& __f)
  { return static_cast<bool>(__f); }
  
  template<class Sig>
  using function = small_task<Sig, sizeof(void*)*4, alignof(void*) >;
}

#endif