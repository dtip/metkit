/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Baudouin Raoult
/// @date   Jun 2020

#ifndef metkit_BUFRDecoder_h
#define metkit_BUFRDecoder_h

#include "eckit/message/Decoder.h"


namespace metkit {
namespace codes {

//----------------------------------------------------------------------------------------------------------------------

class BUFRDecoder : public eckit::message::Decoder {

public: // methods

    static bool typeBySubtype(long subtype, long& type);

private: // methods

    virtual bool match(const eckit::message::Message&) const override;
    virtual void print(std::ostream&) const override;
    virtual void getMetadata(const eckit::message::Message& msg,
                             eckit::message::MetadataGatherer&) const override;

};

//----------------------------------------------------------------------------------------------------------------------

} // namespace codes
} // namespace metkit

#endif
