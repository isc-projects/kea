noinst_SCRIPTS = sqlite3-difftbl-check.py

# We're going to abuse install-data-local for a pre-install check.
# This is to be considered a short term hack and is expected to be removed
# in a near future version.
install-data-local:
	$(PYTHON) sqlite3-difftbl-check.py \
	$(localstatedir)/$(PACKAGE)/zone.sqlite3
