
header_file="Music.h"
filter='*.xm'
define_prefix='SONG_'

echo "#ifndef __MUSIC_H__" > ${header_file}
echo "#define __MUSIC_H__" >> ${header_file}

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

# echo "------ MUSIC ------"
# x=0;
# for i in `ls *.xm`; do
#     i=`echo $i | sed -e "s/\./_/g"`
#     echo "case ${x}:"
#     echo "  loadResult = xmp_load_module_from_memory(ctx, (void *)_${i}_start, _${i}_start - _${i}_end);";
#     echo "break;";
#     x=`echo $x + 1 | bc`;
# done



# echo; echo; echo;

# echo "------ SFX ------"
# x=0;
# for i in `ls *.wav`; do
#     i=`echo $i | sed -e "s/\./_/g"`
#     echo "xmp_smix_load_sample_from_memory(ctx, $x, (void *)_${i}_start, _${i}_start - _${i}_end);";
#     x=`echo $x + 1 | bc`;
# done


