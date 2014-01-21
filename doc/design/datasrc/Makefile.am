UML_FILES = \
	overview.txt \
	auth-local.txt \
	auth-mapped.txt \
	memmgr-mapped-init.txt \
	memmgr-mapped-reload.txt

TEXT_FILES = \
	data-source-classes.txt

devel: $(patsubst %.txt, %.png, $(UML_FILES)) $(patsubst %.txt, %.html, $(TEXT_FILES))

.txt.html:
if HAVE_ASCIIDOC
	$(AM_V_GEN) $(ASCIIDOC) -n $<
else
	@echo "*** asciidoc is required to regenerate $(@) ***"; exit 1;
endif

.txt.png:
if HAVE_PLANTUML
	$(AM_V_GEN) $(PLANTUML) $<
else
	@echo "*** plantuml is required to regenerate $(@) ***"; exit 1;
endif

CLEANFILES = \
	$(patsubst %.txt, %.png, $(UML_FILES)) \
	$(patsubst %.txt, %.html, $(TEXT_FILES)) \
	$(patsubst %.txt, %.xml, $(TEXT_FILES))
