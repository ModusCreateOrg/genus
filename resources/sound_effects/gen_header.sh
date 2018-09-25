
header_file="SoundEffects.h"
filter='*.wav'
define_prefix='SFX_'

echo "#ifndef __SOUNDEFFECTS_H__" > ${header_file}
echo "#define __SOUNDEFFECTS_H__" >> ${header_file}

x=0;

for i in `ls ${filter}`; do
    i=`echo $i | sed -e "s/\./_/g"`
    echo "#define ${define_prefix}${x} ($x)" >> ${header_file}
    echo "extern const uint8_t _${i}_start[]   asm(\"_binary_${i}_start\");" >> ${header_file}
    echo "extern const uint8_t _${i}_end[]   asm(\"_binary_${i}_end\");" >> ${header_file}
    x=$((x + 1));
done

echo "#endif" >> ${header_file}

# echo; echo; echo;


echo "------ SFX ------"
x=0;
for i in `ls *.wav`; do
    i=`echo $i | sed -e "s/\./_/g"`
    echo "xmp_smix_load_sample_from_memory(ctx, $x, (void *)_${i}_start, _${i}_start - _${i}_end);";
    x=$((x + 1));
done


