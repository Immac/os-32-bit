sudo /sbin/losetup -o 1048576 /dev/loop1 ./hd1.img
sleep 0.1
sudo cp -f kernel.elf /media/immac/1788-59D0/
sleep 0.1
sudo /sbin/losetup -d /dev/loop1