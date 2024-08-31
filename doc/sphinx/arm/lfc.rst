.. _kea-lfc:

***************
The LFC Process
***************

.. _kea-lfc-overview:

Overview
========

:iscman:`kea-lfc` is a service process that removes redundant information from
the files used to provide persistent storage for the memfile database
backend. This service is written to run as a standalone process.

While :iscman:`kea-lfc` can be started externally, there is usually no need to
do so. :iscman:`kea-lfc` is run on a periodic basis by the Kea DHCP servers.

The process operates on a set of files, using them to receive input and
output of the lease entries and to indicate what stage the process is
in, in the event of an interruption. Currently the caller must supply
names for all of the files.

.. _kea-lfc-usage:

Command-Line Options
====================

:iscman:`kea-lfc` is run as follows:

::

   kea-lfc [-4 | -6] -c config-file -p pid-file -x previous-file -i copy-file -o output-file -f finish-file

The argument ``-4`` or ``-6`` selects the protocol version of the lease
files.

The ``-c`` argument specifies the configuration file. This is required,
but is not currently used by the process.

The ``-p`` argument specifies the PID file. When the :iscman:`kea-lfc` process
starts, it attempts to determine whether another instance of the process
is already running by examining the PID file. If one is already running,
the new process is terminated; if one is not running, Kea writes its PID
into the PID file.

The other filenames specify where the :iscman:`kea-lfc` process should look
for input, write its output, and perform its bookkeeping:

-  ``previous`` — when :iscman:`kea-lfc` starts, this is the result of any
   previous run of :iscman:`kea-lfc`. When :iscman:`kea-lfc` finishes, it is the
   result of this run. If :iscman:`kea-lfc` is interrupted before completing,
   this file may not exist.

-  ``input`` — before the DHCP server invokes :iscman:`kea-lfc`, it moves
   the current lease file here and then calls :iscman:`kea-lfc` with this file.

-  ``output`` — this is the temporary file where :iscman:`kea-lfc` writes the
   leases. Once the file has finished writing, it is moved to the
   ``finish`` file (see below).

-  ``finish`` — this is another temporary file :iscman:`kea-lfc` uses for
   bookkeeping. When :iscman:`kea-lfc` completes writing the ``output`` file, it
   moves the contents to the file of this name. After :iscman:`kea-lfc` finishes deleting the
   other files (``previous`` and ``input``), it moves this file to the ``previous``
   lease file. By moving the files in this fashion, :iscman:`kea-lfc` and
   the DHCP server processes can determine the correct file to use even
   if one of the processes is interrupted before completing its task.

There are several additional arguments, mostly for debugging purposes.
``-d`` sets the logging level to debug. ``-v`` and ``-V`` print out
version stamps, with ``-V`` providing a longer form. ``-h`` prints out
the usage string.
