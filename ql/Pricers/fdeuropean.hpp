
/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email ferdinando@ametrano.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file fdeuropean.hpp
    \brief Example of European option calculated using finite differences
*/

// $Id$

#ifndef quantlib_pricers_finite_difference_european_option_h
#define quantlib_pricers_finite_difference_european_option_h

#include <ql/Pricers/fdbsmoption.hpp>
#include <ql/FiniteDifferences/fdtypedefs.hpp>

namespace QuantLib {

    namespace Pricers {

        //! Example of European option calculated using finite differences
        class FdEuropean : public FdBsmOption {
          public:
            FdEuropean(Option::Type type,
                       double underlying,
                       double strike,
                       Spread dividendYield,
                       Rate riskFreeRate,
                       Time residualTime,
                       double volatility,
                       Size timeSteps = 200,
                       Size gridPoints = 800);
                   Array getPrices() const;
            Handle<SingleAssetOption> clone() const{
                return Handle<SingleAssetOption>(
                    new FdEuropean(*this));
            }
          protected:
            void calculate() const;
          private:
            Size timeSteps_;
            mutable Array euroPrices_;
        };

        // inline definitions

        inline Array  FdEuropean::getPrices() const{
            value();
            return euroPrices_;
        }

    }

}

#endif
