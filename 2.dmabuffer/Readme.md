1. print linux version code
   LINUX_VERSION_CODE
2. ida 

	struct idr {  
		struct idr_layer __rcu  *hint;  /* the last layer allocated from */  
		struct idr_layer __rcu  *top;  
		struct idr_layer    *id_free;  
		int         layers; /* only valid w/o concurrent changes */  
		int         id_free_cnt;  
		int         cur;    /* current pos for cyclic allocation */  
		spinlock_t      lock;  
	};

	struct ida {  
		struct idr      idr;  
		struct ida_bitmap   *free_bitmap;  
	}; 
	
	#define IDR_INIT(name)                          \  
	{                                   \  
		.lock           = __SPIN_LOCK_UNLOCKED(name.lock),  \  
	}
   #define IDA_INIT(name)      { .idr = IDR_INIT((name).idr), .free_bitmap = NULL, }  
   #define DEFINE_IDA(name)    struct ida name = IDA_INIT(name)

   DEFINE_IDA仅初始化了spin_lock
   ida_simple_get
   
3. idr Small id to pointer translation service
4. alloc_chrdev_region 动态分配字符设备
5. dev_t
   unsigned int 类型，32位，用于在驱动程序中定义设备编号，高12位为主设备号，低20位为次设备号
   #ls -l /dev/udmabuf0 
   crw------- 1 root root 250, 0  4月 26 14:10 /dev/udmabuf0
   262144000 ==> FA00000  ==> 0xFA (250)  0x00000 (0)
6.
7. drwxr-xr-x 2 root root 0  4月 26 14:10 /sys/class/udmabuf   
   /sys/class/udmabuf/udmabuf0
   dev        power  subsystem       sync_for_cpu     sync_mode    sync_owner  uevent
   phys_addr  size   sync_direction  sync_for_device  sync_offset  sync_size
   
8. insmod udmabuf.ko udmabuf0=1048576
   所以预备分配dma 内存为1M
9. PAGE_SHIFT
#ifdef CONFIG_PAGE_SIZE_4KB
#define PAGE_SHIFT    12
#endif
10. device_create src/drivers/base/core.c
extern struct device *device_create(struct class *cls, struct device *parent,dev_t devt, void *drvdata, const char *fmt, ...)
动态的建立逻辑设备，并对新的逻辑设备类进行相应初始化，将其与函数的第一个参数所代表的逻辑类关联起来，
然后将此逻辑设备加到linux内核系统的设备驱动程序模型中。
函数能够自动在/sys/devices/virtual目录下创建新的逻辑设备目录，在/dev目录下创建于逻辑类对应的设备文件
		/sys/devices/virtual/udmabuf/udmabuf0/
11.
 struct device {
	u64  *dma_mask; /* dma mask (if dma'able device) */
	u64  coherent_dma_mask;/* Like dma_mask, but for
          alloc_coherent mappings as
          not all hardware supports
          64 bit addresses for consistent
          allocations such descriptors. */
 }
12. dma_alloc_coherent
   void *dma_alloc_coherent(struct device *dev,size_t size,dma_addr_t *dma_handle,gfp_t gfp);
13. dma_addr_t
   printk %pad
    DMA addresses types dma_addr_t:

	%pad	0x01234567 or 0x0123456789abcdef

	For printing a dma_addr_t type which can vary based on build options,
	regardless of the width of the CPU data path. Passed by reference.   
14.size_t
    printk %zu 
	size_t			%zu or %zx

 
15. write test
    #sudo dd if=/dev/urandom of=/dev/udmabuf0 bs=1024 count=1024
1024+0 records in
1024+0 records out
1048576 bytes (1.0 MB) copied, 0.0796614 s, 13.2 MB/s
16. read test
sudo dd if=/dev/udmabuf0 of=random.bin
2048+0 records in
2048+0 records out
1048576 bytes (1.0 MB) copied, 0.00212622 s, 493 MB/s
