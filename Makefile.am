ACLOCAL_AMFLAGS = -I m4macros ${ACLOCAL_FLAGS}
# ^^^^^^^^ This has to be the first line and cannot come later in this
# Makefile.am due to some bork in some versions of autotools.

SUBDIRS = compatcheck doc . ext src m4macros
USE_LCOV=@USE_LCOV@
LCOV=@LCOV@
GENHTML=@GENHTML@
DISTCHECK_GTEST_CONFIGURE_FLAG=@DISTCHECK_GTEST_CONFIGURE_FLAG@
DISTCHECK_CRYPTO_CONFIGURE_FLAG=@DISTCHECK_CRYPTO_CONFIGURE_FLAG@

DISTCLEANFILES = config.report

# When running distcheck target, do not install the configurations
DISTCHECK_CONFIGURE_FLAGS = --disable-install-configurations

# Use same --with-gtest flag if set
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_GTEST_CONFIGURE_FLAG)

# Keep the crypto backend config
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_CRYPTO_CONFIGURE_FLAG)

dist_doc_DATA = AUTHORS COPYING ChangeLog README

.PHONY: check-valgrind check-valgrind-suppress

check-valgrind:
if HAVE_VALGRIND
	@VALGRIND_COMMAND="$(VALGRIND) -q --gen-suppressions=all --track-origins=yes --num-callers=48 --leak-check=full --fullpath-after=" \
	make -C $(abs_top_builddir) check
else
	@echo "*** Valgrind is required for check-valgrind ***"; exit 1;
endif

check-valgrind-suppress:
if HAVE_VALGRIND
	@VALGRIND_COMMAND="$(VALGRIND) -q --gen-suppressions=all --track-origins=yes --error-exitcode=1 --suppressions=$(abs_top_srcdir)/src/valgrind-suppressions --suppressions=$(abs_top_srcdir)/src/valgrind-suppressions.revisit --num-callers=48 --leak-check=full --fullpath-after=" \
	make -C $(abs_top_builddir) check
else
	@echo "*** Valgrind is required for check-valgrind-suppress ***"; exit 1;
endif

clean-cpp-coverage:
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --directory . --zerocounters; \
		rm -rf $(abs_top_srcdir)/coverage-cpp-html/; \
	else \
		echo "C++ code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-lcov" ; \
	fi

clean-python-coverage:
	@if [ $(USE_PYCOVERAGE) = yes ] ; then \
		rm -f $(abs_top_srcdir)/.coverage ; \
		rm -rf $(abs_top_srcdir)/py-coverage-html ; \
	else \
		echo "Python code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-pycoverage" ; \
	fi

perform-coverage: check

report-cpp-coverage:
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --capture --directory . --output-file all.info ; \
		$(LCOV) --remove all.info \
			c++/4.4\*/\* \
			c++/4.4\*/backward/\* \
			c++/4.4\*/bits/\* \
			c++/4.4\*/ext/\* \
			c++/4.4\*/\*-\*/bits/\* \
			boost/\* \
if HAVE_BOTAN
			botan/\* \
endif
			ext/asio/\* \
			ext/coroutine/\* \
			gtest/\* \
			include/\* \
			log4cplus/\* \
if HAVE_OPENSSL
			openssl/\* \
endif
			unittests/\* \
			\*_unittests.cc \
			\*_unittest.cc \
			\*_unittests.h \
			--output report.info ; \
		sed -e "s|$(abs_top_srcdir)|$(abs_top_builddir)|g" < report.info > report.info.2 ; \
		$(GENHTML) --legend -o $(abs_top_builddir)/coverage-cpp-html report.info.2 ; \
		echo "Generated C++ Code Coverage report in HTML at $(abs_top_builddir)/coverage-cpp-html" ; \
	else \
		echo "C++ code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-lcov" ; \
	fi

