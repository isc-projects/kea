project('netconf')
cpp = meson.get_compiler('cpp')
SYSTEM = build_machine.system()

netconf_deps = {}

foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
    netconf_deps = netconf_deps + {dep: dependency(dep, required: false)}
    if netconf_deps[dep].found()
        continue
    endif

    # Try adding lib to it. libyang and libyang-cpp define the wrong pkg-config.
    netconf_deps = netconf_deps + {
        dep: dependency('lib' + dep, required: false),
    }
    if netconf_deps[dep].found()
        continue
    endif

    # Search in /opt.
    foreach prefix : ['', 'lib']
        path = f'/opt/@prefix@@dep@'
        lib = cpp.find_library(dep, dirs: [f'/@path@/lib'], required: false)
        if lib.found()
            netconf_deps = netconf_deps + {
                dep: declare_dependency(
                    dependencies: [lib],
                    include_directories: include_directories(f'/@path@/include'),
                    variables: {'prefix': f'@path@'},
                ),
            }
            if SYSTEM == 'darwin'
                add_project_link_arguments(
                    f'-Wl,-rpath,@path@/lib',
                    language: 'cpp',
                )
            else
                add_project_link_arguments(
                    f'-Wl,-rpath=@path@/lib',
                    language: 'cpp',
                )
            endif
        endif
    endforeach
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
    if netconf_deps['yang'].found()
        libyang_prefix = netconf_deps['yang'].get_variable('prefix')
        libyang_version = netconf_deps['yang'].version()
        if libyang_version == 'unknown'
            libyang_version = 'unknown version'
        endif
    else
        libyang_prefix = 'unknown'
        libyang_version = 'unknown version'
    endif
    variables += {'libyang_prefix': libyang_prefix}
    variables += {'libyang_version': libyang_version}
    if netconf_deps['yang-cpp'].found()
        libyangcpp_version = netconf_deps['yang-cpp'].version()
        if libyangcpp_version == 'unknown'
            libyangcpp_version = 'unknown version'
        endif
    else
        libyangcpp_version = 'unknown version'
    endif
    variables += {'libyangcpp_version': libyangcpp_version}
    if netconf_deps['sysrepo'].found()
        sysrepo_prefix = netconf_deps['sysrepo'].get_variable('prefix')
        sysrepo_version = netconf_deps['sysrepo'].version()
        if sysrepo_version == 'unknown'
            sysrepo_version = 'unknown version'
        endif
    else
        sysrepo_prefix = 'unknown'
        sysrepo_version = 'unknown version'
    endif
    variables += {'sysrepo_prefix': sysrepo_prefix}
    variables += {'sysrepo_version': sysrepo_version}
    if netconf_deps['sysrepo-cpp'].found()
        sysrepocpp_version = netconf_deps['sysrepo-cpp'].version()
        if sysrepocpp_version == 'unknown'
            sysrepocpp_version = 'unknown version'
        endif
    else
        sysrepocpp_version = 'unknown version'
    endif
    variables += {'sysrepocpp_version': sysrepocpp_version}
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
