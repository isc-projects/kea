// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLNT_CONFIG_H
#define CLNT_CONFIG_H

#include <process/d_cfg_mgr.h>

namespace isc {
namespace client {

class ClntConfig;
typedef boost::shared_ptr<ClntConfig> ClntConfigPtr;

class ClntConfig : public process::DCfgContextBase {
public:
  ClntConfig();

  virtual process::BaseConfigPtr clone() const {
      return (process::BaseConfigPtr(new ClntConfig(*this)));
  }

  virtual isc::data::ElementPtr toElement() const;

  virtual std::string getConfigSummary(const uint32_t selection) const;
};


};
};

#endif
