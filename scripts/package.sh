#!/usr/bin/env bash


SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
. $SCRIPT_DIR/ldk_scripts_common.sh

cd $WORKING_DIR


#### Example IPK File
# See https://docs.google.com/document/d/19kJXO3EZ8XCoeporuUUgV_S93AaPbSagza3sAgBILu8/edit#
#    ipkg/home/retrofw/emus/dosbox/dos.png
#    ipkg/home/retrofw/emus/dosbox/dosbox.png
#    ipkg/home/retrofw/apps/gmenu2x/sections/emulators/dosbox.lnk
#    ipkg/home/retrofw/apps/gmenu2x/sections/systems/dos.dosbox.lnk
#    ipkg/debian-binary
#    ipkg/postinst
#    ipkg/control


#### BEGIN IPK CREATION #####
rm -rf ${IPK_WORKING_DIR}
mkdir -p ${IPK_EXEC_DIR}
mkdir -p ${LNK_DESTINATION_DIR}


# Copy binary and launcher image to the execution directory
cp -r ${TARGET} ${LDK_FILES_DIR}/genus.png ${IPK_EXEC_DIR}
#rm ${TARGET}

cp ${LDK_FILES_DIR}/genus.lnk ${LNK_DESTINATION_DIR}

NOW=`date +%s`

sed "s/^Version:.*/Version: ${NOW}/" ${LDK_FILES_DIR}/control > ${IPK_WORKING_DIR}/control
#cp ${LDK_FILES_DIR}/conffiles ${IPK_EXEC_DIR}/

tar --owner=0 --group=0 -czvf ${IPK_WORKING_DIR}/control.tar.gz -C ${IPK_WORKING_DIR} control #conffiles
tar --owner=0 --group=0 -czvf ${IPK_WORKING_DIR}/data.tar.gz -C ${IPK_WORKING_DIR} home/


echo 2.0 > ${IPK_WORKING_DIR}/debian-binary
ar r ${BUILD_DIR}/genus.ipk ${IPK_WORKING_DIR}/control.tar.gz ${IPK_WORKING_DIR}/data.tar.gz ${IPK_WORKING_DIR}/debian-binary

