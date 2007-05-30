/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2007 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file indonesia.hpp
    \brief Indonesian calendars
*/

#ifndef quantlib_indonesia_calendar_hpp
#define quantlib_indonesia_calendar_hpp

#include <ql/time/calendar.hpp>

namespace QuantLib {

    //! %Indonesian calendars
    /*! Holidays for the Jakarta stock exchange
        (data from <http://www.jsx.co.id/trading.asp?cmd=menu3>):
        <ul>
        <li>Saturdays</li>
        <li>Sundays</li>
        <li>Good Friday</li>
        <li>New Year's Day, January 1st</li>
        <li>Ascension of Jesus Christ</li>
        <li>Independence Day, August 17th</li>
        <li>Christmas, December 25th</li>
        </ul>

        Other holidays for which no rule is given
        (data available for 2005-2007 only:)
        <ul>
        <li>Idul Adha</li>
        <li>Ied Adha</li>
        <li>Imlek</li>
        <li>Moslem's New Year Day</li>
        <li>Nyepi (Saka's New Year)</li>
        <li>Birthday of Prophet Muhammad SAW</li>
        <li>Waisak</li>
        <li>Ascension of Prophet Muhammad SAW</li>
        <li>Idul Fitri</li>
        <li>Ied Fitri</li>
        <li>Other national leaves</li>
        </ul>
        \ingroup calendars
    */
    class Indonesia : public Calendar {
      private:
        class BejImpl : public Calendar::WesternImpl {
          public:
            std::string name() const { return "Jakarta stock exchange"; }
            bool isBusinessDay(const Date&) const;
        };
      public:
        enum Market { BEJ,  //!< Jakarta stock exchange
                      JSX   //!< Jakarta stock exchange
        };
        Indonesia(Market m = BEJ);
    };

}


#endif
