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

#include "containers.hh"

namespace JTobey_PerlCall
{

  Typed_Array<Scalar>::const_iterator
  Typed_Array<Scalar>::begin () const
  {
    if (size ())
      return & at (0);
    return (const_iterator) 0;
  }

  Typed_Array<Scalar>::const_iterator
  Typed_Array<Scalar>::end () const
  {
    size_t sz = size ();
    if (sz)
      return sz + & at (0);
    return (const_iterator) 0;
  }

  void
  Typed_Array<Scalar>::push_back (const Scalar& o)
  {
    push (o);
  }

  Typed_Array<Scalar>
  Typed_Array<Scalar>::deep_copy () const
  {
    Typed_Array<Scalar> new_ary;
    size_t sz = size ();
    for (size_t i = 0; i < sz; i++)
      new_ary .push_back (at (i));
    return new_ary;
  }

}
