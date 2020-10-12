#! /bin/zsh

# C files
rm sources.mk

for file in `ls -1 src/*.c`
do
	printf "SRCS+=%s\n" $file >> sources.mk
done

chmod 755 sources.mk

# header files

rm headers.mk

for file in `ls -1 include/**/*.h`
do
	printf "HFILES+=%s\n" $file >> headers.mk
done

for file in `ls -1 macho-headers/**/*.h`
do
	printf "HFILES+=%s\n" $file >> headers.mk
done

chmod 755 headers.mk
