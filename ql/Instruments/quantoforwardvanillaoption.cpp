
/*
 Copyright (C) 2003 Ferdinando Ametrano

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/Instruments/quantoforwardvanillaoption.hpp>

namespace QuantLib {

    QuantoForwardVanillaOption::QuantoForwardVanillaOption(
        const RelinkableHandle<TermStructure>& foreignRiskFreeTS,
        const RelinkableHandle<BlackVolTermStructure>& exchRateVolTS,
        const RelinkableHandle<Quote>& correlation,
        double moneyness,
        Date resetDate,
        const boost::shared_ptr<BlackScholesStochasticProcess>& stochProc,
        const boost::shared_ptr<StrikedTypePayoff>& payoff,
        const boost::shared_ptr<Exercise>& exercise,
        const boost::shared_ptr<PricingEngine>& engine)
    : QuantoVanillaOption(foreignRiskFreeTS, exchRateVolTS, correlation,
                          stochProc, payoff, exercise, engine),
      moneyness_(moneyness), resetDate_(resetDate) {
        QL_REQUIRE(engine, "null engine or wrong engine type");
    }

    void QuantoForwardVanillaOption::setupArguments(Arguments* args)
        const {
        VanillaOption::setupArguments(args);
        QuantoForwardVanillaOption::arguments* arguments =
            dynamic_cast<QuantoForwardVanillaOption::arguments*>(args);
        QL_REQUIRE(arguments != 0,
                   "pricing engine does not supply needed arguments");

        arguments->foreignRiskFreeTS = foreignRiskFreeTS_;
        arguments->exchRateVolTS = exchRateVolTS_;
        QL_REQUIRE(correlation_, "null correlation given");
        arguments->correlation = correlation_->value();

        arguments->moneyness = moneyness_;
        arguments->resetDate = resetDate_;

    }

}

