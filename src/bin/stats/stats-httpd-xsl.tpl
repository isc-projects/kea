<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml"
  xmlns:bind10="$xsd_namespace">
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
        <xsl:apply-templates />
      </body>
    </html>
  </xsl:template>
  <xsl:template match="bind10:statistics">
    <table>
      <tr>
	<th>Identifier</th><th>Value</th><th>Description</th>
      </tr>
      <xsl:for-each select="item">
	<tr>
	  <td>
	    <xsl:element name="a">
	      <xsl:attribute name="href"><xsl:value-of select="@uri" /></xsl:attribute>
	      <xsl:value-of select="@identifier" />
	    </xsl:element>
	  </td>
	  <td>
	    <xsl:if test="@value"><xsl:value-of select="@value" /></xsl:if>
	  </td>
	  <td>
	    <xsl:if test="@description"><xsl:value-of select="@description" /></xsl:if>
	  </td>
	</tr>
      </xsl:for-each>
    </table>
  </xsl:template>
</xsl:stylesheet>
