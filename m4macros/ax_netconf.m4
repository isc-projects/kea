AC_DEFUN([AX_NETCONF], [

  AC_ARG_WITH([libyang],
    [AS_HELP_STRING([--with-libyang[[=PATH]]], [optional path to the libyang installation directory])],
    [with_libyang="${withval}"])

    DISTCHECK_LIBYANG_CONFIGURE_FLAG="--with-libyang=$with_libyang"

  AC_ARG_WITH([libyang-cpp],
    [AS_HELP_STRING([--with-libyang-cpp[[=PATH]]], [optional path to the libyang-cpp installation directory])],
    [with_libyangcpp="${withval}"])

    DISTCHECK_LIBYANGCPP_CONFIGURE_FLAG="--with-libyang-cpp=$with_libyangcpp"

  AC_ARG_WITH([sysrepo],
    [AS_HELP_STRING([--with-sysrepo[[=PATH]]], [optional path to the sysrepo installation directory])],
    [with_sysrepo="${withval}"])

    DISTCHECK_SYSREPO_CONFIGURE_FLAG="--with-sysrepo=$with_sysrepo"

  AC_ARG_WITH([sysrepo-cpp],
    [AS_HELP_STRING([--with-sysrepo-cpp[[=PATH]]], [optional path to the sysrepo-cpp installation directory])],
    [with_sysrepocpp="${withval}"])

    DISTCHECK_SYSREPOCPP_CONFIGURE_FLAG="--with-sysrepo-cpp=$with_sysrepocpp"

  if test -n "${with_libyang}"; then
    AC_MSG_CHECKING([libyang])
    AX_FIND_LIBRARY([libyang], ["${with_libyang}"], [libyang/libyang.h], [libyang.so], [])
    if "${LIBRARY_FOUND}"; then
      LIBYANG_CPPFLAGS="${LIBRARY_CPPFLAGS}"
      LIBYANG_INCLUDEDIR="${LIBRARY_INCLUDEDIR}"
      LIBYANG_LIBS="${LIBRARY_LIBS}"
      LIBYANG_PREFIX="${LIBRARY_PREFIX}"
      LIBYANG_VERSION="${LIBRARY_VERSION}"

      # Save flags.
      CPPFLAGS_SAVED="${CPPFLAGS}"
      LIBS_SAVED="${LIBS}"

      # Provide libyang flags temporarily.
      CPPFLAGS="${CPPFLAGS} ${LIBYANG_INCLUDEDIR} ${LIBYANG_CPPFLAGS}"
      LIBS="${LIBS} ${LIBYANG_LIBS}"

      # Check that a simple program using libyang C API can compile and link.
      AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
          [#include <libyang/libyang.h>],
          [struct lyd_node* node = NULL;
           lyd_free_all(node);]
        )],
        [],
        [AC_MSG_RESULT([no])
         AX_DISPLAY_LIBRARY_WARNINGS()
         AC_MSG_ERROR([libyang program failed to compile:

$(cat conftest.cpp)

$(cat conftest.err)])]
  )

      # Restore flags.
      CPPFLAGS="${CPPFLAGS_SAVED}"
      LIBS="${LIBS_SAVED}"

      AC_SUBST(LIBYANG_CPPFLAGS)
      AC_SUBST(LIBYANG_INCLUDEDIR)
      AC_SUBST(LIBYANG_LIBS)
      AC_SUBST(LIBYANG_PREFIX)
      AC_SUBST(LIBYANG_VERSION)

      AC_DEFINE([LIBYANG_VERSION], ["${LIBYANG_VERSION}"], [libyang version])
      AC_MSG_RESULT([${LIBYANG_VERSION}])
    else
      AC_MSG_RESULT([no])
      AX_DISPLAY_LIBRARY_WARNINGS()
      AC_MSG_ERROR([Could not enable libyang.])
    fi
  fi

  if test -n "${with_libyangcpp}"; then
    AC_MSG_CHECKING([libyang-cpp])
    AX_FIND_LIBRARY([libyang-cpp], ["${with_libyangcpp}"], [libyang/Libyang.hpp], [libyang-cpp.so], [], ["${LIBYANG_PREFIX}/lib/pkgconfig:${LIBYANG_PREFIX}/lib64/pkgconfig"])
    if "${LIBRARY_FOUND}"; then
      LIBYANGCPP_CPPFLAGS="${LIBRARY_CPPFLAGS}"
      LIBYANGCPP_INCLUDEDIR="${LIBRARY_INCLUDEDIR}"
      LIBYANGCPP_LIBS="${LIBRARY_LIBS}"
      LIBYANGCPP_PREFIX="${LIBRARY_PREFIX}"
      LIBYANGCPP_VERSION="${LIBRARY_VERSION}"

      if ! "${CPP20_SUPPORTED}"; then
          AC_MSG_RESULT([no])
          AC_MSG_ERROR([You need a compiler with C++20 support to enable libyang-cpp.])
      fi

      # Save flags.
      CPPFLAGS_SAVED="${CPPFLAGS}"
      LIBS_SAVED="${LIBS}"

      # Provide libyang-cpp flags temporarily.
      CPPFLAGS="${CPPFLAGS} ${LIBYANG_INCLUDEDIR} ${LIBYANGCPP_INCLUDEDIR} ${LIBYANG_CPPFLAGS} ${LIBYANGCPP_CPPFLAGS} -std=c++20"
      LIBS="${LIBS} ${LIBYANG_LIBS} ${LIBYANGCPP_LIBS}"

      # Check that a simple program using libyang C++ API can compile and link.
      AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
          [#include <libyang-cpp/DataNode.hpp>],
          [libyang::DataNode *node = nullptr;
           node->findPath("/path");]
        )],
        [],
        [AC_MSG_RESULT([no])
         AX_DISPLAY_LIBRARY_WARNINGS()
         AC_MSG_ERROR([libyang-cpp program failed to compile:

$(cat conftest.cpp)

$(cat conftest.err)])]
  )

      # Restore flags.
      CPPFLAGS="${CPPFLAGS_SAVED}"
      LIBS="${LIBS_SAVED}"

      AC_SUBST(LIBYANGCPP_CPPFLAGS)
      AC_SUBST(LIBYANGCPP_INCLUDEDIR)
      AC_SUBST(LIBYANGCPP_LIBS)
      AC_SUBST(LIBYANGCPP_PREFIX)
      AC_SUBST(LIBYANGCPP_VERSION)

      AC_MSG_RESULT([${LIBYANGCPP_VERSION}])
    else
      AC_MSG_RESULT([no])
      AX_DISPLAY_LIBRARY_WARNINGS()
      AC_MSG_ERROR([Could not enable libyang-cpp.])
    fi
  fi

  if test -n "${with_sysrepo}"; then
    AC_MSG_CHECKING([sysrepo])
    AX_FIND_LIBRARY([sysrepo], ["${with_sysrepo}"], [sysrepo.h], [libsysrepo.so], [SR_REPO_PATH,SR_PLUGINS_PATH,SRPD_PLUGINS_PATH], ["${LIBYANG_PREFIX}/lib/pkgconfig:${LIBYANG_PREFIX}/lib64/pkgconfig"])
    if "${LIBRARY_FOUND}"; then
      SYSREPO_CPPFLAGS="${LIBRARY_CPPFLAGS}"
      SYSREPO_INCLUDEDIR="${LIBRARY_INCLUDEDIR}"
      SYSREPO_LIBS="${LIBRARY_LIBS}"
      SYSREPO_PREFIX="${LIBRARY_PREFIX}"
      SYSREPO_VERSION="${LIBRARY_VERSION}"

      # Save flags.
      CPPFLAGS_SAVED="${CPPFLAGS}"
      LIBS_SAVED="${LIBS}"

      # Provide sysrepo flags temporarily.
      CPPFLAGS="${CPPFLAGS} ${LIBYANG_INCLUDEDIR} ${SYSREPO_INCLUDEDIR} ${LIBYANG_CPPFLAGS} ${SYSREPO_CPPFLAGS}"
      LIBS="${LIBS} ${LIBYANG_LIBS} ${SYSREPO_LIBS}"

      # Check that a simple program using sysrepo C API can compile and link.
      AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
          [#include <sysrepo.h>],
          [sr_conn_ctx_t* connection = NULL;
           sr_disconnect(connection);]
        )],
        [],
        [AC_MSG_RESULT([no])
         AX_DISPLAY_LIBRARY_WARNINGS()
         AC_MSG_ERROR([sysrepo program failed to compile:

$(cat conftest.cpp)

$(cat conftest.err)])]
  )

      # Restore flags.
      CPPFLAGS="${CPPFLAGS_SAVED}"
      LIBS="${LIBS_SAVED}"

      AC_SUBST(SYSREPO_CPPFLAGS)
      AC_SUBST(SYSREPO_INCLUDEDIR)
      AC_SUBST(SYSREPO_LIBS)
      AC_SUBST(SYSREPO_PREFIX)
      AC_SUBST(SYSREPO_VERSION)

      AC_SUBST(SR_REPO_PATH)
      AC_SUBST(SR_PLUGINS_PATH)
      AC_SUBST(SRPD_PLUGINS_PATH)

      AC_DEFINE([SYSREPO_VERSION], ["${SYSREPO_VERSION}"], [sysrepo version])
      AC_MSG_RESULT([${SYSREPO_VERSION}])
    else
      AC_MSG_RESULT([no])
      AX_DISPLAY_LIBRARY_WARNINGS()
      AC_MSG_ERROR([Could not enable sysrepo.])
    fi
  fi

  if test -n "${with_sysrepocpp}"; then
    AC_MSG_CHECKING([sysrepo-cpp])
    AX_FIND_LIBRARY([sysrepo-cpp], ["${with_sysrepocpp}"], [sysrepo-cpp/Session.hpp], [libsysrepo-cpp.so], [], ["${LIBYANG_PREFIX}/lib/pkgconfig:${LIBYANG_PREFIX}/lib64/pkgconfig:${LIBYANGCPP_PREFIX}/lib/pkgconfig:${LIBYANGCPP_PREFIX}/lib64/pkgconfig:${SYSREPO_PREFIX}/lib/pkgconfig:${SYSREPOCPP_PREFIX}/lib64/pkgconfig"])
    if "${LIBRARY_FOUND}"; then
      SYSREPOCPP_CPPFLAGS="${LIBRARY_CPPFLAGS}"
      SYSREPOCPP_INCLUDEDIR="${LIBRARY_INCLUDEDIR}"
      SYSREPOCPP_LIBS="${LIBRARY_LIBS}"
      SYSREPOCPP_PREFIX="${LIBRARY_PREFIX}"
      SYSREPOCPP_VERSION="${LIBRARY_VERSION}"

      if ! "${CPP20_SUPPORTED}"; then
          AC_MSG_RESULT([no])
          AC_MSG_ERROR([You need a compiler with C++20 support to enable sysrepo-cpp.])
      fi

      # Save flags.
      CPPFLAGS_SAVED="${CPPFLAGS}"
      LIBS_SAVED="${LIBS}"

      # Provide sysrepo-cpp flags temporarily.
      CPPFLAGS="${CPPFLAGS} ${LIBYANG_INCLUDEDIR} ${LIBYANG_CPPFLAGS} ${LIBYANGCPP_INCLUDEDIR} ${LIBYANGCPP_CPPFLAGS} ${SYSREPO_INCLUDEDIR} ${SYSREPO_CPPFLAGS} ${SYSREPOCPP_INCLUDEDIR} ${SYSREPOCPP_CPPFLAGS} -std=c++20"
      LIBS="${LIBS} ${LIBYANG_LIBS} ${LIBYANGCPP_LIBS} ${SYSREPO_LIBS} ${SYSREPOCPP_LIBS}"

      # Check that a simple program using sysrepo C++ API can compile and link.
      AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
          [#include <sysrepo-cpp/Connection.hpp>],
          [sysrepo::Connection connection;
           connection.sessionStart();]
        )],
        [],
        [AC_MSG_RESULT([no])
         AX_DISPLAY_LIBRARY_WARNINGS()
         AC_MSG_ERROR([sysrepo-cpp program failed to compile:

$(cat conftest.cpp)

$(cat conftest.err)])]
  )

      # Restore flags.
      CPPFLAGS="${CPPFLAGS_SAVED}"
      LIBS="${LIBS_SAVED}"

      AC_SUBST(SYSREPOCPP_CPPFLAGS)
      AC_SUBST(SYSREPOCPP_INCLUDEDIR)
      AC_SUBST(SYSREPOCPP_LIBS)
      AC_SUBST(SYSREPOCPP_PREFIX)
      AC_SUBST(SYSREPOCPP_VERSION)

      AC_MSG_RESULT([${SYSREPOCPP_VERSION}])
    else
      AC_MSG_RESULT([no])
      AX_DISPLAY_LIBRARY_WARNINGS()
      AC_MSG_ERROR([Could not enable sysrepo-cpp.])
    fi
  fi

  # Set HAVE_NETCONF.
  if test -n "${LIBYANG_VERSION}" && \
    test -n "${LIBYANGCPP_VERSION}" && \
    test -n "${SYSREPO_VERSION}" && \
    test -n "${SYSREPOCPP_VERSION}"; then
    HAVE_NETCONF=yes

    # C++20 support is already proven to be supported, but it may not be the
    # default for the current compiler, so enforce it.
    CPPFLAGS="${CPPFLAGS} -std=c++20"
  else
    HAVE_NETCONF=no
  fi
  AM_CONDITIONAL(HAVE_NETCONF, test "${HAVE_NETCONF}" = 'yes')
  AM_COND_IF([HAVE_NETCONF], AC_DEFINE([HAVE_NETCONF], [true], [NETCONF capabilities enabled]))
  AC_SUBST(HAVE_NETCONF)

  AC_SUBST(DISTCHECK_LIBYANG_CONFIGURE_FLAG)
  AC_SUBST(DISTCHECK_LIBYANGCPP_CONFIGURE_FLAG)
  AC_SUBST(DISTCHECK_SYSREPO_CONFIGURE_FLAG)
  AC_SUBST(DISTCHECK_SYSREPOCPP_CONFIGURE_FLAG)
])
