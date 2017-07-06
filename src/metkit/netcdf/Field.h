/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// Baudouin Raoult - ECMWF Jan 2015

#ifndef metkit_netcdf_Field
#define metkit_netcdf_Field


#include <string>
#include <vector>

namespace metkit {
namespace netcdf {

class Variable;

class Field  {
public:

    Field(const Variable &);
    virtual ~Field();

    // -- Methods

    // Same as GRIB

    virtual std::string gridType() const = 0;
    virtual long paramId() const = 0;
    virtual double north() const = 0;
    virtual double south() const = 0;
    virtual double west() const = 0;
    virtual double east() const = 0;
    virtual double westEastIncrement() const = 0;
    virtual double southNorthIncrement() const = 0;
    virtual std::vector<size_t> dimensions() const = 0;
    virtual void values(std::vector<double>&) const = 0;

protected:

    // -- Members
    const Variable& owner_;

private:

    Field(const Field &);
    Field &operator=(const Field &);

    // From Endowed

    // - Methods

    virtual void print(std::ostream &s) const = 0;

    // -- Friends
    friend std::ostream &operator<<(std::ostream &s, const Field &v) {
        v.print(s);
        return s;
    }
};

}
}
#endif
