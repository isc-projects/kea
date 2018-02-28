AC_DEFUN([AX_ISC_CPP11], [

CXX_SAVED=$CXX
feature=
for retry in "none" "--std=c++11" "--std=c++0x" "--std=c++1x" "fail"; do
	if test "$retry" = "fail"; then
		AC_MSG_ERROR([$feature (a C++11 feature) is not supported])
	fi
	if test "$retry" != "none"; then
		AC_MSG_WARN([unsupported C++11 feature])
		AC_MSG_NOTICE([retrying by adding $retry to $CXX])
		CXX="$CXX_SAVED $retry"
		AC_MSG_CHECKING($retry support)
		AC_COMPILE_IFELSE(
			[AC_LANG_PROGRAM(
				[],
				[int myincr = 1;])],
			[AC_MSG_RESULT([yes])],
			[AC_MSG_RESULT([no])
			 continue])
	fi

	AC_MSG_CHECKING(std::unique_ptr support)
	feature="std::unique_ptr"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[#include <memory>],
			[std::unique_ptr<int> a;])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(cbegin/cend support)
	feature="cbegin/cend"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[#include <string>],
			[const std::string& s = "abcd";
			 unsigned count = 0;
			 for (std::string::const_iterator i = s.cbegin();
			      i != s.cend(); ++i)
				if (*i == 'b')
					++count;])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(final method support)
	feature="final method"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[class Foo {
			 public:
			 	virtual ~Foo() {};
				virtual void bar() final;
			 };],[])],
		 [AC_MSG_RESULT([yes])],
		 [AC_MSG_RESULT([no])
		  continue])

	AC_MSG_CHECKING(override method support)
	feature="override method"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[class Foo {
			 public:
			 	virtual ~Foo() {};
				virtual void foobar();
			 };
			 class Bar : public Foo {
                         public:
			 	virtual ~Bar() {};
				virtual void foobar() override;
			 };],[])],
		 [AC_MSG_RESULT([yes])],
		 [AC_MSG_RESULT([no])
		  continue])

	AC_MSG_CHECKING(aggregate initialization support)
	feature="aggregate initialization"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[#include <vector>],
			[std::vector<int> foo = { 1, 2, 3};])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(variadic template support)
	feature="variadic template"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[template<typename ... Args>
			 struct A {
			 void foo(Args... myargs) { return; };
			 };],
			 [A<> a;
			  a.foo();])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(static_assert support)
	feature="static_assert"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[static_assert(1 + 1 == 2, "");],
			[])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(template alias)
	feature="template alias"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[template<int i>
			 class I {
			 public: int get() { return i; };
			 };
			 using Zero = I<0>;],
			[Zero Z;
			 return Z.get();])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(constexpr support)
	feature="constexpr"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[#include <string>
			 typedef char const* const Tag;
			 constexpr Tag FOOBAR = "FOOBAR";],
			[const std::string foobar(FOOBAR);
			 return static_cast<int>(foobar.length());])],
		[AC_MSG_RESULT([yes])],
		[AC_MSG_RESULT([no])
		 continue])

	AC_MSG_CHECKING(lambda support)
	feature="lambda"
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[],
			[auto myincr = [[]](int x) { return x + 1; };])],
		[AC_MSG_RESULT([yes])
		 break],
		[AC_MSG_RESULT([no])
		 continue])
done

])dnl AX_ISC_RPATH
