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

#ifndef _JTOBEY_DATE_HH
#define _JTOBEY_DATE_HH

#include "perlcall.hh"

namespace JTobey_PerlCall
{

  class Date : public Scalar
  {
  public:
    Date () : Scalar (Scalar ("JTobey::Date") .call_method ("today")) {}
    Date (const Scalar& s) : Scalar (s) {}
    Date (int y, int m =1, int d =1) : Scalar
    (Scalar ("JTobey::Date")
     .call_method ("from_ymd", List () << y << m << d))
    {}
    string strftime (const string& format) const
    { return call_method ("strftime", List () << format); }
    bool operator== (const Date& d1) const
    { return call_method ("equals", List () << d1); }
    bool operator< (const Date& d1) const
    { return call_method ("is_before", List () << d1); }
    bool operator> (const Date& d1) const
    { return call_method ("is_after", List () << d1); }
    bool operator<= (const Date& d1) const
    { return call_method ("is_not_after", List () << d1); }
    bool operator>= (const Date& d1) const
    { return call_method ("is_not_before", List () << d1); }
    bool operator!= (const Date& d1) const
    { return ! (*this == d1); }
    int operator- (const Date& d1)
    { return call_method ("minus", List () << d1); }
    Date operator+ (long delta)
    { return call_method ("plus", List () << delta); }
    Date operator- (long delta)
    { return call_method ("minus", List () << delta); }
    int get_year  () const { return call_method ("year"); }
    int get_month () const { return call_method ("month_number"); }
    int get_day   () const { return call_method ("day_of_month"); }
  };
  extern inline ostream& operator<< (ostream& os, const Date& d)
  { return os << d.strftime ("%Y-%m-%d"); }

  class TimeDate : public Scalar
  {
  public:
    TimeDate () : Scalar (Scalar ("JTobey::TimeDate") .call_method ("now")) {}
    TimeDate (const Scalar& s) : Scalar (s) {}
    TimeDate (int year, int month =1, int day =1,
	      int hour =0, int minute =0, int second =0) : Scalar
    (Scalar ("JTobey::TimeDate")
     .call_method ("from_ymdhms", List () << year << month << day
		   << hour << minute << second))
    {}
    string strftime (const string& format) const
    { return call_method ("strftime", List () << format); }
  };
  extern inline ostream& operator << (ostream& os, const TimeDate& d)
  { return os << d.strftime ("%Y-%m-%d %H:%M:%S"); }

}

#endif // _JTOBEY_DATE_HH
