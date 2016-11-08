/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @file   TypeParam.h
/// @author Baudouin Raoult
/// @author Tiago Quintino
/// @date   April 2016

#ifndef metkit_TypeParam_H
#define metkit_TypeParam_H

#include "metkit/types/Type.h"

namespace metkit {

//----------------------------------------------------------------------------------------------------------------------

class TypeParam : public Type {

public: // methods

    TypeParam(const std::string &name, const eckit::Value& settings);

    virtual ~TypeParam();

    virtual void expand(std::vector<std::string>& values) const;

protected:
    virtual bool expand(std::vector<std::string>& values, bool fail) const;

private: // methods

    virtual void print( std::ostream &out ) const;
    virtual void reset();

};

//----------------------------------------------------------------------------------------------------------------------

} // namespace metkit

#endif
