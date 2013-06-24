UML_FILES = \
	overview.txt \
	auth-local.txt \
	auth-mapped.txt \
	memmgr-mapped-init.txt \
	memmgr-mapped-reload.txt

TEXT_FILES = \
	data-source-classes.txt

devel:	$(UML_FILES:.txt=.png) $(TEXT_FILES:.txt=.html)

.txt.html:
if HAVE_ASCIIDOC
	$(AM_V_GEN) $(ASCIIDOC) -n $<
else
	@echo "*** asciidoc is required to regenerate $(@); creating dummy ***";
	@echo "<html><body><p>" > $@
	@echo "Dummy document. Install asciidoc to correctly generate this file." >> $@
	@echo "</p></body></html>" >> $@
endif

.txt.png:
if HAVE_PLANTUML
	$(AM_V_GEN) $(PLANTUML) $<
else
	@echo "*** plantuml is required to regenerate $(@); creating dummy ***";
	@echo "Dummy image. Install plantuml to correctly generate this file." > $@
endif

CLEANFILES = \
	$(UML_FILES:.txt=.png) \
	$(TEXT_FILES:.txt=.html) \
	$(TEXT_FILES:.txt=.xml)
