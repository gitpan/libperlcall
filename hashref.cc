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

#include "perlcall_int.hh"


namespace JTobey_PerlCall
{

  static inline SV*
  new_hash ()
  {
    dTHX;
    return Perl_newRV_noinc ((SV*) Perl_newHV ());
  }

  Hashref::Hashref () : Scalar (new_hash ()) {}

  static inline SV*
  lookup_hash (const string& name)
  {
    dTHX;
    return Perl_newRV ((SV*) Perl_get_hv (name .c_str (), 1));
  }

  Hashref::Hashref (const string& name) : Scalar (lookup_hash (name)) {}
  Hashref::Hashref (const char* name) : Scalar (lookup_hash (name)) {}

  Scalar
  Hashref::fetch (const Scalar& key) const
  {
    dTHX;

    HE* loc = Perl_hv_fetch_ent ((HV*) SvRV (imp), key.imp, 0, 0);
    if (loc)
      return Perl_newSVsv (HeVAL (loc));
    else
      return &PL_sv_undef;
  }

  Scalar&
  Hashref::store (const Scalar& key, const Scalar& val)
  {
    dTHX;
    return ref (HeVAL (Perl_hv_store_ent ((HV*) SvRV (imp), key.imp,
					  SvREFCNT_inc (val.imp), 0)));
  }

}
