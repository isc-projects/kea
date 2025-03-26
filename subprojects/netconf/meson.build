project('netconf')
cpp = meson.get_compiler('cpp')
SYSTEM = build_machine.system()

netconf_deps = {}

foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
    netconf_deps = netconf_deps + {dep: dependency(dep, required: false)}
    if netconf_deps[dep].found()
        continue
    endif

    # Try adding lib to it. yang and yang-cpp define the wrong pkg-config.
    netconf_deps = netconf_deps + {
        dep: dependency('lib' + dep, required: false),
    }
    if netconf_deps[dep].found()
        continue
    endif
endforeach

all_deps_found = true
foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
    if not netconf_deps[dep].found()
        all_deps_found = false
        break
    endif
endforeach

if all_deps_found
    variables = {}
    foreach i : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
        if netconf_deps[i].found()
            libdir = netconf_deps[i].get_variable('libdir')
            prefix = netconf_deps[i].get_variable('prefix')
            version = netconf_deps[i].version()
            if version == 'unknown'
                version = 'unknown version'
            endif
        else
            prefix = 'unknown'
            version = 'unknown version'
        endif
        variables += {f'@i@-libdir': libdir}
        variables += {f'@i@-prefix': prefix}
        variables += {f'@i@-version': version}
    endforeach
    netconf = declare_dependency(
        dependencies: [
            netconf_deps['yang'],
            netconf_deps['yang-cpp'],
            netconf_deps['sysrepo'],
            netconf_deps['sysrepo-cpp'],
        ],
        variables: variables,
    )
else
    # Can't use a disabler here?
    netconf = dependency('')
endif
