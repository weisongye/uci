cmake .
make clean
rm -f uci
make STRIP=true
gcc cli.c -Wall -Wextra -O0 -g3 -ggdb -static -L. -luci -o uci
gcc example/uci_example.c -Wall -Wextra -O0 -g3 -ggdb -static -I. -L. -luci -o uci-example
mkdir -p etc
ln -s test/config etc/config
