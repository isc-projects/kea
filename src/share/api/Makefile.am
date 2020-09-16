# list of api files
api_files =
include $(srcdir)/api_files.mk

EXTRA_DIST = api_files.mk
EXTRA_DIST += README
EXTRA_DIST += _template.json
EXTRA_DIST += generate-templates
EXTRA_DIST += generate-api-files
EXTRA_DIST += $(api_files)

install-data-local:
	mkdir -p $(DESTDIR)$(datarootdir)/${PACKAGE_NAME}/api
	cp $(api_files) $(DESTDIR)$(datarootdir)/${PACKAGE_NAME}/api

uninstall-local:
	rm -rf $(DESTDIR)$(datarootdir)/${PACKAGE_NAME}/api
