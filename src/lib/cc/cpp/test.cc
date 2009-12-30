
#include "data.h"
#include "data_def.h"

#include <fstream>

using namespace std;
using namespace isc::data;

int
main(int argc, char **argv) {
    std::ifstream file;
    std::stringstream ss;
    DataDefinition def;
    ElementPtr data;

    file.open("parkinglot.spec");
    if (!file) {
        cout << "error opening parkinglot.spec" << endl;
        return 1;
    }

    try {
        def = DataDefinition(file);
        cout << "Definition: " << endl;
        cout << def.getDefinition() << endl;
    } catch (ParseError pe) {
        cout << "Error parsing definition file: " << pe.what() << endl;
        return 1;
    } catch (DataDefinitionError dde) {
        cout << "Error reading definition file: " << dde.what() << endl;
        return 1;
    }
    file.close();

    file.open("parkinglot.data");
    if (!file) {
        cout << "error opening parkinglot.data" << endl;
        return 1;
    }
    try {
        data = Element::createFromString(file);
        cout << "Data: " << endl;
        cout << data << endl;
    } catch (ParseError pe) {
        cout << "Error parsing data file: " << pe.what() << endl;
        return 1;
    }

    if (def.validate(data)) {
        cout << "Data validated" << endl;
        cout << data << endl;
    } else {
        cout << "Error in data validation" << endl;
    }
    file.close();
}
