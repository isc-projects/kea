SUBDIRS = src
USE_LCOV=@USE_LCOV@
LCOV=@LCOV@
GENHTML=@GENHTML@

DISTCLEANFILES = config.report

# When running distcheck target, do not install the configurations
DISTCHECK_CONFIGURE_FLAGS = --disable-install-configurations

clean-coverage:
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --directory . --zerocounters; \
		rm -rf coverage/; \
	else \
		echo "Code coverage not enabled at configuration time"; \
		exit 1; \
	fi

perform-coverage: check

report-coverage:
	$(LCOV) --capture --directory . --output-file all.info
	$(LCOV) --remove all.info \
			c++/4.4\*/\* \
			c++/4.4\*/backward/\* \
			c++/4.4\*/bits/\* \
			c++/4.4\*/ext/\* \
			c++/4.4\*/\*-\*/bits/\* \
			boost/\* \
			ext/asio/\* \
			gtest/\* \
			usr/include/\* \
			tests/\* \
			unittests/\* \
			\*_unittests.cc \
			\*_unittest.cc \
			\*_unittests.h \
		--output report.info
	$(GENHTML) -o coverage report.info 

coverage: clean-coverage perform-coverage report-coverage

#### include external sources in the distributed tarball:
EXTRA_DIST = ext/asio/README
EXTRA_DIST += ext/asio/asio/local/stream_protocol.hpp
EXTRA_DIST += ext/asio/asio/local/basic_endpoint.hpp
EXTRA_DIST += ext/asio/asio/local/datagram_protocol.hpp
EXTRA_DIST += ext/asio/asio/local/connect_pair.hpp
EXTRA_DIST += ext/asio/asio/windows/basic_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/random_access_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/random_access_handle_service.hpp
EXTRA_DIST += ext/asio/asio/windows/basic_random_access_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/overlapped_ptr.hpp
EXTRA_DIST += ext/asio/asio/windows/stream_handle.hpp
EXTRA_DIST += ext/asio/asio/windows/stream_handle_service.hpp
EXTRA_DIST += ext/asio/asio/windows/basic_stream_handle.hpp
EXTRA_DIST += ext/asio/asio/impl/write.ipp
EXTRA_DIST += ext/asio/asio/impl/read.ipp
EXTRA_DIST += ext/asio/asio/impl/serial_port_base.ipp
EXTRA_DIST += ext/asio/asio/impl/write_at.ipp
EXTRA_DIST += ext/asio/asio/impl/read_at.ipp
EXTRA_DIST += ext/asio/asio/impl/error_code.ipp
EXTRA_DIST += ext/asio/asio/impl/read_until.ipp
EXTRA_DIST += ext/asio/asio/impl/io_service.ipp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_serial_port_service.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_socket_service.hpp
EXTRA_DIST += ext/asio/asio/detail/wince_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/win_event.hpp
EXTRA_DIST += ext/asio/asio/detail/descriptor_ops.hpp
EXTRA_DIST += ext/asio/asio/detail/pipe_select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/task_io_service_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/handler_alloc_helpers.hpp
EXTRA_DIST += ext/asio/asio/detail/pop_options.hpp
EXTRA_DIST += ext/asio/asio/detail/strand_service.hpp
EXTRA_DIST += ext/asio/asio/detail/buffer_resize_guard.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_io_service_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_scheduler.hpp
EXTRA_DIST += ext/asio/asio/detail/kqueue_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/hash_map.hpp
EXTRA_DIST += ext/asio/asio/detail/event.hpp
EXTRA_DIST += ext/asio/asio/detail/buffered_stream_storage.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/deadline_timer_service.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_fd_set_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/service_registry.hpp
EXTRA_DIST += ext/asio/asio/detail/null_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/task_io_service_operation.hpp
EXTRA_DIST += ext/asio/asio/detail/epoll_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/local_free_on_block_exit.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/null_mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor_op.hpp
EXTRA_DIST += ext/asio/asio/detail/fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue_set.hpp
EXTRA_DIST += ext/asio/asio/detail/winsock_init.hpp
EXTRA_DIST += ext/asio/asio/detail/signal_init.hpp
EXTRA_DIST += ext/asio/asio/detail/call_stack.hpp
EXTRA_DIST += ext/asio/asio/detail/operation.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_handle_service.hpp
EXTRA_DIST += ext/asio/asio/detail/fd_set_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/io_control.hpp
EXTRA_DIST += ext/asio/asio/detail/null_signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_ops.hpp
EXTRA_DIST += ext/asio/asio/detail/bind_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_overlapped_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_scheduler_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/consuming_buffers.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_option.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/win_fd_set_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/null_buffers_op.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_holder.hpp
EXTRA_DIST += ext/asio/asio/detail/scoped_lock.hpp
EXTRA_DIST += ext/asio/asio/detail/service_registry_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/base_from_completion_cond.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/solaris_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/epoll_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/push_options.hpp
EXTRA_DIST += ext/asio/asio/detail/win_signal_blocker.hpp
EXTRA_DIST += ext/asio/asio/detail/eventfd_select_interrupter.hpp
EXTRA_DIST += ext/asio/asio/detail/select_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/old_win_sdk_compat.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor_op_queue.hpp
EXTRA_DIST += ext/asio/asio/detail/null_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/buffer_sequence_adapter.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_event.hpp
EXTRA_DIST += ext/asio/asio/detail/thread.hpp
EXTRA_DIST += ext/asio/asio/detail/handler_invoke_helpers.hpp
EXTRA_DIST += ext/asio/asio/detail/null_event.hpp
EXTRA_DIST += ext/asio/asio/detail/service_id.hpp
EXTRA_DIST += ext/asio/asio/detail/socket_types.hpp
EXTRA_DIST += ext/asio/asio/detail/throw_error.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_op.hpp
EXTRA_DIST += ext/asio/asio/detail/win_mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_descriptor_service.hpp
EXTRA_DIST += ext/asio/asio/detail/resolver_service.hpp
EXTRA_DIST += ext/asio/asio/detail/op_queue.hpp
EXTRA_DIST += ext/asio/asio/detail/dev_poll_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/win_thread.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_operation.hpp
EXTRA_DIST += ext/asio/asio/detail/service_base.hpp
EXTRA_DIST += ext/asio/asio/detail/select_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_socket_service.hpp
EXTRA_DIST += ext/asio/asio/detail/wrapped_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/mutex.hpp
EXTRA_DIST += ext/asio/asio/detail/completion_handler.hpp
EXTRA_DIST += ext/asio/asio/detail/noncopyable.hpp
EXTRA_DIST += ext/asio/asio/detail/task_io_service.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/win_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/win_tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/kqueue_reactor.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue_base.hpp
EXTRA_DIST += ext/asio/asio/detail/win_iocp_io_service.hpp
EXTRA_DIST += ext/asio/asio/detail/gcc_x86_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/posix_tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/detail/macos_fenced_block.hpp
EXTRA_DIST += ext/asio/asio/detail/dev_poll_reactor_fwd.hpp
EXTRA_DIST += ext/asio/asio/detail/timer_queue.hpp
EXTRA_DIST += ext/asio/asio/detail/reactive_serial_port_service.hpp
EXTRA_DIST += ext/asio/asio/detail/null_tss_ptr.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_stream_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_operation.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_init.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_context_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/detail/openssl_types.hpp
EXTRA_DIST += ext/asio/asio/ssl/stream.hpp
EXTRA_DIST += ext/asio/asio/ssl/stream_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/context_base.hpp
EXTRA_DIST += ext/asio/asio/ssl/context.hpp
EXTRA_DIST += ext/asio/asio/ssl/context_service.hpp
EXTRA_DIST += ext/asio/asio/ssl/basic_context.hpp
EXTRA_DIST += ext/asio/asio/ssl/stream_base.hpp
EXTRA_DIST += ext/asio/asio/posix/stream_descriptor.hpp
EXTRA_DIST += ext/asio/asio/posix/stream_descriptor_service.hpp
EXTRA_DIST += ext/asio/asio/posix/basic_stream_descriptor.hpp
EXTRA_DIST += ext/asio/asio/posix/basic_descriptor.hpp
EXTRA_DIST += ext/asio/asio/posix/descriptor_base.hpp
EXTRA_DIST += ext/asio/asio/ip/detail/socket_option.hpp
EXTRA_DIST += ext/asio/asio/ip/v6_only.hpp
EXTRA_DIST += ext/asio/asio/ip/address_v4.hpp
EXTRA_DIST += ext/asio/asio/ip/address_v6.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver.hpp
EXTRA_DIST += ext/asio/asio/ip/multicast.hpp
EXTRA_DIST += ext/asio/asio/ip/unicast.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver_iterator.hpp
EXTRA_DIST += ext/asio/asio/ip/host_name.hpp
EXTRA_DIST += ext/asio/asio/ip/resolver_query_base.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_endpoint.hpp
EXTRA_DIST += ext/asio/asio/ip/resolver_service.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver_entry.hpp
EXTRA_DIST += ext/asio/asio/ip/address.hpp
EXTRA_DIST += ext/asio/asio/ip/tcp.hpp
EXTRA_DIST += ext/asio/asio/ip/basic_resolver_query.hpp
EXTRA_DIST += ext/asio/asio/ip/udp.hpp
EXTRA_DIST += ext/asio/asio/ip/icmp.hpp
EXTRA_DIST += ext/asio/asio/error.hpp
EXTRA_DIST += ext/asio/asio/basic_socket.hpp
EXTRA_DIST += ext/asio/asio/buffered_stream.hpp
EXTRA_DIST += ext/asio/asio/system_error.hpp
EXTRA_DIST += ext/asio/asio/basic_io_object.hpp
EXTRA_DIST += ext/asio/asio/read_at.hpp
EXTRA_DIST += ext/asio/asio/basic_raw_socket.hpp
EXTRA_DIST += ext/asio/asio/serial_port_service.hpp
EXTRA_DIST += ext/asio/asio/basic_stream_socket.hpp
EXTRA_DIST += ext/asio/asio/placeholders.hpp
EXTRA_DIST += ext/asio/asio/basic_deadline_timer.hpp
EXTRA_DIST += ext/asio/asio/thread.hpp
EXTRA_DIST += ext/asio/asio/buffered_write_stream_fwd.hpp
EXTRA_DIST += ext/asio/asio/datagram_socket_service.hpp
EXTRA_DIST += ext/asio/asio/handler_invoke_hook.hpp
EXTRA_DIST += ext/asio/asio/is_read_buffered.hpp
EXTRA_DIST += ext/asio/asio/buffer.hpp
EXTRA_DIST += ext/asio/asio/basic_socket_acceptor.hpp
EXTRA_DIST += ext/asio/asio/write_at.hpp
EXTRA_DIST += ext/asio/asio/completion_condition.hpp
EXTRA_DIST += ext/asio/asio/raw_socket_service.hpp
EXTRA_DIST += ext/asio/asio/socket_base.hpp
EXTRA_DIST += ext/asio/asio/serial_port.hpp
EXTRA_DIST += ext/asio/asio/error_code.hpp
EXTRA_DIST += ext/asio/asio/basic_serial_port.hpp
EXTRA_DIST += ext/asio/asio/version.hpp
EXTRA_DIST += ext/asio/asio/deadline_timer_service.hpp
EXTRA_DIST += ext/asio/asio/io_service.hpp
EXTRA_DIST += ext/asio/asio/buffered_read_stream.hpp
EXTRA_DIST += ext/asio/asio/streambuf.hpp
EXTRA_DIST += ext/asio/asio/basic_datagram_socket.hpp
EXTRA_DIST += ext/asio/asio/basic_streambuf.hpp
EXTRA_DIST += ext/asio/asio/write.hpp
EXTRA_DIST += ext/asio/asio/strand.hpp
EXTRA_DIST += ext/asio/asio/basic_socket_iostream.hpp
EXTRA_DIST += ext/asio/asio/buffered_stream_fwd.hpp
EXTRA_DIST += ext/asio/asio/basic_socket_streambuf.hpp
EXTRA_DIST += ext/asio/asio/ssl.hpp
EXTRA_DIST += ext/asio/asio/deadline_timer.hpp
EXTRA_DIST += ext/asio/asio/buffers_iterator.hpp
EXTRA_DIST += ext/asio/asio/handler_alloc_hook.hpp
EXTRA_DIST += ext/asio/asio/buffered_write_stream.hpp
EXTRA_DIST += ext/asio/asio/read.hpp
EXTRA_DIST += ext/asio/asio/serial_port_base.hpp
EXTRA_DIST += ext/asio/asio/stream_socket_service.hpp
EXTRA_DIST += ext/asio/asio/time_traits.hpp
EXTRA_DIST += ext/asio/asio/read_until.hpp
EXTRA_DIST += ext/asio/asio/is_write_buffered.hpp
EXTRA_DIST += ext/asio/asio/buffered_read_stream_fwd.hpp
EXTRA_DIST += ext/asio/asio/socket_acceptor_service.hpp
EXTRA_DIST += ext/asio/asio.hpp

## include the guide in tarball, later will include the other parts there
## but they cleanup.
EXTRA_DIST += doc/guide/bind10-guide.css
EXTRA_DIST += doc/guide/bind10-guide.html
EXTRA_DIST += doc/guide/bind10-guide.xml
