/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*

 Copyright (C) 2008 Toyin Akin

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

/*! \file subperiodcoupons.hpp
    \brief averaging coupons
*/

#ifndef quantlib_sub_period_coupons_hpp
#define quantlib_sub_period_coupons_hpp

#include <ql/cashflows/floatingratecoupon.hpp>
#include <ql/time/schedule.hpp>
#include <ql/indexes/iborindex.hpp>
#include <vector>

namespace QuantLib {

    class SubPeriodsCoupon: public FloatingRateCoupon {
      public:
          // The index object passed in has a tenor significantly less than the
          // start/end dates.
          // Thus endDate-startDate may equal 3M
          // The Tenor used within the index object should be 1M for
          // averaging/compounding across three coupons within the
          // coupon period.
          SubPeriodsCoupon(
                const Date& paymentDate,
                Real nominal,
                const boost::shared_ptr<IborIndex>& index,
                const Date& startDate,
                const Date& endDate,
                Natural fixingDays,
                const DayCounter& dayCounter,
                Real gearing,
                Rate couponSpread, // Spread added to the computed
                                   // averaging/compounding rate.
                Rate rateSpread, // Spread to be added onto each
                                 // fixing within the
                                 // averaging/compounding calculation
                const Date& refPeriodStart,
                const Date& refPeriodEnd);

        Spread rateSpread() const { return rateSpread_; }

        Real startTime() const { return startTime_; }
        Real endTime() const { return endTime_; }
        Size observations() const { return observations_; }
        const std::vector<Date>& observationDates() const {
            return observationDates_;
        }
        const std::vector<Real>& observationTimes() const {
            return observationTimes_;
        }

        const boost::shared_ptr<Schedule> observationsSchedule() const {
            return observationsSchedule_;
        }

        Real priceWithoutOptionality(
                       const Handle<YieldTermStructure>& discountCurve) const;
        //! \name Visitability
        //@{
        virtual void accept(AcyclicVisitor&);
        //@}
      private:

        Real startTime_;                               // S
        Real endTime_;                                 // T

        boost::shared_ptr<Schedule> observationsSchedule_;
        std::vector<Date> observationDates_;
        std::vector<Real> observationTimes_;

        Size observations_;
        Rate rateSpread_;
    };


}


#endif
