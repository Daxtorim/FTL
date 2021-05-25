/* Pi-hole: A black hole for Internet advertisements
*  (c) 2021 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  dnsmasq server interfacing routines
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef FTL_CHECK_BLOCKING_H
#define FTL_CHECK_BLOCKING_H

#ifdef FTL_PRIVATE
  #if !defined(FTLDNS)
  #define FTLDNS
  #include "../dnsmasq/dnsmasq.h"
  #undef __USE_XOPEN
  #include "../FTL.h"
  #endif
#endif // FTL_PRIVATE

#include <stdbool.h>

#define FTL_check_blocking(queryID, domainID, clientID, blockingreason) _FTL_check_blocking(queryID, domainID, clientID, blockingreason, __FILE__, __LINE__)
bool _FTL_check_blocking(int queryID, int domainID, int clientID, const char **blockingreason, const char* file, const int line);

#endif // FTL_CHECK_BLOCKING_H
