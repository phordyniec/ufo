/*
 * (C) Copyright 2017-2018 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_MARINE_SEASURFACETEMP_OBSSEASURFACETEMPTLAD_H_
#define UFO_MARINE_SEASURFACETEMP_OBSSEASURFACETEMPTLAD_H_

#include <ostream>
#include <string>

#include <boost/scoped_ptr.hpp>

#include "oops/base/Variables.h"
#include "oops/util/ObjectCounter.h"

#include "ufo/LinearObsOperatorBase.h"
#include "ufo/marine/seasurfacetemp/ObsSeaSurfaceTempTLAD.interface.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace ioda {
  class ObsSpace;
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsBias;
  class ObsBiasIncrement;

// -----------------------------------------------------------------------------
/// SeaSurfaceTemp TL/AD observation operator class
class ObsSeaSurfaceTempTLAD : public LinearObsOperatorBase,
                              private util::ObjectCounter<ObsSeaSurfaceTempTLAD> {
 public:
  static const std::string classname() {return "ufo::ObsSeaSurfaceTempTLAD";}

  ObsSeaSurfaceTempTLAD(const ioda::ObsSpace &, const eckit::Configuration &);
  virtual ~ObsSeaSurfaceTempTLAD();

  // Obs Operators
  void setTrajectory(const GeoVaLs &, const ObsBias &);
  void simulateObsTL(const GeoVaLs &, ioda::ObsVector &, const ObsBiasIncrement &) const;
  void simulateObsAD(GeoVaLs &, const ioda::ObsVector &, ObsBiasIncrement &) const;

  // Other
  const oops::Variables & variables() const {return *varin_;}

  int & toFortran() {return keyOper_;}
  const int & toFortran() const {return keyOper_;}

 private:
  void print(std::ostream &) const;
  F90hop keyOper_;
  const ioda::ObsSpace& odb_;
  boost::scoped_ptr<const oops::Variables> varin_;
};

// -----------------------------------------------------------------------------

}  // namespace ufo
#endif  // UFO_MARINE_SEASURFACETEMP_OBSSEASURFACETEMPTLAD_H_