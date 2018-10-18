.PHONY: Resources.bin
	echo "THERE"
	cd ../creative-engine/tools && make
	../creative-engine/tools/rcomp Resources.r

#ADD_COMPONENT_INCLUDEDIRS=./src ./src/GameState
COMPONENT_ADD_INCLUDEDIRS=src 
#ADD_COMPONENT_INCLUDEDIRS=foo
COMPONENT_PRIV_INCLUDEDIRS=../creative-engine/src ../src/GameState ../src
#COMPONENT_SRCDIRS:=./creative-engine/src .

COMPONENT_EMBED_FILES := Resources.bin
