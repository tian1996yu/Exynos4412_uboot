#include <common.h>
#include <command.h>
#include <console.h>
#include <mmc.h>
#include <sparse_format.h>
#include <image-sparse.h>

/*
static cmd_tbl_t cmd_mmc[] = {
    U_BOOT_CMD_MKENT(info, 1, 0, do_fdisk, "", ""),
	
}
static int do_mmcinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]){
	
	return 1;
}
*/
static int do_fdisk(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	puts("do_fdisk ........\n");
	return1   1;	
}
/*在新uboot中添加fdisk命令*/
U_BOOT_CMD(
	fdisk, 1, 0, do_fdisk,
	"fdisk for sd/mmc.\n",
	"-p <device_num>\t- print partition information\n"
	"fdisk -c <device_num> [<sys. part size(MB)> <user data part size> <cache part size>]\n"
			"\t- create partition\n"
);
