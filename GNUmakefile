
SVN=$(shell git log --grep=git-svn-id -1 | awk '/git-svn-id/{v=$$2;sub(".*@","",v);print v+0;}')

REMOTE=$(shell git show-ref --hash --head origin/master putty | head -1)
FORKED=$(shell git merge-base $(REMOTE) HEAD)
PVER=$(shell git describe --tags --abbrev=0 | sed 's/putty-//')
MDIF=$(shell git describe --tags --long $(FORKED) | sed 's/.*-\([0-9]*\)-g.*/\1/' )
RDIF=$(shell git log --oneline --format=%h $(FORKED)..HEAD | wc -l )
CDATE=$(shell git log -1 --format='%h %ci' | awk '{print $$2;}')
FDATE=$(shell git log -1 --format='%h %ci' $(FORKED) | awk '{print $$2;}')

BVER=$(shell git describe --tags --abbrev=0 | sed -e 's/putty-//' -e 's/\([0-9]*\)\.\([0-9]*\)/\1,\2,'"$(MDIF),$(RDIF)"'/')
VER=$(PVER).$(MDIF) $(FDATE) +RdB-$(RDIF) $(CDATE)
SVER=$(PVER).$(MDIF)+RdB-$(RDIF)
J99=-j99
CNF=$(J99) COMPAT="-DVERNAME='$(VER)' -DSHORTVERNAME='$(SVER)'" RCFL="-DVERNAME='$(VER)' -DBINARY_VERSION='$(BVER)'"

WINTGT=/home/samba/public
WINTOOLPATH32=i686-w64-mingw32-
WINTOOLPATH64=x86_64-w64-mingw32-

all: unix-all windows-all

complete: all doc-all icons-all

pterm: unix-pterm

putty: unix-putty windows-putty

# All cleanup

clean: unix/makefile windows/Makefile.cyg
	make -C unix -f Makefile.gtk clean
	make -C windows -f Makefile.cyg clean
	make -C doc clean
	make -C icons clean
	make -C macosx clean

doc-all:
	make -C doc

# NB: make install in here changes files in other directories ... those files
# are generated. BUT mkfiles.pl *requires* them to exist.
icons-all:
	make -C icons

# Unix (Linux) compile

unix-all: unix/makefile
	make $(CNF) -C unix -f Makefile.gtk

unix-putty: unix/makefile
	make $(CNF) -C unix -f Makefile.gtk putty

unix-pterm: unix/makefile
	make $(CNF) -C unix -f Makefile.gtk pterm

unix/makefile: mkfiles.pl
	./mkfiles.pl

# WINDOWS Cross compile

windows-all: windows/Makefile.cyg
	make TOOLPATH=$(WINTOOLPATH32) $(CNF) -C windows -f Makefile.cyg

windows-putty: windows/Makefile.cyg
	make TOOLPATH=$(WINTOOLPATH32) $(CNF) -C windows -f Makefile.cyg putty.exe

windows-x64: windows/Makefile.cyg
	make TOOLPATH=$(WINTOOLPATH64) $(CNF) -C windows -f Makefile.cyg

windows/Makefile.vc: mkfiles.pl
	./mkfiles.pl

windows/Makefile.cyg: mkfiles.pl
	./mkfiles.pl

push:
	git push git@github.com:rdebath/PuTTY.git $(PUSHARGS) \
		origin/master:refs/heads/master \
		+putty-rdb `git tag | grep ^0.`
	-git fetch origin
	-git fetch rdebath

# WINDOWS Compile archive
zip: windows/Makefile.vc
	-rm $(WINTGT)/putty.zip
	rsync -vrc --delete --delete-excluded \
		--exclude /.pc --exclude /.git\* \
		--exclude='*.orig' --exclude='*.rej' \
		--exclude=unix/plink --exclude=unix/pscp \
		--exclude=unix/psftp --exclude=unix/pterm \
		--exclude=unix/putty --exclude=unix/puttygen \
		--exclude=unix/puttytel \
		--exclude='*.obj' \
		--exclude='*.rsp' --exclude='*.res' \
		--exclude='*.map' --exclude='*.o' \
		--exclude='*.zip' --exclude='*.tgz' \
		--exclude='x' --exclude='x?' \
		. $(WINTGT)/putty

	cd $(WINTGT)/putty ; \
	zip -Dq9rp \
		$(WINTGT)/putty.zip . \
		-x \*.obj \*.exe \*.rsp \*.map \*.res


realclean: clean
	@echo : Removing more generated files.
	@# Recipe
	@-rm -f charset/sbcsdat.c
	@-rm -f empty.h
	@-rm -f Makefile.am
	@-rm -f macosx/Makefile
	@-rm -f unix/Makefile.am
	@-rm -f unix/Makefile.ux
	@-rm -f unix/Makefile.gtk
	@# windows
	@-rm -f windows/Makefile.cyg
	@-rm -f windows/Makefile.vc
	@-rm -f windows/Makefile.bor
	@-rm -f windows/Makefile.lcc
	@-rm -rf windows/VS2010
	@-rm -rf windows/VS2012
	@-rm -rf windows/MSVC
	@-rm -rf windows/DEVCPP
	@# autoconf clutter
	@-rm -rf .deps/
	@-rm -rf charset/.deps/
	@-rm -rf unix/.deps/
	@-rm -f Makefile
	@-rm -f Makefile.in
	@-rm -f aclocal.m4
	@-rm -f ar-lib
	@-rm -f compile
	@-rm -f config.log
	@-rm -f config.status
	@-rm -f configure
	@-rm -f depcomp
	@-rm -f install-sh
	@-rm -f missing
	@-rm -f stamp-h1
	@-rm -f uxconfig.h
	@-rm -f uxconfig.in
