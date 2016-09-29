/*
 * (C) Copyright 1996-2015 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef grib_GribAccessor_H
#define grib_GribAccessor_H

#include "eckit/log/Log.h"
#include "eckit/exception/Exceptions.h"
#include "grib/GribHandle.h"

namespace grib {

//----------------------------------------------------------------------------------------------------------------------

class GribAccessorBase {

protected:

    void grib_get_value(const GribHandle& h, const std::string& name, double& x, bool quiet = false) const;

    void grib_get_value(const GribHandle& h, const std::string& name,  unsigned long& x, bool quiet = false) const;

    void grib_get_value(const GribHandle& h, const std::string& name,  long& x, bool quiet = false) const;

    void grib_get_value(const GribHandle& h, const std::string& name,  bool& x, bool quiet = false) const;

    void grib_get_value(const GribHandle& h, const std::string& name,  std::string& x, bool quiet = false) const;

    void grib_get_value(const GribHandle& h, const std::string& name,  std::vector<long>& x, bool quiet = false) const;

    void grib_get_value(const GribHandle& h, const std::string& name,  std::vector<double>& x, bool quiet = false) const;

};

//----------------------------------------------------------------------------------------------------------------------

template<class T>
class GribAccessor : private GribAccessorBase {

private: // members

	std::string name_;

public: // methods

	GribAccessor(const std::string& name): name_(name) {}

	T value(const GribHandle& h) const
	{
		T value;
		grib_get_value(h, name_, value);
		return value;
	}

	T value(const GribHandle& h,T def) const
	{
		T value = def;
		grib_get_value(h, name_, value, true);
		return value;
	}

	T operator()(const GribHandle& h) const
	{
		return value(h);
	}

	T operator()(const GribHandle& h, T def) const
	{
		return value(h, def);
	}

};

//----------------------------------------------------------------------------------------------------------------------

} // namespace grib

#endif
