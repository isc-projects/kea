UML_FILES = \
	auth-mapped.txt

TEXT_FILES = \
	data-source-classes.txt

BUILT_SOURCES = \
	$(UML_FILES:.txt=.png) \
	$(TEXT_FILES:.txt=.html)

.txt.html:
if HAVE_ASCIIDOC
	$(AM_V_GEN) $(ASCIIDOC) -n $<
else
	@echo "*** a2x (asciidoc) is required to regenerate $(@) ***"; exit 1;
endif

.txt.png:
if HAVE_PLANTUML
	$(AM_V_GEN) $(PLANTUML) $<
else
	@echo "*** a2x (plantuml) is required to regenerate $(@) ***"; exit 1;
endif

CLEANFILES = \
	$(UML_FILES:.txt=.png) \
	$(TEXT_FILES:.txt=.html) \
	$(TEXT_FILES:.txt=.xml)
