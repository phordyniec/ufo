/*
 * (C) Copyright 2018-2019 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

#ifndef UFO_OBSBOUNDSCHECK_H_
#define UFO_OBSBOUNDSCHECK_H_

#include <ostream>
#include <string>

#include "eckit/config/LocalConfiguration.h"
#include "ioda/ObsSpace.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

namespace ioda {
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;

/// ObsBoundsCheck: generic quality control based on observation data only

// Check that observations are within some bounds over some domain

class ObsBoundsCheck : public util::Printable,
                       private util::ObjectCounter<ObsBoundsCheck> {
 public:
  static const std::string classname() {return "ufo::ObsBoundsCheck";}

  ObsBoundsCheck(ioda::ObsSpace &, const eckit::Configuration &);
  ~ObsBoundsCheck();

  void priorFilter(const GeoVaLs &) const;
  void postFilter(const ioda::ObsVector &) const {}

 private:
  void print(std::ostream &) const;

  ioda::ObsSpace & obsdb_;
  const eckit::LocalConfiguration config_;
};

}  // namespace ufo

#endif  // UFO_OBSBOUNDSCHECK_H_