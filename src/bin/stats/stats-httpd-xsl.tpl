<?xml version="1.0" encoding="UTF-8"?>
<!--
 - Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
 -
 - Permission to use, copy, modify, and/or distribute this software for any
 - purpose with or without fee is hereby granted, provided that the above
 - copyright notice and this permission notice appear in all copies.
 -
 - THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 - REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 - AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 - INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 - LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 - OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 - PERFORMANCE OF THIS SOFTWARE.
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml"
  xmlns:stats="$xsd_namespace">
  <xsl:output method="html" encoding="UTF-8"
    doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"
    doctype-system=" http://www.w3.org/TR/html4/loose.dtd " />
  <xsl:template match="/">
    <html lang="en">
      <head>
        <title>BIND 10 Statistics</title>
        <style type="text/css"><![CDATA[
table {
  border: 1px #000000 solid;
  border-collapse: collapse;
}
td, th {
  padding: 3px 20px;
  border: 1px #000000 solid;
}
td.title {
  text-decoration:underline;
}
]]>
        </style>
      </head>
      <body>
        <h1>BIND 10 Statistics</h1>
        <table>
          <tr>
            <th>Title</th>
            <th>Value</th>
          </tr>
          <xsl:apply-templates />
        </table>
      </body>
    </html>
  </xsl:template>
  $xsl_string
</xsl:stylesheet>
