make
./output &
sudo taskset -cp 3 $!
