cmake .
make clean
rm -f uci
make STRIP=true
gcc cli.c -Wall -Wextra -O0 -g3 -ggdb -static -L. -luci -o uci
mkdir -p etc
ln -s test/config etc/config
