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

#ifndef metkit_data_Message_H
#define metkit_data_Message_H

#include <iosfwd>
#include <vector>


namespace eckit {
class DataHandle;
class Offset;
class PathName;
};  // namespace eckit

namespace metkit {

namespace mars {
class MarsRequest;
}

namespace data {

class MessageContent;

//----------------------------------------------------------------------------------------------------------------------

class MetadataGatherer {
public:
    virtual ~MetadataGatherer();
    virtual void setValue(const std::string& key, const std::string& value) = 0;
    virtual void setValue(const std::string& key, long value) = 0;
    virtual void setValue(const std::string& key, double value) = 0;
};

//----------------------------------------------------------------------------------------------------------------------

class Message {
public:
    Message();

    explicit Message(MessageContent*);

    Message(const Message&);

    ~Message();

    Message& operator=(const Message&);

    operator bool() const;

    void write(eckit::DataHandle&) const;

    size_t length() const;
    eckit::Offset offset() const;
    const void* data() const;

    std::string getString(const std::string& key) const;
    long getLong(const std::string& key) const;
    double getDouble(const std::string& key) const;
    void getDoubleArray(const std::string& key, std::vector<double>&) const;


    void getMetadata(MetadataGatherer&) const;


    eckit::DataHandle* readHandle() const;

    mars::MarsRequest request() const;

private:
    mutable MessageContent* content_;

    void print(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream& s, const Message& p) {
        p.print(s);
        return s;
    }
};

//----------------------------------------------------------------------------------------------------------------------

template<class T>
class StringSetter : public MetadataGatherer {
    T& object_;

    virtual void setValue(const std::string& key, const std::string& value) override {
        object_.setValue(key, value);
    }

    virtual void setValue(const std::string& key, long value)   override {
    }

    virtual void setValue(const std::string& key, double value)  override  {
    }

public:
    StringSetter(T& object): object_(object) {}
};

template<class T>
class TypedSetter : public MetadataGatherer {
    T& object_;

    virtual void setValue(const std::string& key, const std::string& value) override {
        object_.setValue(key, value);
    }

    virtual void setValue(const std::string& key, long value)   override  {
        object_.setValue(key, value);
    }

    virtual void setValue(const std::string& key, double value)  override  {
        object_.setValue(key, value);
    }

public:
    TypedSetter(T& object): object_(object) {}
};
//----------------------------------------------------------------------------------------------------------------------


}  // namespace data
}  // namespace metkit

#endif
