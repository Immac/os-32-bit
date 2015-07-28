sudo /sbin/losetup -o 1048576 /dev/loop1 ./hd1.img
sudo cp os-32/kernel.elf /hd1
sudo /sbin/losetup -d /dev/loop1