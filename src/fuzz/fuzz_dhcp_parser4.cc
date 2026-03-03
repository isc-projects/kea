// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <cc/command_interpreter.h>
#include <cc/data.h>

#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/parser_context.h>
#include <log/logger_support.h>
#include <process/daemon.h>

#include "helper_func.h"

#include <array>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <vector>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;

using ControlledDhcpvSrv = ControlledDhcpv4Srv;
static constexpr Parser4Context::ParserType parserTypes[] = {
    Parser4Context::PARSER_JSON,
    Parser4Context::PARSER_INTERFACES,
    Parser4Context::PARSER_OPTION_DATA,
    Parser4Context::PARSER_OPTION_DEF,
    Parser4Context::PARSER_OPTION_DEFS,
    Parser4Context::PARSER_HOST_RESERVATION,
    Parser4Context::PARSER_HOOKS_LIBRARY,
    Parser4Context::PARSER_DHCP_DDNS,
    Parser4Context::PARSER_CONFIG_CONTROL,
    Parser4Context::PARSER_HOST_RESERVATION,
    Parser4Context::PARSER_DHCP4,
    Parser4Context::SUBPARSER_DHCP4,
    Parser4Context::PARSER_SUBNET4,
    Parser4Context::PARSER_POOL4,
};

static const char *cmds[] = {"config-get",
                             "config-hash-get",
                             "config-write",
                             "config-set",
                             "config-test",
                             "config-reload",
                             "dhcp-disable",
                             "dhcp-enable",
                             "version-get",
                             "build-report",
                             "leases-reclaim",
                             "server-tag-get",
                             "config-backend-pull",
                             "status-get",
                             "statistic-set-max-sample-count-all",
                             "statistic-set-max-sample-age-all",
                             "subnet4-select-test",
                             "subnet4o6-select-test",
                             "lfc-start",
                             "shutdown"};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialise logging
  setenv("KEA_LOGGER_DESTINATION", "/dev/null", 0);
  setenv("KEA_LOCKFILE_DIR", "/tmp", 0);
  setenv("KEA_PIDFILE_DIR", "/tmp", 0);
  setenv("KEA_LFC_EXECUTABLE", "/bin/true", 0);
  try {
    isc::log::initLogger("fuzzer");
    isc::process::Daemon::loggerInit("fuzzer", false);
    isc::process::Daemon::setDefaultLoggerName("fuzzer");
  } catch (...) {
    // Early exit if logging initialisation failed
    return 0;
  }

  // Set variables
  FuzzedDataProvider fdp(data, size);
  Parser4Context ctx;
  ControlledDhcpv4Srv srv(0, 0);

  // Get random flags
  const bool checkOnly = fdp.ConsumeBool();
  const bool extraChecks = fdp.ConsumeBool();

  // Get random type and command
  Parser4Context::ParserType type =
      parserTypes[fdp.ConsumeIntegralInRange<int>(0, 13)];
  std::string cmdStr =
      std::string(cmds[fdp.ConsumeIntegralInRange<int>(0, 19)]);

  // If no more remaining bytes, early exit
  if (fdp.remaining_bytes() <= 0) {
    return 0;
  }

  // Provide two type of payload with different length to avoid
  // timeout from parsing trusted configuration file
  std::string limit_payload = fdp.ConsumeRandomLengthString(25600);
  std::string full_payload(reinterpret_cast<const char*>(data), size);

  // First target based on the raw payload entire. This makes seeding a lot
  // easier.
  try {
    ElementPtr rawTree = ctx.parseString(limit_payload, Parser4Context::PARSER_JSON);

    // Configure the server with valid tree
    if (rawTree) {
        configureDhcp4Server(srv, rawTree, false, extraChecks);
        ControlledDhcpv4Srv::checkConfig(rawTree);
        ControlledDhcpv4Srv::processConfig(rawTree);
    }
  } catch (const isc::Exception&) {
  }

  try {
    ElementPtr tree = ctx.parseString(limit_payload, type);

    // Configure the server with valid tree
    if (tree) {
      if (type == Parser4Context::PARSER_JSON ||
          type == Parser4Context::PARSER_DHCP4) {
        configureDhcp4Server(srv, tree, checkOnly, extraChecks);
        ControlledDhcpv4Srv::checkConfig(tree);
        ControlledDhcpv4Srv::processConfig(tree);
      }
    }
  } catch (const isc::Exception&) {
  }

  // File base parsing
  try {
    std::string path = fuzz::writeTempFile(limit_payload, "json");
    if (!path.empty()) {
      ElementPtr fileTree = ctx.parseFile(path, Parser4Context::PARSER_DHCP4);
      if (fileTree) {
        configureDhcp4Server(srv, fileTree, checkOnly, extraChecks);
        ControlledDhcpv4Srv::checkConfig(fileTree);
        ControlledDhcpv4Srv::processConfig(fileTree);
      }
      unlink(path.c_str());
    }
  } catch (const isc::Exception&) {
  }

  // Command parsing
  try {
    ElementPtr args = fuzz::parseJSON(full_payload);
    ElementPtr cmd = Element::create(cmdStr);

    // Configure root element
    ElementPtr root = Element::createMap();
    root->set("command", cmd);
    root->set("arguments", args);

    // Transform to const element
    ConstElementPtr cmd_const = cmd;
    ConstElementPtr root_const = root;

    parseCommand(cmd_const, root_const);

    // Response answer parsing
    int status = 0;
    parseAnswer(status, fuzz::parseJSON(full_payload));
  } catch(const isc::Exception&) {}

    // Try fuzzing specific deeper fuzzers directly

    // Subnets6ListConfigParser
    try {
        ElementPtr elem = fuzz::parseJSON(full_payload);
        SrvConfigPtr srv = SrvConfigPtr(new SrvConfig());
        Subnets6ListConfigParser parser(fdp.ConsumeBool());
        parser.parse(srv, elem, fdp.ConsumeBool());
    } catch (const isc::Exception&) {
        // Known exceptions
    }

    // RelayInfoParser
    try {
        Option::Universe opt = Option::V4;
        ElementPtr elem = fuzz::parseJSON(full_payload);
        Network::RelayInfoPtr info = Network::RelayInfoPtr(new Network::RelayInfo());
        RelayInfoParser parser(opt);
        parser.parse(info, elem);
    } catch (const isc::Exception&) {
        // Known exceptions
    }

    // PdPoolParser
    try {
        ElementPtr elem = fuzz::parseJSON(full_payload);
        PoolStoragePtr pools(new PoolStorage());
        PdPoolParser parser = PdPoolParser();
        parser.parse(pools, elem, fdp.ConsumeBool());
    } catch (const isc::Exception&) {
        // Known exceptions
    }

    // CompatibilityParser
    try {
        ElementPtr elem = fuzz::parseJSON(full_payload);
        SrvConfig srv = SrvConfig();
        CompatibilityParser parser = CompatibilityParser();
        parser.parse(elem, srv);
    } catch (const isc::Exception&) {
        // Known exceptions
    }

  return 0;
}
