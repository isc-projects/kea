#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include <cc/cpp/data.h>

#include "name.h"

#include "data_source.h"

namespace isc {
namespace dns {

void
DataSource::getData(isc::dns::RRsetPtr query, isc::dns::Message& answer)
{
    return;
}

}
}
