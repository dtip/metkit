/*
 * (C) Copyright 2017- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Baudouin Raoult
/// @date   Jun 2020



#ifndef metkit_data_MessageContent_H
#define metkit_data_MessageContent_H

#include <iosfwd>
#include <vector>

#include "eckit/memory/Counted.h"
typedef struct grib_handle codes_handle;

namespace eckit {
class DataHandle;
class Offset;
class PathName;
};

namespace metkit {

namespace mars {
class MarsRequest;
}

namespace data {

class MessageContent : public eckit::Counted {

public:

    virtual operator bool() const ;

    virtual void write(eckit::DataHandle&) const;

    virtual size_t length() const ;

    virtual std::string getString(const std::string& key) const;

    virtual long getLong(const std::string& key) const;

    virtual double getDouble(const std::string& key) const ;

    virtual void getDoubleArray(const std::string& key, std::vector<double>&) const;

    virtual eckit::DataHandle* readHandle() const;

    virtual eckit::Offset offset() const;

    virtual const void* data() const;

    virtual const codes_handle* codesHandle() const;

private:

    virtual void print(std::ostream &) const = 0;

    friend std::ostream &operator<<(std::ostream &s, const MessageContent &p) {
        p.print(s);
        return s;
    }
};


}  // namespace data
}  // namespace metkit


#endif
