hello:
	make -C modules/hello

oops:
	make -C modules/oops

modules: oops hello

perm:
	make -C perm
	#mv perm/perm bin/

bin:
	find -executable -not -type d -exec mv bin

.PHONY: bin perm modules hello oops
