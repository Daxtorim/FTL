/* Pi-hole: A black hole for Internet advertisements
*  (c) 2019 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Datastructure prototypes
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

// Definition of sqlite3_stmt
#include "database/sqlite3.h"

// enum privacy_level
#include "enums.h"

extern const char *querytypes[TYPE_MAX];

typedef struct {
	unsigned char magic;
	enum query_status status;
	enum query_types type;
	enum privacy_level privacylevel;
	enum reply_type reply;
	enum dnssec_status dnssec;
	uint16_t qtype;
	int domainID;
	int clientID;
	int upstreamID;
	int id; // the ID is a (signed) int in dnsmasq, so no need for a long int here
	int CNAME_domainID; // only valid if query has a CNAME blocking status
	unsigned int timeidx;
	unsigned long response; // saved in units of 1/10 milliseconds (1 = 0.1ms, 2 = 0.2ms, 2500 = 250.0ms, etc.)
	unsigned long forwardresponse; // saved in units of 1/10 milliseconds (1 = 0.1ms, 2 = 0.2ms, 2500 = 250.0ms, etc.)
	time_t timestamp;
	int64_t db;
	bool whitelisted;
	bool complete;
} queriesData;

typedef struct {
	unsigned char magic;
	bool new;
	int count;
	int failed;
	unsigned int responses;
	in_addr_t port;
	unsigned long rtime;
	unsigned long rtuncertainty;
	size_t ippos;
	size_t namepos;
	time_t lastQuery;
} upstreamsData;

typedef struct {
	unsigned char magic;
	unsigned char reread_groups;
	char hwlen;
	unsigned char hwaddr[16]; // See DHCP_CHADDR_MAX in dnsmasq/dhcp-protocol.h
	bool new;
	bool found_group;
	bool aliasclient;
	int count;
	int blockedcount;
	int aliasclient_id;
	int overTime[OVERTIME_SLOTS];
	unsigned int id;
	unsigned int numQueriesARP;
	size_t groupspos;
	size_t ippos;
	size_t namepos;
	size_t ifacepos;
	time_t lastQuery;
	time_t firstSeen;
} clientsData;

typedef struct {
	unsigned char magic;
	size_t domainpos;
	int count;
	int blockedcount;
} domainsData;

typedef struct {
	unsigned char magic;
	enum domain_client_status blocking_status;
	unsigned char force_reply;
	enum query_types query_type;
	int domainID;
	int clientID;
	int black_regex_idx;
} DNSCacheData;

void strtolower(char *str);
int findQueryID(const int id);
int findUpstreamID(const char * upstream, const in_port_t port, const bool count);
int findDomainID(const char *domain, const bool count);
int findClientID(const char *client, const bool count, const bool aliasclient);
int findCacheID(int domainID, int clientID, enum query_types query_type);
bool isValidIPv4(const char *addr);
bool isValidIPv6(const char *addr);

void FTL_reload_all_domainlists(void);
void FTL_reset_per_client_domain_data(void);

const char *getDomainString(const queriesData* query);
const char *getCNAMEDomainString(const queriesData* query);
const char *getClientIPString(const queriesData* query);
const char *getClientNameString(const queriesData* query);

void change_clientcount(clientsData *client, int total, int blocked, int overTimeIdx, int overTimeMod);

// Pointer getter functions
#define getQuery(queryID, checkMagic) _getQuery(queryID, checkMagic, __LINE__, __FUNCTION__, __FILE__)
queriesData* _getQuery(int queryID, bool checkMagic, int line, const char * function, const char * file);
#define getClient(clientID, checkMagic) _getClient(clientID, checkMagic, __LINE__, __FUNCTION__, __FILE__)
clientsData* _getClient(int clientID, bool checkMagic, int line, const char * function, const char * file);
#define getDomain(domainID, checkMagic) _getDomain(domainID, checkMagic, __LINE__, __FUNCTION__, __FILE__)
domainsData* _getDomain(int domainID, bool checkMagic, int line, const char * function, const char * file);
#define getUpstream(upstreamID, checkMagic) _getUpstream(upstreamID, checkMagic, __LINE__, __FUNCTION__, __FILE__)
upstreamsData* _getUpstream(int upstreamID, bool checkMagic, int line, const char * function, const char * file);
#define getDNSCache(cacheID, checkMagic) _getDNSCache(cacheID, checkMagic, __LINE__, __FUNCTION__, __FILE__)
DNSCacheData* _getDNSCache(int cacheID, bool checkMagic, int line, const char * function, const char * file);

#endif //DATASTRUCTURE_H
