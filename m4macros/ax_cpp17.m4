AC_DEFUN([AX_ISC_CPP17], [
    AC_MSG_CHECKING([c++17 support])

    # Save flags.
    CPPFLAGS_SAVED="${CPPFLAGS}"

    # Provide -std=c++17 flag temporarily.
    CPPFLAGS="${CPPFLAGS} -std=c++17"

    # Check that the filesystem library is supported.
    AC_LINK_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <filesystem>],
        [std::filesystem::path cwd = std::filesystem::current_path();]
      )],
      [AC_MSG_RESULT([yes])
       CPP17_SUPPORTED=true],
      [AC_MSG_RESULT([no])
       CPP17_SUPPORTED=false])

    # Restore flags.
    CPPFLAGS="${CPPFLAGS_SAVED}"
])
