
#include <scripts.h>
#include <scripts_cfg.h>

namespace hooks {
namespace scripts {

bool callScript(const Variables& vars) {
    
    ScriptsConfigPtr cfg = getScriptsConfig();
    try {


    } catch (const std::exception& e) {

        return (false);
    }

    return (true);
}

};
};
