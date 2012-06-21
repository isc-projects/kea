#include <datasrc/client_list.h>
#include <datasrc/client.h>

#include <dns/name.h>

// Note: This file breaks almost every rule about how it should look like and
// other formalities. However, it is only a transitional file and will be deleted
// before the end of this branch.

using namespace isc::datasrc;
using namespace isc::dns;

class SingletonList : public ClientList {
public:
    SingletonList(DataSourceClient& client) :
        client_(client)
    {}
    virtual FindResult find(const Name& zone, bool exact, bool) const {
        DataSourceClient::FindResult result(client_.findZone(zone));
        switch (result.code) {
            case result::SUCCESS:
                return (FindResult(&client_, result.zone_finder, true));
            case result::PARTIALMATCH:
                if (!exact) {
                    return (FindResult(&client_, result.zone_finder, false));
                }
            default:
                return (FindResult());
        }
    }
private:
    DataSourceClient& client_;
};
