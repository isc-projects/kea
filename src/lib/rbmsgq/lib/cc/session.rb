# Copyright (C) 2009  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

require 'socket'

class CC
class ProtocolError < Exception ; end
end

class CC
class Session
  attr_reader :socket
  attr_reader :lname

  #
  # :host => host to connect to (defaults to "127.0.0.1")
  # :port => port to connect to (defaults to 9913)
  #
  def initialize(args = {})
    @socket = nil      # TCP socket.
    @lname = nil       # local name, or nil if not connected.
    @recvbuffer = ""   # data buffer for partial reads.
    @recvlength = nil  # if non-nil, we have a length to fill buffer to.
    @sendbuffer = ""   # pending output data.
    @sequence = "a"    # per message sequence id, always unique

    options = {
      :host => "127.0.0.1",
      :port => 9912
    }.merge(args)

    @socket = TCPSocket.new(options[:host], options[:port])

    #
    # Get our local name.
    #
    sendmsg({ :type => :getlname })
    msg = recvmsg(false)
    @lname = msg["lname"]
    if @lname.nil?
      raise CC::ProtocolError, "Could not get local name"
    end
    CC::set_utf8(@lname)
  end

  #
  # Send a message to the controller.  The item to send can either be a
  # CC::Message object, or a Hash.  If a Hash, it will be internally
  # converted to a CC::Message before transmitting.
  #
  # A return value of true means the entire message was not
  # transmitted, and a call to send_pending will have to be
  # made to send remaining data.  This should only happen when
  # the socket is in non-blocking mode.
  #
  def sendmsg(msg)
    if msg.is_a?(Hash)
      msg = CC::Message.new(msg)
    end

    unless msg.is_a?(CC::Message)
      raise ArgumentError, "msg is not a CC::Message or a Hash"
    end

    wire = msg.to_wire
    @sendbuffer << [wire.length].pack("N")
    @sendbuffer << wire

    send_pending
  end

  #
  # Send as much data as we can.  
  def send_pending
    return false if @sendbuffer.length == 0
    sent = @socket.send(@sendbuffer, 0)
    @sendbuffer = @sendbuffer[sent .. -1]
    @sendbuffer.length == 0 ? true : false
  end

  def recvmsg(nonblock = true)
    data = receive_full_buffer(nonblock)
    if data
      CC::Message::from_wire(data)
    else
      nil
    end
  end

  def group_subscribe(group, instance = "*", subtype = "normal")
    sendmsg({ :type => "subscribe",
              :group => group,
              :instance => instance,
              :subtype => subtype,
            })
  end

  def group_unsubscribe(group, instance = "*")
    sendmsg({ :type => "unsubscribe",
              :group => group,
              :instance => instance,
            })
  end

  def group_sendmsg(msg, group, instance = "*", to = "*")
    seq = next_sequence
    sendmsg({ :type => "send",
              :from => @lname,
              :to => to,
              :group => group,
              :instance => instance,
              :seq => seq,
              :msg => CC::Message.to_wire(msg),
            })
    seq
  end

  def group_replymsg(routing, msg)
    seq = next_sequence
    sendmsg({ :type => "send",
              :from => @lname,
              :to => routing["from"],
              :group => routing["group"],
              :instance => routing["instance"],
              :seq => seq,
              :reply => routing["seq"],
              :msg => CC::Message.to_wire(msg),
            })
    seq
  end

  def group_recvmsg(nonblock = true)
    msg = recvmsg(nonblock)
    return nil if msg.nil?
    data = CC::Message::from_wire(msg["msg"])
    msg.delete("msg")
    return [data, msg]
  end

  private

  def next_sequence
    @sequence.next!
  end

  #
  # A rather tricky function.  If we have something waiting in our buffer,
  # and it will satisfy the current request, we will read it all in.  If
  # not, we will read only what we need to satisfy a single message.
  #
  def receive_full_buffer(nonblock)
    # read the length prefix if we need it still.
    if @recvlength.nil?
      length = 4
      length -= @recvbuffer.length
      data = nil
      begin
        if nonblock
          data = @socket.recv_nonblock(length)
        else
          data = @socket.recv(length)
        end
        rescue Errno::EINPROGRESS
        rescue Errno::EAGAIN
      end
      return nil if data == nil
      @recvbuffer += data
      return nil if @recvbuffer.length < 4
      @recvlength = @recvbuffer.unpack('N')[0]
      @recvbuffer = ""
      CC::set_binary(@recvbuffer)
    end

    #
    # we have a length target.  Loop reading data until we get enough to
    # fill our buffer.
    #
    length = @recvlength - @recvbuffer.length
    while (length > 0) do
      data = nil
      begin
        if nonblock
          data = @socket.recv_nonblock(length)
        else
          data = @socket.recv(length)
        end
        rescue Errno::EINPROGRESS
        rescue Errno::EAGAIN
      end
      return nil if data == 0 # blocking I/O
      @recvbuffer += data
      length -= data.length
    end

    data = @recvbuffer
    @recvbuffer = ""
    @recvlength = nil
    data
  end

end # class Session
end # class CC
