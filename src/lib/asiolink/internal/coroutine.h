//
// coroutine.h
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef COROUTINE_HPP
#define COROUTINE_HPP


// \brief Coroutine object
//
// A coroutine object maintains the state of a re-enterable routine.  It
// is assignable and copy-constructable, and can be used as a base class
// for a class that uses it, or as a data member.  The copy overhead is
// a single int.
//
// A reenterable function contains a CORO_REENTER (coroutine)  { ... }
// block.  Whenever an asychrnonous operation is initiated within the
// routine, the function is provided as the handler object.  (The simplest
// way to do this is to have the reenterable function be the operator()
// member for the coroutine object itself.)   For example:
// 
//     CORO_YIELD socket->async_read_some(buffer, *this);
//
// The CORO_YIELD keyword updates the current status of the coroutine to
// indicate the line number currently being executed.  The
// async_read_some() call is initiated, with a copy of the updated
// corotutine as its handler object, and the current coroutine exits.  When
// the async_read_some() call finishes, the copied coroutine will be
// called, and will resume processing exactly where the original one left
// off--right after asynchronous call.  This allows asynchronous I/O
// routines to be written with a logical flow, step following step, rather
// than as a linked chain of separate handler functions.
//
// When necessary, a coroutine can fork itself using the CORO_FORK keyword.
// This updates the status of the coroutine and makes a copy.  The copy can
// then be called directly or posted to the ASIO service queue so that both
// coroutines will continue forward, one "parent" and one "child".  The
// is_parent() and is_child() methods indicate which is which.
//
// The CORO_REENTER, CORO_YIELD and CORO_FORK keywords are implemented
// via preprocessor macros.  The CORO_REENTER block is actually a large,
// complex switch statement.  Because of this, inline variable declaration
// is impossible within CORO_REENTER unless it is done in a subsidiary
// scope--and if it is, that scope cannot contain CORO_YIELD or CORO_FORK
// keywords.
//
// Because coroutines are frequently copied, it is best to minimize copy
// overhead by limiting the size of data members in derived classes.
//
// It should be noted that when a coroutine falls out of scope its memory
// is reclaimed, even though it may be scheduled to resume when an
// asynchronous operation completes.  Any shared_ptr<> objects declared in
// the coroutine may be destroyed if their reference count drops to zero,
// in which case the coroutine will have serious problems once it resumes.
// One solution so this is to have the space that will be used by a
// coroutine pre-allocated and stored on a free list; a new coroutine can
// fetch the block of space off a free list, place a shared pointer to it
// on an "in use" list, and carry on.  The reference in the "in use" list
// would prevent the data from being destroyed.
class coroutine
{
public:
  coroutine() : value_(0) {}
  virtual ~coroutine() {}
  bool is_child() const { return value_ < 0; }
  bool is_parent() const { return !is_child(); }
  bool is_complete() const { return value_ == -1; }
  int get_value() const { return value_; }
private:
  friend class coroutine_ref;
  int value_;
};

class coroutine_ref
{
public:
  coroutine_ref(coroutine& c) : value_(c.value_), modified_(false) {}
  coroutine_ref(coroutine* c) : value_(c->value_), modified_(false) {}
  ~coroutine_ref() { if (!modified_) value_ = -1; }
  operator int() const { return value_; }
  int& operator=(int v) { modified_ = true; return value_ = v; }
private:
  void operator=(const coroutine_ref&);
  int& value_;
  bool modified_;
};

#define CORO_REENTER(c) \
  switch (coroutine_ref _coro_value = c) \
    case -1: if (_coro_value) \
    { \
      goto terminate_coroutine; \
      terminate_coroutine: \
      _coro_value = -1; \
      goto bail_out_of_coroutine; \
      bail_out_of_coroutine: \
      break; \
    } \
    else case 0:

#define CORO_YIELD \
  for (_coro_value = __LINE__;;) \
    if (_coro_value == 0) \
    { \
      case __LINE__: ; \
      break; \
    } \
    else \
      switch (_coro_value ? 0 : 1) \
        for (;;) \
          case -1: if (_coro_value) \
            goto terminate_coroutine; \
          else for (;;) \
            case 1: if (_coro_value) \
              goto bail_out_of_coroutine; \
            else case 0:

#define CORO_FORK \
  for (_coro_value = -__LINE__;; _coro_value = __LINE__) \
    if (_coro_value == __LINE__) \
    { \
      case -__LINE__: ; \
      break; \
    } \
    else
#endif // COROUTINE_HPP

