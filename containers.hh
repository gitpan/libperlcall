/* 
   Copyright (C) 2000 by John Tobey,
   jtobey@john-edwin-tobey.org.  All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
   MA 02111-1307  USA
*/

#ifndef _JTOBEY_CONTAINERS_HH
#define _JTOBEY_CONTAINERS_HH

// XXX should be <jtobey/perlcall.hh>
#include "perlcall.hh"

namespace JTobey_PerlCall
{

  template <class S> class Typed_Array;

  template <>
  class Typed_Array<Scalar> : public Arrayref
  {
  public:
    Typed_Array<Scalar> () {}
    Typed_Array<Scalar> (const Typed_Array<Scalar>& a) : Arrayref (a) {}
    Typed_Array<Scalar> (const Scalar& s) : Arrayref (s) {}

    typedef const Scalar* const_iterator;
    const_iterator begin () const;
    const_iterator end () const;
    void push_back (const Scalar& o);
    Typed_Array<Scalar> deep_copy () const;
  };

  template <class S>
  class Typed_Array : public Typed_Array<Scalar>
  {
  public:
    Typed_Array () {}
    Typed_Array (const Typed_Array& a) : Typed_Array<Scalar> (a) {}
    Typed_Array (const Scalar& s)
      : Typed_Array<Scalar> (s) {}  // XXX could check type

    typedef const S* const_iterator;
    inline const_iterator begin () const;
    inline const_iterator end () const;
    inline void push_back (const S& o);
    inline S& at (size_t index);
    inline const S& at (size_t index) const;
    inline S& operator[] (size_t index) { return at (index); }
    inline const S& operator[] (size_t index) const { return at (index); }
    inline Typed_Array<S> deep_copy () const;
  };

  template<class S>
  inline Typed_Array<S>::const_iterator
  Typed_Array<S>::begin () const
  {
    return (const_iterator) Typed_Array<Scalar>::begin ();
  }

  template<class S>
  inline Typed_Array<S>::const_iterator
  Typed_Array<S>::end () const
  {
    return (const_iterator) Typed_Array<Scalar>::end ();
  }

  template<class S>
  inline void
  Typed_Array<S>::push_back (const S& o)
  {
    Typed_Array<Scalar>::push_back (o);
  }

  template<class S>
  inline S&
  Typed_Array<S>::at (size_t index)
  {
    return (S&) Typed_Array<Scalar>::at (index);
  }

  template<class S>
  inline const S&
  Typed_Array<S>::at (size_t index) const
  {
    return (const S&) Typed_Array<Scalar>::at (index);
  }

  template<class S>
  inline Typed_Array<S>
  Typed_Array<S>::deep_copy () const
  {
    return Typed_Array<Scalar>::deep_copy ();
  }

}

#endif // _JTOBEY_CONTAINERS_HH
