#ifndef _DATA_DEF_H
#define _DATA_DEF_H 1

#include "data.h"

#include <sstream>

namespace ISC { namespace Data {

    class DataDefinition {
    public:
        explicit DataDefinition() {};
        explicit DataDefinition(ElementPtr e) : definition(e) {};
        explicit DataDefinition(std::istream& in) throw(ParseError);

        const ElementPtr getDefinition() { return definition; };
        // returns true if the given element conforms to this data
        // definition scheme
        bool validate(const ElementPtr data);

    private:
        bool validate_item(const ElementPtr spec, const ElementPtr data);
        bool validate_spec(const ElementPtr spec, const ElementPtr data);
        bool validate_spec_list(const ElementPtr spec, const ElementPtr data);

        ElementPtr definition;
    };

} }

#endif // _DATA_DEF_H
