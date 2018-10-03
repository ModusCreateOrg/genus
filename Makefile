# ESP-IDF Makefile for game project

PROJECT_NAME=Genus
EXTRA_COMPONENT_DIRS=creative-engine src
include $(IDF_PATH)/make/project.mk

rcomp: FORCE
	echo "Building rcomp"
	cd ./creative-engine/tools && make

resources: rcomp FORCE
	echo "Compiling resources"
	cd src && ../creative-engine/tools/rcomp Resources.r

docs:
	cd doxygen && doxygen Doxyfile.in

clean-docs:
	rm -rf docs
	
FORCE:


