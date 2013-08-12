/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2013 Peter Caspers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib liense.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file onefactorcmsswaptionengine.hpp
    \brief cms swaption engine for one factor interest rate models
*/

#ifndef quantlib_pricers_gaussian1d_cmsswaption_hpp
#define quantlib_pricers_gaussian1d_cmsswaption_hpp

#include <ql/experimental/models/cmsswaption.hpp>
#include <ql/pricingengines/genericmodelengine.hpp>

#include <ql/experimental/models/gaussian1dmodel.hpp>

namespace QuantLib {

    //! One factor model cms swaption engine
    /*! \ingroup swaptionengines

		All float coupons with start date greater or equal to the respective option expiry and all structured 
        coupons with fixing date greater or equal to the respective option expiry
		are considered to be part of the exercise into right.

		// FIXME relevant floating coupons may have been fixed on or before today, this may cause problems below

	*/

    class Gaussian1dCmsSwaptionEngine
        : public GenericModelEngine<Gaussian1dModel,
                                    CmsSwaption::arguments,
                                    CmsSwaption::results > {
      public:
        Gaussian1dCmsSwaptionEngine(const boost::shared_ptr<Gaussian1dModel>& model,
                                        const int integrationPoints=64,
                                        const Real stddevs=7.0,
                                        const bool extrapolatePayoff=true,
                                        const bool flatPayoffExtrapolation=false,
                                        const Handle<YieldTermStructure>& discountCurve = Handle<YieldTermStructure>()) :
            GenericModelEngine<Gaussian1dModel, CmsSwaption::arguments, CmsSwaption::results>(model),
            integrationPoints_(integrationPoints) , stddevs_(stddevs), 
            extrapolatePayoff_(extrapolatePayoff), flatPayoffExtrapolation_(flatPayoffExtrapolation), 
            model_(model), discountCurve_(discountCurve) {
             
            if(!discountCurve_.empty())
                registerWith(discountCurve_);

        }

        void calculate() const;
      
	private:
		const int integrationPoints_;
		const Real stddevs_;
		const bool extrapolatePayoff_, flatPayoffExtrapolation_;
		const boost::shared_ptr<Gaussian1dModel> model_;
        const Handle<YieldTermStructure> discountCurve_;
    };

}


#endif

