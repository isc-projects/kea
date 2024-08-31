AC_DEFUN([AX_ISC_CPP20], [
    AC_MSG_CHECKING(c++20 support)

    # Save flags.
    CPPFLAGS_SAVED="${CPPFLAGS}"
    LIBS_SAVED="${LIBS}"

    # Provide -std=c++20 flag temporarily.
    CPPFLAGS="${CPPFLAGS} -std=c++20"

    # Simulate the definition of std::derived_from.
    AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <concepts>
         template<class Derived, class Base>
           concept derived_from =
             std::is_base_of_v<Base, Derived> &&
             std::is_convertible_v<const volatile Derived*, const volatile Base*>;

          struct BaseClass {};
          struct DerivedClass : BaseClass {};
        ],
        [static_assert(std::derived_from<BaseClass, DerivedClass> == false);
         static_assert(std::derived_from<DerivedClass, BaseClass> == true);]
      )],
      [AC_MSG_RESULT([yes])
       CPP20_SUPPORTED=true],
      [AC_MSG_RESULT([no])
       CPP20_SUPPORTED=false])

    # Restore flags.
    CPPFLAGS="${CPPFLAGS_SAVED}"
])