report-python-coverage:
	@if [ $(USE_PYCOVERAGE) = yes ] ; then \
		$(PYCOVERAGE) html -d $(abs_top_builddir)/coverage-python-html --omit=src/bin/bind10/tests/,src/bin/bindctl/tests/,src/bin/cfgmgr/tests/,src/bin/cmdctl/tests/,src/bin/loadzone/tests/,src/bin/msgq/tests/,src/bin/stats/tests/,src/bin/tests/,src/bin/xfrin/tests/,src/bin/xfrout/tests/,src/bin/zonemgr/tests/,src/lib/dns/python/tests/,src/lib/dns/tests/,src/lib/python/isc/cc/tests/,src/lib/python/isc/config/tests/,src/lib/python/isc/datasrc/tests/,src/lib/python/isc/log/tests/,src/lib/python/isc/net/tests/,src/lib/python/isc/notify/tests/,src/lib/python/isc/util/tests/ ; \
		echo "Generated Python Code Coverage report in HTML at $(abs_top_builddir)/coverage-python-html" ; \
	else \
		echo "Python code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-pycoverage" ; \
	fi

# for python and c++ test coverage
coverage: clean-coverage perform-coverage report-coverage

clean-coverage: clean-cpp-coverage clean-python-coverage

report-coverage: report-cpp-coverage report-python-coverage

# for static C++ check using cppcheck (when available)
cppcheck:
	cppcheck -I./src/lib -I./src/bin --enable=all --suppressions \
		src/cppcheck-suppress.lst --inline-suppr \
		--quiet --error-exitcode=1 \
		--template '{file}:{line}: check_fail: {message} ({severity},{id})' \
		src

# These steps are necessary during installation
install-exec-hook:
	mkdir -p $(DESTDIR)${localstatedir}/log/
	mkdir -p $(DESTDIR)${localstatedir}/run/${PACKAGE_NAME}

### include tool to generate documentation from log message specifications
### in the distributed tarball:
EXTRA_DIST = tools/system_messages.py
EXTRA_DIST += tools/path_replacer.sh
EXTRA_DIST += tools/mk_cfgrpt.sh

