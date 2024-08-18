Boost C++ Libraries
...one of the most highly regarded and expertly designed C++ library projects in the world.
— Herb Sutter and Andrei Alexandrescu, C++ Coding Standards

Search...
This is the documentation for an old version of Boost. Click here to view this page for the latest version.
PrevUpHomeNext
coroutine

Provides support for implementing stackless coroutines.

class coroutine
Member Functions
Name

Description

coroutine [constructor]

Constructs a coroutine in its initial state.

is_child

Returns true if the coroutine is the child of a fork.

is_complete

Returns true if the coroutine has reached its terminal state.

is_parent

Returns true if the coroutine is the parent of a fork.

The coroutine class may be used to implement stackless coroutines. The class itself is used to store the current state of the coroutine.

Coroutines are copy-constructible and assignable, and the space overhead is a single int. They can be used as a base class:

class session : coroutine
{
  ...
};
or as a data member:

class session
{
  ...
  coroutine coro_;
};
or even bound in as a function argument using lambdas or bind(). The important thing is that as the application maintains a copy of the object for as long as the coroutine must be kept alive.

Pseudo-keywords
A coroutine is used in conjunction with certain "pseudo-keywords", which are implemented as macros. These macros are defined by a header file:

#include <boost/asio/yield.hpp>
and may conversely be undefined as follows:

#include <boost/asio/unyield.hpp>
reenter

The reenter macro is used to define the body of a coroutine. It takes a single argument: a pointer or reference to a coroutine object. For example, if the base class is a coroutine object you may write:

reenter (this)
{
  ... coroutine body ...
}
and if a data member or other variable you can write:

reenter (coro_)
{
  ... coroutine body ...
}
When reenter is executed at runtime, control jumps to the location of the last yield or fork.

The coroutine body may also be a single statement, such as:

reenter (this) for (;;)
{
  ...
}
Limitation: The reenter macro is implemented using a switch. This means that you must take care when using local variables within the coroutine body. The local variable is not allowed in a position where reentering the coroutine could bypass the variable definition.

yield statement

This form of the yield keyword is often used with asynchronous operations:

yield socket_->async_read_some(buffer(*buffer_), *this);
This divides into four logical steps:

yield saves the current state of the coroutine.
The statement initiates the asynchronous operation.
The resume point is defined immediately following the statement.
Control is transferred to the end of the coroutine body.
When the asynchronous operation completes, the function object is invoked and reenter causes control to transfer to the resume point. It is important to remember to carry the coroutine state forward with the asynchronous operation. In the above snippet, the current class is a function object object with a coroutine object as base class or data member.

The statement may also be a compound statement, and this permits us to define local variables with limited scope:

yield
{
  mutable_buffers_1 b = buffer(*buffer_);
  socket_->async_read_some(b, *this);
}
yield return expression ;

This form of yield is often used in generators or coroutine-based parsers. For example, the function object:

struct interleave : coroutine
{
  istream& is1;
  istream& is2;
  char operator()(char c)
  {
    reenter (this) for (;;)
    {
      yield return is1.get();
      yield return is2.get();
    }
  }
};
defines a trivial coroutine that interleaves the characters from two input streams.

This type of yield divides into three logical steps:

yield saves the current state of the coroutine.
The resume point is defined immediately following the semicolon.
The value of the expression is returned from the function.
yield ;

This form of yield is equivalent to the following steps:

yield saves the current state of the coroutine.
The resume point is defined immediately following the semicolon.
Control is transferred to the end of the coroutine body.
This form might be applied when coroutines are used for cooperative threading and scheduling is explicitly managed. For example:

struct task : coroutine
{
  ...
  void operator()()
  {
    reenter (this)
    {
      while (... not finished ...)
      {
        ... do something ...
        yield;
        ... do some more ...
        yield;
      }
    }
  }
  ...
};
...
task t1, t2;
for (;;)
{
  t1();
  t2();
}
yield break ;

The final form of yield is used to explicitly terminate the coroutine. This form is comprised of two steps:

yield sets the coroutine state to indicate termination.
Control is transferred to the end of the coroutine body.
Once terminated, calls to is_complete() return true and the coroutine cannot be reentered.

Note that a coroutine may also be implicitly terminated if the coroutine body is exited without a yield, e.g. by return, throw or by running to the end of the body.

fork statement

The fork pseudo-keyword is used when "forking" a coroutine, i.e. splitting it into two (or more) copies. One use of fork is in a server, where a new coroutine is created to handle each client connection:

reenter (this)
{
  do
  {
    socket_.reset(new tcp::socket(my_context_));
    yield acceptor->async_accept(*socket_, *this);
    fork server(*this)();
  } while (is_parent());
  ... client-specific handling follows ...
}
The logical steps involved in a fork are:

fork saves the current state of the coroutine.
The statement creates a copy of the coroutine and either executes it immediately or schedules it for later execution.
The resume point is defined immediately following the semicolon.
For the "parent", control immediately continues from the next line.
The functions is_parent() and is_child() can be used to differentiate between parent and child. You would use these functions to alter subsequent control flow.

Note that fork doesn't do the actual forking by itself. It is the application's responsibility to create a clone of the coroutine and call it. The clone can be called immediately, as above, or scheduled for delayed execution using something like post.

Alternate macro names
If preferred, an application can use macro names that follow a more typical naming convention, rather than the pseudo-keywords. These are:

BOOST_ASIO_CORO_REENTER instead of reenter
BOOST_ASIO_CORO_YIELD instead of yield
BOOST_ASIO_CORO_FORK instead of fork
Requirements
Header: boost/asio/coroutine.hpp

Convenience header: boost/asio.hpp

Copyright © 2003-2022 Christopher M. Kohlhoff
Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

PrevUpHomeNext