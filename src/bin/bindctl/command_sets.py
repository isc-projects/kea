# Copyright (C) 2012  Internet Systems Consortium.
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

# This file provides a built-in set of 'execute' commands, for common
# functions, such as adding an initial auth server
# These sets must have an associated CommandInfo defined in
# bindctl_main.py.in, in prepare_execute_commands

init_auth_server = [
'!echo adding Authoritative server component',
'config add /Boss/components b10-auth',
'config set /Boss/components/b10-auth/kind needed',
'config set /Boss/components/b10-auth/special auth',
'!echo adding Xfrin component',
'config add /Boss/components b10-xfrin',
'config set /Boss/components/b10-xfrin/address Xfrin',
'config set /Boss/components/b10-xfrin/kind dispensable',
'!echo adding Xfrout component',
'config add /Boss/components b10-xfrout',
'config set /Boss/components/b10-xfrout/address Xfrout',
'config set /Boss/components/b10-xfrout/kind dispensable',
'!echo adding Zone Manager component',
'config add /Boss/components b10-zonemgr',
'config set /Boss/components/b10-zonemgr/address Zonemgr',
'config set /Boss/components/b10-zonemgr/kind dispensable',
'!echo Components added. Please enter "config commit" to finalize initial'+
' setup and run the components.'
]
