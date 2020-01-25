SUBDIRS = src
EXTRA_DIST = autogen.sh LICENSE README.md
ACLOCAL_AMFLAGS = -I m4

man1_MANS = docs/pyflame.man

.PHONY: clean-local
clean-local:
	rm -f core.* pyflame

.PHONY: check
check:
	./runtests.sh -v

.PHONY: tidy
tidy:
	clang-tidy\
	  -p ./compile_commands.json\
-checks='modernize*,performance*,readability*,-modernize-use-trailing-return-type,-readability-implicit-bool-conversion,-readability-magic-numbers,-modernize-avoid-c-arrays'\
	  src/*.cc src/*.h
