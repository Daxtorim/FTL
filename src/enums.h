/* Pi-hole: A black hole for Internet advertisements
*  (c) 2020 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Global enums
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef ENUMS_H
#define ENUMS_H

enum memory_type {
	QUERIES,
	UPSTREAMS,
	CLIENTS,
	DOMAINS,
	OVERTIME,
	DNS_CACHE,
	STRINGS
} __attribute__ ((packed));

enum dnssec_status {
	DNSSEC_UNKNOWN,
	DNSSEC_SECURE,
	DNSSEC_INSECURE,
	DNSSEC_BOGUS,
	DNSSEC_ABANDONED,
	DNSSEC_MAX
} __attribute__ ((packed));

enum query_status {
	STATUS_UNKNOWN,
	STATUS_GRAVITY,
	STATUS_FORWARDED,
	STATUS_CACHE,
	STATUS_REGEX,
	STATUS_DENYLIST,
	STATUS_EXTERNAL_BLOCKED_IP,
	STATUS_EXTERNAL_BLOCKED_NULL,
	STATUS_EXTERNAL_BLOCKED_NXRA,
	STATUS_GRAVITY_CNAME,
	STATUS_REGEX_CNAME,
	STATUS_DENYLIST_CNAME,
	STATUS_RETRIED,
	STATUS_RETRIED_DNSSEC,
	STATUS_IN_PROGRESS,
	STATUS_MAX
} __attribute__ ((packed));

enum reply_type {
	REPLY_UNKNOWN,
	REPLY_NODATA,
	REPLY_NXDOMAIN,
	REPLY_CNAME,
	REPLY_IP,
	REPLY_DOMAIN,
	REPLY_RRNAME,
	REPLY_SERVFAIL,
	REPLY_REFUSED,
	REPLY_NOTIMP,
	REPLY_OTHER,
	REPLY_MAX
}  __attribute__ ((packed));

enum privacy_level {
	PRIVACY_SHOW_ALL = 0,
	PRIVACY_HIDE_DOMAINS,
	PRIVACY_HIDE_DOMAINS_CLIENTS,
	PRIVACY_MAXIMUM
} __attribute__ ((packed));

enum blocking_mode {
	MODE_IP,
	MODE_NX,
	MODE_NULL,
	MODE_IP_NODATA_AAAA,
	MODE_NODATA,
	MODE_MAX
} __attribute__ ((packed));

enum regex_type {
	REGEX_DENY,
	REGEX_ALLOW,
	REGEX_CLI,
	REGEX_MAX
} __attribute__ ((packed));

enum query_type {
	TYPE_A = 1,
	TYPE_AAAA,
	TYPE_ANY,
	TYPE_SRV,
	TYPE_SOA,
	TYPE_PTR,
	TYPE_TXT,
	TYPE_NAPTR,
	TYPE_MX,
	TYPE_DS,
	TYPE_RRSIG,
	TYPE_DNSKEY,
	TYPE_NS,
	TYPE_OTHER,
	TYPE_SVCB,
	TYPE_HTTPS,
	TYPE_MAX
} __attribute__ ((packed));

enum blocking_status {
	BLOCKING_DISABLED,
	BLOCKING_ENABLED,
	BLOCKING_UNKNOWN
} __attribute__ ((packed));

// Blocking status constants used by the dns_cache->blocking_status vector
// We explicitly force UNKNOWN_BLOCKED to zero on all platforms as this is the
// default value set initially with calloc
enum domain_client_status {
	UNKNOWN_BLOCKED = 0,
	GRAVITY_BLOCKED,
	DENYLIST_BLOCKED,
	REGEX_BLOCKED,
	ALLOWED,
	NOT_BLOCKED
} __attribute__ ((packed));

enum debug_flag {
	DEBUG_DATABASE      = (1 << 0),
	DEBUG_NETWORKING    = (1 << 1),
	DEBUG_LOCKS         = (1 << 2),
	DEBUG_QUERIES       = (1 << 3),
	DEBUG_FLAGS         = (1 << 4),
	DEBUG_SHMEM         = (1 << 5),
	DEBUG_GC            = (1 << 6),
	DEBUG_ARP           = (1 << 7),
	DEBUG_REGEX         = (1 << 8),
	DEBUG_API           = (1 << 9),
	DEBUG_OVERTIME      = (1 << 10),
	DEBUG_STATUS        = (1 << 11),
	DEBUG_CAPS          = (1 << 12),
	DEBUG_DNSMASQ_LINES = (1 << 13),
	DEBUG_VECTORS       = (1 << 14),
	DEBUG_RESOLVER      = (1 << 15),
	DEBUG_EDNS0         = (1 << 16),
	DEBUG_CLIENTS       = (1 << 17),
	DEBUG_ALIASCLIENTS  = (1 << 18),
	DEBUG_EVENTS        = (1 << 19),
	DEBUG_HELPER        = (1 << 20),
	DEBUG_CONFIG        = (1 << 21),
	DEBUG_EXTRA         = (1 << 22),
	// DEBUG_EXTRA has always to be the last option
} __attribute__ ((packed));

enum events {
	RELOAD_GRAVITY,
	RELOAD_PRIVACY_LEVEL,
	RESOLVE_NEW_HOSTNAMES,
	RERESOLVE_HOSTNAMES,
	RERESOLVE_HOSTNAMES_FORCE,
	REIMPORT_ALIASCLIENTS,
	PARSE_NEIGHBOR_CACHE,
	EVENTS_MAX
} __attribute__ ((packed));


enum gravity_list_type {
	GRAVITY_DOMAINLIST_ALLOW_EXACT,
	GRAVITY_DOMAINLIST_ALLOW_REGEX,
	GRAVITY_DOMAINLIST_ALLOW_ALL,
	GRAVITY_DOMAINLIST_DENY_EXACT,
	GRAVITY_DOMAINLIST_DENY_REGEX,
	GRAVITY_DOMAINLIST_DENY_ALL,
	GRAVITY_DOMAINLIST_ALL_EXACT,
	GRAVITY_DOMAINLIST_ALL_REGEX,
	GRAVITY_DOMAINLIST_ALL_ALL,
	GRAVITY_GROUPS,
	GRAVITY_ADLISTS,
	GRAVITY_CLIENTS
} __attribute__ ((packed));

enum gravity_tables {
	GRAVITY_TABLE,
	EXACT_BLACKLIST_TABLE,
	EXACT_WHITELIST_TABLE,
	REGEX_BLACKLIST_TABLE,
	REGEX_WHITELIST_TABLE,
	CLIENTS_TABLE,
	GROUPS_TABLE,
	ADLISTS_TABLE,
	DENIED_DOMAINS_TABLE,
	ALLOWED_DOMAINS_TABLE,
	UNKNOWN_TABLE
} __attribute__ ((packed));

enum timers {
	DATABASE_WRITE_TIMER,
	EXIT_TIMER,
	GC_TIMER,
	LISTS_TIMER,
	REGEX_TIMER,
	ARP_TIMER,
	LAST_TIMER
} __attribute__ ((packed));

enum web_code {
	HTTP_INFO,
	PH7_ERROR
} __attribute__ ((packed));

enum refresh_hostnames {
	REFRESH_ALL,
	REFRESH_IPV4_ONLY,
	REFRESH_UNKNOWN,
	REFRESH_NONE
} __attribute__ ((packed));

enum api_auth_status {
	API_AUTH_UNAUTHORIZED  = -1,
	API_AUTH_LOCALHOST  = -2,
	API_AUTH_EMPTYPASS  = -3,
} __attribute__ ((packed));

enum thread_types {
	DB,
	GC,
	DNSclient,
	THREADS_MAX
} __attribute__ ((packed));


enum protocol {
	TCP,
	UDP
} __attribute__ ((packed));

#endif // ENUMS_H
