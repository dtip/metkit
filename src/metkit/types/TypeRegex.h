/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @file   TypeRegex.h
/// @author Baudouin Raoult
/// @author Tiago Quintino
/// @date   April 2016

#ifndef metkit_TypeRegex_H
#define metkit_TypeRegex_H

#include "metkit/types/Type.h"
#include "eckit/utils/Regex.h"

namespace metkit {

//----------------------------------------------------------------------------------------------------------------------

class TypeRegex : public Type {

public: // methods

    TypeRegex(const std::string &name, const eckit::Value& settings);

    virtual ~TypeRegex();


private: // methods

    virtual void print( std::ostream &out ) const;
    virtual bool expand( std::string &value) const;

    std::vector<eckit::Regex> regex_;
    bool uppercase_;

};

//----------------------------------------------------------------------------------------------------------------------

} // namespace metkit

#endif