#### include external sources in the distributed tarball:
EXTRA_DIST += ext/asio/README
EXTRA_DIST += ext/asio/README
EXTRA_DIST += ext/asio/asio.hpp
EXTRA_DIST += ext/asio/asio/basic_socket.hpp
EXTRA_DIST += ext/asio/asio/streambuf.hpp
EXTRA_DIST += ext/asio/asio/thread.hpp
EXTRA_DIST += ext/asio/asio/detail/wait_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/resolve_op.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_hppa_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/null_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/noncopyable.hpp
EXTRA_DIST += ext/asio/asio/detail/eventfd_select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/task_io_service_operation.hpp
EXTRA_DIST += ext/asio/asio/detail/service_base.hpp
EXTRA_DIST += ext/asio/asio/detail/task_io_service_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/null_buffers_op.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_handle_write_op.hpp
EXTRA_DIST += ext/asio/asio/detail/thread.hpp
EXTRA_DIST += ext/asio/asio/detail/select_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/event.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_descriptor_service.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_overlapped_op.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_recv_op.hpp
EXTRA_DIST += ext/asio/asio/detail/macos_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/dev_poll_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_service.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/local_free_on_block_exit.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_scheduler.hpp
EXTRA_DIST += ext/asio/asio/detail/signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/resolver_service_base.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_holder.hpp
EXTRA_DIST += ext/asio/asio/detail/dev_poll_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/select_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_arm_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/consuming_buffers.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor_op.hpp
EXTRA_DIST += ext/asio/asio/detail/base_from_completion_cond.hpp
EXTRA_DIST += ext/asio/asio/detail/epoll_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/bind_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/strand_service.hpp
EXTRA_DIST += ext/asio/asio/detail/op_queue.hpp
EXTRA_DIST += ext/asio/asio/detail/win_mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_operation.hpp
EXTRA_DIST += ext/asio/asio/detail/pipe_select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/wince_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/buffered_stream_storage.hpp
EXTRA_DIST += ext/asio/asio/detail/mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor_op_queue.hpp
EXTRA_DIST += ext/asio/asio/detail/win_event.hpp
EXTRA_DIST += ext/asio/asio/detail/select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/io_control.hpp
EXTRA_DIST += ext/asio/asio/detail/buffer_sequence_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_io_service.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_handle_service.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_send_op.hpp
EXTRA_DIST += ext/asio/asio/detail/epoll_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/operation.hpp
EXTRA_DIST += ext/asio/asio/detail/descriptor_ops.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/shared_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/winsock_init.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue_set.hpp
EXTRA_DIST += ext/asio/asio/detail/completion_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_serial_port_service.hpp
EXTRA_DIST += ext/asio/asio/detail/fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/null_event.hpp
EXTRA_DIST += ext/asio/asio/detail/hash_map.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_sync_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/win_tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/win_fd_set_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_null_buffers_op.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/old_win_sdk_compat.hpp
EXTRA_DIST += ext/asio/asio/detail/call_stack.hpp
EXTRA_DIST += ext/asio/asio/detail/weak_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_accept_op.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_x86_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_service.hpp
EXTRA_DIST += ext/asio/asio/detail/null_mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_recvfrom_op.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_event.hpp
EXTRA_DIST += ext/asio/asio/detail/service_id.hpp
EXTRA_DIST += ext/asio/asio/detail/kqueue_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/regex_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_sendto_op.hpp
EXTRA_DIST += ext/asio/asio/detail/push_options.hpp
EXTRA_DIST += ext/asio/asio/detail/null_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_service_base.hpp
EXTRA_DIST += ext/asio/asio/detail/throw_error.hpp
EXTRA_DIST += ext/asio/asio/detail/null_signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_accept_op.hpp
EXTRA_DIST += ext/asio/asio/detail/wrapped_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/object_pool.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_scheduler_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/resolve_endpoint_op.hpp
EXTRA_DIST += ext/asio/asio/detail/array_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/config.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_option.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_overlapped_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/win_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_types.hpp
EXTRA_DIST += ext/asio/asio/detail/null_tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/handler_invoke_helpers.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_send_op.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_null_buffers_op.hpp
EXTRA_DIST += ext/asio/asio/detail/pop_options.hpp
EXTRA_DIST += ext/asio/asio/detail/resolver_service.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_service_base.hpp
EXTRA_DIST += ext/asio/asio/detail/descriptor_read_op.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_connect_op.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue_base.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_recvfrom_op.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_serial_port_service.hpp
EXTRA_DIST += ext/asio/asio/detail/tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/buffer_resize_guard.hpp
EXTRA_DIST += ext/asio/asio/detail/kqueue_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/win_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/deadline_timer_service.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_recv_op.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_op.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/signal_init.hpp
EXTRA_DIST += ext/asio/asio/detail/descriptor_write_op.hpp
EXTRA_DIST += ext/asio/asio/detail/win_signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/reactive_socket_service_base.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_mutex.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/posix_event.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_iocp_io_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/select_reactor.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/posix_tss_ptr.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/task_io_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/dev_poll_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/select_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/eventfd_select_interrupter.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/epoll_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/strand_service.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/winsock_init.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/pipe_select_interrupter.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_iocp_serial_port_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/dev_poll_reactor.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_iocp_io_service.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/strand_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_iocp_socket_service_base.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/timer_queue.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/posix_mutex.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/reactive_serial_port_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/socket_ops.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/socket_select_interrupter.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/posix_thread.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/reactive_descriptor_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/kqueue_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/kqueue_reactor.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_event.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/timer_queue_set.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_tss_ptr.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_iocp_handle_service.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/resolver_service_base.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/win_thread.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/task_io_service.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/throw_error.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/epoll_reactor.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/service_registry.hpp
EXTRA_DIST += ext/asio/asio/detail/impl/descriptor_ops.ipp
EXTRA_DIST += ext/asio/asio/detail/impl/service_registry.ipp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_io_service_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/fd_set_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/task_io_service.hpp
EXTRA_DIST += ext/asio/asio/detail/solaris_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue.hpp
EXTRA_DIST += ext/asio/asio/detail/handler_alloc_helpers.hpp
EXTRA_DIST += ext/asio/asio/detail/scoped_lock.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_handle_read_op.hpp
EXTRA_DIST += ext/asio/asio/detail/service_registry_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/service_registry.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_fd_set_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_ops.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/serial_port_base.hpp
EXTRA_DIST += ext/asio/asio/ssl/context_base.hpp
EXTRA_DIST += ext/asio/asio/ssl/context.hpp
EXTRA_DIST += ext/asio/asio/ssl/context_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_types.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_context_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_stream_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_operation.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_init.hpp
EXTRA_DIST += ext/asio/asio/ssl/basic_context.hpp
EXTRA_DIST += ext/asio/asio/ssl/stream_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/stream.hpp
EXTRA_DIST += ext/asio/asio/ssl/stream_base.hpp
EXTRA_DIST += ext/asio/asio/basic_streambuf.hpp
EXTRA_DIST += ext/asio/asio/serial_port_service.hpp
EXTRA_DIST += ext/asio/asio/error.hpp
EXTRA_DIST += ext/asio/asio/handler_alloc_hook.hpp
EXTRA_DIST += ext/asio/asio/buffers_iterator.hpp
EXTRA_DIST += ext/asio/asio/is_read_buffered.hpp
EXTRA_DIST += ext/asio/asio/buffered_stream_fwd.hpp
EXTRA_DIST += ext/asio/asio/placeholders.hpp
EXTRA_DIST += ext/asio/asio/local/stream_protocol.hpp
EXTRA_DIST += ext/asio/asio/local/detail/impl/endpoint.ipp
EXTRA_DIST += ext/asio/asio/local/detail/endpoint.hpp
EXTRA_DIST += ext/asio/asio/local/datagram_protocol.hpp
EXTRA_DIST += ext/asio/asio/local/connect_pair.hpp
EXTRA_DIST += ext/asio/asio/local/basic_endpoint.hpp
EXTRA_DIST += ext/asio/asio/buffered_stream.hpp
EXTRA_DIST += ext/asio/asio/basic_serial_port.hpp
EXTRA_DIST += ext/asio/asio/datagram_socket_service.hpp
EXTRA_DIST += ext/asio/asio/socket_base.hpp
EXTRA_DIST += ext/asio/asio/io_service.hpp
EXTRA_DIST += ext/asio/asio/ssl.hpp
EXTRA_DIST += ext/asio/asio/basic_socket_iostream.hpp
EXTRA_DIST += ext/asio/asio/basic_io_object.hpp
EXTRA_DIST += ext/asio/asio/basic_socket_streambuf.hpp
EXTRA_DIST += ext/asio/asio/error_code.hpp
EXTRA_DIST += ext/asio/asio/basic_stream_socket.hpp
EXTRA_DIST += ext/asio/asio/read_until.hpp
EXTRA_DIST += ext/asio/asio/basic_streambuf_fwd.hpp
EXTRA_DIST += ext/asio/asio/is_write_buffered.hpp
EXTRA_DIST += ext/asio/asio/basic_datagram_socket.hpp
EXTRA_DIST += ext/asio/asio/buffered_write_stream_fwd.hpp
EXTRA_DIST += ext/asio/asio/basic_deadline_timer.hpp
EXTRA_DIST += ext/asio/asio/socket_acceptor_service.hpp
EXTRA_DIST += ext/asio/asio/raw_socket_service.hpp
EXTRA_DIST += ext/asio/asio/buffered_read_stream.hpp
EXTRA_DIST += ext/asio/asio/time_traits.hpp
EXTRA_DIST += ext/asio/asio/completion_condition.hpp
EXTRA_DIST += ext/asio/asio/posix/basic_stream_descriptor.hpp
EXTRA_DIST += ext/asio/asio/posix/basic_descriptor.hpp
EXTRA_DIST += ext/asio/asio/posix/descriptor_base.hpp
EXTRA_DIST += ext/asio/asio/posix/stream_descriptor_service.hpp
EXTRA_DIST += ext/asio/asio/posix/stream_descriptor.hpp
EXTRA_DIST += ext/asio/asio/write.hpp
EXTRA_DIST += ext/asio/asio/write_at.hpp
EXTRA_DIST += ext/asio/asio/basic_raw_socket.hpp
EXTRA_DIST += ext/asio/asio/serial_port.hpp
EXTRA_DIST += ext/asio/asio/windows/basic_stream_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/basic_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/random_access_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/overlapped_ptr.hpp
EXTRA_DIST += ext/asio/asio/windows/stream_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/random_access_handle_service.hpp
EXTRA_DIST += ext/asio/asio/windows/stream_handle_service.hpp
EXTRA_DIST += ext/asio/asio/windows/basic_random_access_handle.hpp
EXTRA_DIST += ext/asio/asio/read.hpp
EXTRA_DIST += ext/asio/asio/deadline_timer_service.hpp
EXTRA_DIST += ext/asio/asio/buffered_write_stream.hpp
EXTRA_DIST += ext/asio/asio/buffer.hpp
EXTRA_DIST += ext/asio/asio/impl/read_until.ipp
EXTRA_DIST += ext/asio/asio/impl/serial_port_base.hpp
EXTRA_DIST += ext/asio/asio/impl/read_at.ipp
EXTRA_DIST += ext/asio/asio/impl/read.ipp
EXTRA_DIST += ext/asio/asio/impl/error.ipp
EXTRA_DIST += ext/asio/asio/impl/io_service.ipp
EXTRA_DIST += ext/asio/asio/impl/io_service.hpp
EXTRA_DIST += ext/asio/asio/impl/src.hpp
EXTRA_DIST += ext/asio/asio/impl/src.cpp
EXTRA_DIST += ext/asio/asio/impl/read_until.hpp
EXTRA_DIST += ext/asio/asio/impl/serial_port_base.ipp
EXTRA_DIST += ext/asio/asio/impl/write.hpp
EXTRA_DIST += ext/asio/asio/impl/write_at.hpp
EXTRA_DIST += ext/asio/asio/impl/write.ipp
EXTRA_DIST += ext/asio/asio/impl/read.hpp
EXTRA_DIST += ext/asio/asio/impl/write_at.ipp
EXTRA_DIST += ext/asio/asio/impl/error_code.ipp
EXTRA_DIST += ext/asio/asio/impl/read_at.hpp
EXTRA_DIST += ext/asio/asio/strand.hpp
EXTRA_DIST += ext/asio/asio/version.hpp
EXTRA_DIST += ext/asio/asio/basic_socket_acceptor.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver_query.hpp
EXTRA_DIST += ext/asio/asio/ip/address.hpp
EXTRA_DIST += ext/asio/asio/ip/host_name.hpp
EXTRA_DIST += ext/asio/asio/ip/detail/socket_option.hpp
EXTRA_DIST += ext/asio/asio/ip/detail/impl/endpoint.ipp
EXTRA_DIST += ext/asio/asio/ip/detail/endpoint.hpp
EXTRA_DIST += ext/asio/asio/ip/udp.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver_iterator.hpp
EXTRA_DIST += ext/asio/asio/ip/v6_only.hpp
EXTRA_DIST += ext/asio/asio/ip/address_v4.hpp
EXTRA_DIST += ext/asio/asio/ip/resolver_query_base.hpp
EXTRA_DIST += ext/asio/asio/ip/multicast.hpp
EXTRA_DIST += ext/asio/asio/ip/address_v6.hpp
EXTRA_DIST += ext/asio/asio/ip/tcp.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver_entry.hpp
EXTRA_DIST += ext/asio/asio/ip/unicast.hpp
EXTRA_DIST += ext/asio/asio/ip/resolver_service.hpp
EXTRA_DIST += ext/asio/asio/ip/icmp.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_endpoint.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver.hpp
EXTRA_DIST += ext/asio/asio/ip/impl/address.hpp
EXTRA_DIST += ext/asio/asio/ip/impl/address_v4.hpp
EXTRA_DIST += ext/asio/asio/ip/impl/address_v4.ipp
EXTRA_DIST += ext/asio/asio/ip/impl/address_v6.hpp
EXTRA_DIST += ext/asio/asio/ip/impl/address.ipp
EXTRA_DIST += ext/asio/asio/ip/impl/host_name.ipp
EXTRA_DIST += ext/asio/asio/ip/impl/basic_endpoint.hpp
EXTRA_DIST += ext/asio/asio/ip/impl/address_v6.ipp
EXTRA_DIST += ext/asio/asio/handler_invoke_hook.hpp
EXTRA_DIST += ext/asio/asio/read_at.hpp
EXTRA_DIST += ext/asio/asio/buffered_read_stream_fwd.hpp
EXTRA_DIST += ext/asio/asio/system_error.hpp
EXTRA_DIST += ext/asio/asio/deadline_timer.hpp
EXTRA_DIST += ext/asio/asio/stream_socket_service.hpp
EXTRA_DIST += ext/coroutine/coroutine.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = dns++.pc

CLEANFILES = $(abs_top_builddir)/logger_lockfile

# config.h may be included by headers supplied for building user-written
# hooks libraries, so we need to include it in the distribution.
pkginclude_HEADERS = config.h
