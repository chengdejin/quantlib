
/* 
Copyright (C) 2000 Ferdinando Ametrano, Luigi Ballabio, Adolfo Benin, Marco Marchioro
See the file LICENSE.TXT for information on usage and distribution
Contact ferdinando@ametrano.net if LICENSE.TXT was not distributed with this file
*/

/*! \file daycounter.h
	\brief Abstract day counter class
*/

/*! \namespace QuantLib::DayCounters
	\brief Concrete implementations of the DayCounter interface
*/

#ifndef quantlib_day_counter_h
#define quantlib_day_counter_h

#include "qldefines.h"
#include "date.h"
#include "handle.h"

namespace QuantLib {

	//! Abstract day counter class
	/*! This class is purely abstract and defines the interface of concrete
		day counter classes which will be derived from this one.
		
		It provides methods for determining the length of a time period according
		to a number of market conventions, both as a number of days and as a year fraction.
	*/
	class DayCounter {
	  public:
		//! Returns the name of the day counter.
		/*!	\warning This method is used for output and comparison between day counters.
			It is <b>not</b> meant to be used for writing switch-on-type code.
		*/
		virtual std::string name() const = 0;
		//! Returns the number of days between two dates.
		virtual int dayCount(const Date&, const Date&) const = 0;
		//! Returns the period between two dates as a fraction of year.
		virtual Time yearFraction(const Date&, const Date&, 
		  const Date& refPeriodStart = Date(), const Date& refPeriodEnd = Date()) const = 0;
	};
	
	// comparison based on name	
	QL_DECLARE_TEMPLATE_SPECIALIZATION(
	bool operator==(const Handle<DayCounter>&, const Handle<DayCounter>&))
	QL_DECLARE_TEMPLATE_SPECIALIZATION(
	bool operator!=(const Handle<DayCounter>&, const Handle<DayCounter>&))
	
	
	// inline definitions

	/*! \defgroup daycountercomparisons Comparisons between day counters */
	
	/*! \ingroup daycountercomparisons
		\relates DayCounter
	*/
	QL_TEMPLATE_SPECIALIZATION
	inline bool operator==(const Handle<DayCounter>& h1, const Handle<DayCounter>& h2) {
		return (h1->name() == h2->name());
	}
	
	/*! \ingroup daycountercomparisons
		\relates DayCounter
	*/
	QL_TEMPLATE_SPECIALIZATION
	inline bool operator!=(const Handle<DayCounter>& h1, const Handle<DayCounter>& h2) {
		return (h1->name() != h2->name());
	}

}


#endif
