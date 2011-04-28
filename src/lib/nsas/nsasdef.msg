# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

$PREFIX NSAS_
$NAMESPACE isc::nsas

INVRESPSTR      queried for %s but got invalid response
+ This message indicates an internal error in the nameserver address store
+ component (NSAS) of the resolver.  The NSAS made a query for a RR for the
+ specified nameserver but received an invalid response.  Either the success
+ function was called without a DNS message or the message was invalid on some
+ way. (In the latter case, the error should have been picked up elsewhere in
+ the processing logic, hence the raising of the error here.)

INVRESPTC       queried for %s RR of type/class %s/%s, received response %s/%s
+ This message indicates an internal error in the nameserver address store
+ component (NSAS) of the resolver.  The NSAS made a query for the given RR
+ type and class, but instead received an answer with the given type and class.

LOOKUPCANCEL    lookup for zone %s has been cancelled
+ A debug message, this is output when a NSAS (nameserver address store -
+ part of the resolver) lookup for a zone has been + cancelled.

LOOKUPZONE      searching NSAS for nameservers for zone %s
+ A debug message, this is output when a call is made to the nameserver address
+ store (part of the resolver) to obtain the nameservers for the specified zone.

NSADDR          asking resolver to obtain A and AAAA records for %s
+ A debug message, the NSAS (nameserver address store - part of the resolver) is
+ making a callback into the resolver to retrieve the address records for the
+ specified nameserver.

NSLKUPFAIL      failed to lookup any %s for %s
+ A debug message, the NSAS (nameserver address store - part of the resolver)
+ has been unable to retrieve the specified resource record for the specified
+ nameserver.  This is not necessarily a problem - the nameserver may be
+ unreachable, in which case the NSAS will try other nameservers in the zone.

NSLKUPSUCC      found address %s for %s
+ A debug message, the NSAS (nameserver address store - part of the resolver)
+ has retrieved the given address for the specified nameserver through an
+ external query.

SETRTT          reporting RTT for %s as %d; new value is now %d
+ A NSAS (nameserver address store - part of the resolver) debug message
+ reporting the round-trip time (RTT) for a query made to the specified
+ nameserver.  The RTT has been updated using the value given and the new RTT is
+ displayed.  (The RTT is subject to a calculation that damps out sudden
+ changes.  As a result, the new RTT is not necessarily equal to the RTT
+ reported.)
