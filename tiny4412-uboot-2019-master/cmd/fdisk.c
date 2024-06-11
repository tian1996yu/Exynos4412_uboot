#include <common.h>
#include <command.h>
#include <console.h>
#include <mmc.h>
#include <sparse_format.h>
#include <image-sparse.h>
#define		BLOCK_SIZE			512
#define		BLOCK_END			0xFFFFFFFF
#define		_10MB				(10*1024*1024)
#define		_100MB				(100*1024*1024)
#define		_8_4GB				(1023*254*63)
	
#define		SYSTEM_PART_SIZE		(300*1024*1024)
#define		USER_DATA_PART_SIZE		(300*1024*1024)
#define		CACHE_PART_SIZE			(300*1024*1024)

#define		CHS_MODE			0
#define		LBA_MODE			!(CHS_MODE)

typedef struct
{
	int		C_start;
	int		H_start;
	int		S_start;

	int		C_end;
	int		H_end;
	int		S_end;

	int		available_block;
	int		unit;
	int		total_block_count;
	int		addr_mode;	// LBA_MODE or CHS_MODE
} SDInfo;

typedef struct
{
	unsigned char bootable;
	unsigned char partitionId;

	int		C_start;
	int		H_start;
	int		S_start;

	int		C_end;
	int		H_end;
	int		S_end;

	int		block_start;
	int		block_count;
	int		block_end;
} PartitionInfo;
/*
static cmd_tbl_t cmd_mmc[] = {
    U_BOOT_CMD_MKENT(info, 1, 0, do_fdisk, "", ""),
	
}
static int do_mmcinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]){
	
	return 1;
}
*/
/////////////////////////////////////////////////////////////////
int get_mmc_block_count(char *device_name)      //得到扇区的数量
{
	int rv;
	struct mmc *mmc;
	int block_count = 0;
	int dev_num;

	dev_num = simple_strtoul(device_name, NULL, 0);
	
	mmc = find_mmc_device(dev_num);
	if (!mmc)
	{
		printf("mmc/sd device is NOT founded.\n");
		return -1;
	}	
	
	block_count = mmc->capacity * (mmc->read_bl_len / BLOCK_SIZE);
	printf("block_count = %d\n", block_count);	
	printf("mmc->capacity = %d\n", mmc->capacity);	
	printf("mmc->read_bl_len = %d\n",mmc->read_bl_len);	
   //printf("block_count = %d\n", block_count);
	return block_count;
}

static int do_fdisk(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	puts("do_fdisk ........\n");	 
	if ( argc == 3 || argc ==6 )
	{
		if (strcmp(argv[1], "-c") == 0 ){
			//printf("argc == 3\n");
			return 0;
		}
		else if (strcmp(argv[1], "-p") == 0 ){
			//printf("argc == 3");
			//printf("-p\n");
	       //	printf("block_count == %x\n",get_mmc_block_count(argv[2]));
			//return print_mmc_part_info(argc, argv);
			return get_mmc_block_count(argv[2]);
			
		}
	}
	puts("do_fdisk  end........\n");	 
	return   1;	
}
/*在新uboot中添加fdisk命令*/
U_BOOT_CMD(
	fdisk, 6, 0, do_fdisk,
	"fdisk for sd/mmc.\n",
	"-p <device_num>\t- print partition information\n"
	"fdisk -c <device_num> [<sys. part size(MB)> <user data part size> <cache part size>]\n"
			"\t- create partition\n"
);
