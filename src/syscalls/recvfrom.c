/* Pi-hole: A black hole for Internet advertisements
*  (c) 2020 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Pi-hole syscall implementation for recvfrom
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */

#include "../FTL.h"
//#include "syscalls.h" is implicitly done in FTL.h
#include "../log.h"

#include <sys/types.h>
#include <sys/socket.h>

#undef recvfrom
ssize_t FTLrecvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen, const char *file, const char *func, const int line)
{
    ssize_t ret = 0;
	do
	{
		// Reset errno before trying to write
		errno = 0;
		ret = recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
	}
	// Try again if the last accept() call failed due to an interruption by an
	// incoming signal
	while(ret < 0 && errno == EINTR);

	// Final error checking (may have faild for some other reason then an
	// EINTR = interrupted system call)
	if(ret < 0)
		log_warn("Could not recvfrom() in %s() (%s:%i): %s",
		         func, file, line, strerror(errno));

    return ret;
}