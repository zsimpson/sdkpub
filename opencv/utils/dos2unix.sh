for i in `find .. -name '*.c*'; find .. -name '*.h*'`;do
    perl dos2unix.pl $i
done
