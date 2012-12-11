<?xml version="1.0" encoding="UTF-8"?>
<schema targetNamespace="$xsd_namespace"
        xmlns="http://www.w3.org/2001/XMLSchema"
        xmlns:bind10="$xsd_namespace">
  <annotation>
    <documentation>XML schema of statistics data in BIND 10</documentation>
  </annotation>
  <element name="statistics">
    <annotation><documentation>A set of statistics data</documentation></annotation>
    <complexType>
      <sequence>
        <element name="item" maxOccurs="unbounded" minOccurs="1">
          <complexType>
	    <attribute name="identifier" type="string" use="required">
            <annotation>
              <appinfo>Identifier</appinfo>
              <documentation>Identifier of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="value" type="string" use="optional">
            <annotation>
              <appinfo>Value</appinfo>
              <documentation>Value of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="owner" type="string" use="required">
            <annotation>
              <appinfo>Owner</appinfo>
              <documentation>Owner module name</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="uri" type="anyURI" use="required">
            <annotation>
              <appinfo>URI</appinfo>
              <documentation>URI of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="name" type="string" use="required">
            <annotation>
              <appinfo>Name</appinfo>
              <documentation>Name of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="type" use="required">
  	    	<annotation>
  	    	  <appinfo>Type</appinfo>
  	    	  <documentation>Type of item</documentation>
  	    	</annotation>
  	    	<simpleType>
  	    	  <restriction base="token">
  	    	    <enumeration value="boolean"/>
  	    	    <enumeration value="integer"/>
  	    	    <enumeration value="real"/>
  	    	    <enumeration value="string"/>
  	    	    <enumeration value="map"/>
  	    	    <enumeration value="list"/>
  	    	    <enumeration value="named_set"/>
  	    	    <enumeration value="any"/>
  	    	  </restriction>
  	    	</simpleType>
  	    </attribute>
  	    <attribute name="description" type="string" use="optional">
            <annotation>
              <appinfo>Description</appinfo>
              <documentation>Description of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="title" type="string" use="optional">
            <annotation>
              <appinfo>Title</appinfo>
              <documentation>Title of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="optional" type="boolean" use="optional">
            <annotation>
              <appinfo>Optional</appinfo>
              <documentation>The item is optional or not</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="default" type="string" use="optional">
            <annotation>
              <appinfo>Default</appinfo>
              <documentation>Default of item</documentation>
            </annotation>
  	    </attribute>
  	    <attribute name="format" type="string" use="optional">
            <annotation>
              <appinfo>Format</appinfo>
              <documentation>Format of item value</documentation>
            </annotation>
  	    </attribute>
          </complexType>
        </element>
      </sequence>
    </complexType>
  </element>
</schema>
