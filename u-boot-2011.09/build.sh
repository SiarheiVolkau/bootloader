#!/bin/bash
set -e

PLATFORM="sun8iw1p1"
MODULE=""
TOOLSPATH=`pwd`
show_help()
{
	printf "\nbuild.sh - Top level build scritps\n"
	echo "Valid Options:"
	echo "  -h  Show help message"
	echo "  -p <platform> platform, e.g. sun4i, sun4i-lite, sun4i_crane"
	printf "  -m <module> module\n\n"
}

calc_pad_size()
{
    local orig_size=$1;
    local align=$2;
    local _size=$((($orig_size + $align - 1) / $align * $align));
    echo "$_size";
}

read_uint32_from_file()
{
    local file=$1;
    local offset=$2;
    local value=$(dd if=$file bs=1 count=4 skip=$offset 2> /dev/null | od -An -t x4 | xargs);
    echo $((16#$value));
}

write_uint32_to_file()
{
    local file=$1;
    local offset=$2;
    local value=$3;
    echo "$value" | \
    xargs printf %.8x | \
    dd conv=swab 2> /dev/null | rev | \
    while read -n 2 code; do printf "\x$code"; done | \
    dd conv=notrunc of=$file bs=1 seek=$offset count=4 2> /dev/null
}

calc_file_checksum()
{
    od -An -t x4 -w4 -v < $1 | while read line; 
    do
        csum=$((($csum + 16#$line) & 16#ffffffff));
        echo "$csum"
    done | tail -n 1
}

while getopts hp:m: OPTION
do
	case $OPTION in
	h) show_help
	;;
	p) PLATFORM=$OPTARG
	;;
	m) MODULE=$OPTARG
	;;
	*) show_help
	;;
esac
done

if [ -z "$PLATFORM" ]; then
	show_help
	exit 1
fi

if [ -z "$MODULE" ]; then
	MODULE="all"
fi

#export PATH=$PATH:${TOOLSPATH}/../buildroot/output/external-toolchain/bin/
make distclean && make $PLATFORM
#cp -rf u-boot.bin  ../brandy/out_source

#NOTE: use only with sunxi u-boot(s)
# prepare uboot file to flash
# 1. make padding
# 2. write sizes in spare_head (20-27 bytes)
# 3. recalculate checksum (12-15 bytes)

addsum_signature=1594518585
filename="u-boot-$PLATFORM.bin";
tmpfile=`mktemp`;
outfile="u-boot-$PLATFORM.prepared.bin";
size=$(stat -L -c %s $filename)
alignment=$(read_uint32_from_file $filename 16)
newsize=$(calc_pad_size $size $alignment)

# make new file with 0xff padding
dd if=/dev/zero bs=1 count=$newsize 2> /dev/null | tr "\000" "\377" >$tmpfile
dd conv=notrunc if=$filename of=$tmpfile 2> /dev/null
write_uint32_to_file $tmpfile 12 $addsum_signature
write_uint32_to_file $tmpfile 20 $newsize
write_uint32_to_file $tmpfile 24 $newsize
#calculate new checksum
checksum=$(calc_file_checksum $tmpfile)
write_uint32_to_file $tmpfile 12 $checksum
cp $tmpfile $outfile
rm $tmpfile
