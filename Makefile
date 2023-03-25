hello:
	make -C modules/hello

oops:
	make -C modules/oops

modules: oops hello

perm:
	make -C perm

posttrans:
	make -C posttrans

bin:
	ln -sf `pwd`/perm/perm bin/perm
	ln -sf `pwd`/posttrans/posttrans bin/posttrans

.PHONY: bin perm posttrans modules hello oops
