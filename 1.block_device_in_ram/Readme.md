#1. /proc/devices
    251 rb
#2./proc/partitions 
	major     minor   #blocks  	name
 	251        0        512 	rb
 	251        1        159 	rb1
 	251        2          1 	rb2
 	251        3        192 	rb3
 	251        5         63 	rb5
 	251        6         63 	rb6
 	251        7         31 	rb7
#3. ls -l /dev/rb*
brw-rw---- 1 root disk 251, 0  4月 19 09:58 /dev/rb
brw-rw---- 1 root disk 251, 1  4月 19 09:58 /dev/rb1
brw-rw---- 1 root disk 251, 2  4月 19 09:58 /dev/rb2
brw-rw---- 1 root disk 251, 3  4月 19 09:58 /dev/rb3
brw-rw---- 1 root disk 251, 5  4月 19 09:58 /dev/rb5
brw-rw---- 1 root disk 251, 6  4月 19 09:58 /dev/rb6
brw-rw---- 1 root disk 251, 7  4月 19 09:58 /dev/rb7
#4. sudo dd if=/dev/rb of=dor count=1
1+0 records in
1+0 records out
512 bytes (512 B) copied, 0.000417765 s, 1.2 MB/s
Partition rb's first sector has got copied to dor
    xxd dor
00001b0: 0000 0000 0000 0000 6d75 e536 0000 0000  ........mu.6....
00001c0: 0200 8300 2009 0100 0000 3f01 0000 0000  .... .....?.....
00001d0: 010a 0500 2013 4001 0000 4001 0000 0000  .... .@...@.....
00001e0: 0114 8300 201f 8002 0000 8001 0000 0000  .... ...........
00001f0: 0000 0000 0000 0000 0000 0000 0000 55aa  ..............U.
#5. fdisk -l

Disk /dev/rb: 512 KiB, 524288 bytes, 1024 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x36e5756d

Device     Boot Start   End Sectors   Size Id Type
/dev/rb1            1   319     319 159.5K 83 Linux
/dev/rb2          320   639     320   160K  5 Extended
/dev/rb3          640  1023     384   192K 83 Linux
/dev/rb5          321   447     127  63.5K 83 Linux
/dev/rb6          449   575     127  63.5K 83 Linux
/dev/rb7          577   639      63  31.5K 83 Linux
#6. sudo mkfs -t ext4 -c /dev/rb3
mke2fs 1.42.12 (29-Aug-2014)

Filesystem too small for a journal
Creating filesystem with 192 1k blocks and 24 inodes

Checking for bad blocks (read-only test): done                                  
Allocating group tables: done
Writing inode tables: done
Writing superblocks and filesystem accounting information: done
#7.mkdir /tmp/rb3_filesystem
#8.sudo mount /dev/rb3 /tmp/rb3_filesystem/
   now we can add file in /tmp/rb3_filesystem
#9.df
   /dev/rb3             184       15       157   9% /tmp/rb3_filesystem
