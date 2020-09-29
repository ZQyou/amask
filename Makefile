
.PHONY: all clean

all:
	cd src && $(MAKE)
	cd src/placement && $(MAKE)
clean:
	cd src && $(MAKE) clean
	cd src/placement && $(MAKE) clean
cleanall:
	cd src && $(MAKE) cleanall
