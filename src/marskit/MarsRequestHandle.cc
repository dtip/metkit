/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File MarsRequestHandle.cc
// Baudouin Raoult - (c) ECMWF Feb 12

#include "marskit/MarsRequestHandle.h"
#include "eckit/parser/StringTools.h"
#include "eckit/types/Types.h"

using namespace eckit;

namespace marskit {

MarsRequestHandle::MarsRequestHandle(const Request request, BaseProtocol* protocol)
: request_(StringTools::lower(request->text())[0] == 'r' ? "retrieve" : "archive"),
  protocol_(protocol)
{
    ASSERT(protocol);
    //request->showGraph(string("MarsRequestHandle: request: ") + request->str());
    for (Request r(request->rest()); r; r = r->rest())
    {
        std::string key (r->text());
        std::vector<std::string> vs;

        ASSERT(r->value() && r->value()->tag() == "_list");

        for (Request v (r->value()); v; v = v->rest())
            vs.push_back(v->value()->text());

        // FIXME: lookup failure for the overloaded operator from Types.h:
        //   std::ostream& operator<<(std::ostream& s,const std::vector<T>& v)
        // Log::debug() << "MarsRequestHandle: " << key <<" = " << vs << std::endl;

        request_.setValues(key, vs);
    }
}

MarsRequestHandle::MarsRequestHandle(const MarsRequest& request, BaseProtocol* protocol)
: request_(request),
  protocol_(protocol)
{
    ASSERT(protocol);
}

MarsRequestHandle::~MarsRequestHandle() {}

Length MarsRequestHandle::openForRead()
{
    ASSERT(StringTools::lower(request_.name()) == "retrieve");
    return protocol_->retrieve(request_);
}

void MarsRequestHandle::openForWrite(const Length& size)
{
    Log::debug() << "openForWrite: request_.name()=" << request_.name() << std::endl;

    ASSERT(StringTools::lower(request_.name()) == "archive");
    protocol_->archive(request_, size);
}

void MarsRequestHandle::openForAppend(const Length&)
{
    NOTIMP;
}

long MarsRequestHandle::read(void* buffer, long len)
{
    return protocol_->read(buffer, len);
}

long MarsRequestHandle::write(const void* buffer, long len)
{
    return protocol_->write(buffer, len);
}

void MarsRequestHandle::close()
{
    protocol_->cleanup();
}

void MarsRequestHandle::print(std::ostream& s) const
{
    s << "MarsRequestHandle["<< *protocol_ << "," << request_ << "]";
}

}
