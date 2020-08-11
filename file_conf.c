#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXNAME 64
#define MAXVERSION 64
#define MAXFILENUM 10
#define MAXBLOCKCRC 32
#define MAXFACTORYNAME 64

int i;

static const unsigned int dsyslib_crc32_table[ 256 ] =
{
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 
    0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd,
    0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,	0x1adad47d, 
    0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
    0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4,
    0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c, 
    0xdbbbc9d6, 0xacbcf940, 0x32d86ce3,	0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac,
    0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599,	0xb8bda50f, 
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab,
    0xb6662d3d, 0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f,
    0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb,
    0x086d3d2d, 0x91646c97, 0xe6635c01,	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,	0x8bbeb8ea,
    0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce,
    0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a,
    0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010,	0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409,
    0xce61e49f, 0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17,	0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739,
    0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
    0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344, 0x8708a3d2, 0x1e01f268,
    0x6906c2fe, 0xf762575d, 0x806567cb,	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0,
    0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,	0xd6d6a3e8,
    0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b, 
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef,
    0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 
    0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7,  
    0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 
    0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 
    0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777, 0x88085ae6,
    0xff0f6a70, 0x66063bca, 0x11010b5c,	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7,	0x4969474d, 
    0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 
    0x47b2cf7f, 0x30b5ffe9, 0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605,
    0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b,	0x2d02ef8d
} ;

/*
char f_path[][500] = {
	"/home/zengkai358/xiaoqianhao/ME3630J2AV2.0B01/mdm/target_files/tz.mbn", 
	"/home/zengkai358/xiaoqianhao/ME3630J2AV2.0B01/mdm/target_files/rpm.mbn", 
	"/home/zengkai358/xiaoqianhao/ME3630J2AV2.0B01/mdm/target_files/NON-HLOS.ubi", 
	"/home/zengkai358/xiaoqianhao/ME3630J2AV2.0B01/apps/images/appsboot.mbn", 
	"/home/zengkai358/xiaoqianhao/ME3630J2AV2.0B01/apps/images/mdm9607-perf-sysfs.ubi", 
	"/home/zengkai358/xiaoqianhao/ME3630J2AV2.0B01/apps/images/mdm9607-perf-boot.img" };
*/

char f_path[][500] = {
	"/home/ubuntu/c_compile/header_test/version_file/tz.mbn", 
	"/home/ubuntu/c_compile/header_test/version_file/rpm.mbn", 
	"/home/ubuntu/c_compile/header_test/version_file/NON-HLOS.ubi", 
	"/home/ubuntu/c_compile/header_test/version_file/appsboot.mbn", 
	"/home/ubuntu/c_compile/header_test/version_file/mdm9607-perf-sysfs.ubi", 
	"/home/ubuntu/c_compile/header_test/version_file/mdm9607-perf-boot.img" };
	
char f_name[][25] = {
	"tz.mbn",
	"rpm.mbn",
	"NON-HLOS.ubi",
	"appsboot.mbn",
	"mdm9607-perf-sysfs.ubi",
	"mdm9607-perf-boot.img"};

struct file_stat{
	char name[MAXNAME];
	unsigned int file_crc;
	int length;
	int block_num;
	int start_block_8;
	int end_block_8;
	int start_offset_128;
	int end_offset_128;	
};

struct status
{
	unsigned int img_count;
	char factory_name[MAXFACTORYNAME];
	char version[MAXVERSION];
	struct file_stat tag[MAXFILENUM];
	unsigned int block_crc[MAXBLOCKCRC];
	unsigned int header_crc;
	unsigned int header_crc_comp;
};


unsigned int dsyslib_crc32_calc(
    const unsigned char *buf,
    unsigned int len,
    unsigned int crc_prev)
{
    unsigned int crc ;
    for (crc=crc_prev; len>0 ; buf++, len--) {
        crc = dsyslib_crc32_table[ ( (crc>>24) ^ (*buf) ) ] ^ (crc<<8) ;
    }
    return crc ;
}


int file_length(char *path)
{
	FILE *fp_tg = NULL;
	long int f_len;
	long int ff_len;
	
	fp_tg = fopen(path, "rb");
	if(fp_tg == NULL)
	{
		printf("error to locate file \"%s\" \n", path);
		return 1;
	}
	fseek(fp_tg, 0L, SEEK_END);
	f_len = ftell(fp_tg);
	fclose(fp_tg);
	fp_tg = NULL;
	return f_len;
}


unsigned int caculate_file_crc(
	unsigned char *path_crc,
	unsigned int crc_begin)
{
	FILE *fp_crc = NULL;

	unsigned int crc = 0x00000000;
	long int file_len_crc;

	char *buff_crc = NULL;

	file_len_crc = file_length(path_crc);
	fp_crc = fopen(path_crc, "rb");
	if(fp_crc == NULL)
	{
		printf("file crc open error\n");
		return 1;
	}
	buff_crc = (char *)malloc(sizeof(char)*file_len_crc);
	if(buff_crc == NULL)
	{
		printf("buff_crc malloc error\n");
		return 1;
	}
	fread(buff_crc, file_len_crc, 1, fp_crc);
	crc = dsyslib_crc32_calc(buff_crc, file_len_crc, crc_begin);
	free(buff_crc);
	buff_crc = NULL;
	fclose(fp_crc);
	fp_crc = NULL;
	return crc;
}


int main()
{
	
	FILE *fp = NULL;
	FILE *tg = NULL;
	FILE *tp = NULL;

	unsigned int n = 0;
	unsigned int j = 0;
	unsigned int count = 0;
	unsigned int fill_code = 0; 
	unsigned int temp_block;
	unsigned int crc_init = 0xFFFFFFFF;
	unsigned int crc_prev;
				

	long int block_size = 0;					//128K divided number 
	long int full_bit = 0;						//file full bite 
	long int offset = 128*1024 + 1;				//certain offset point to locate the file access point  
	long int temp_offset = 0;					//offset temp variate

	int f_size = 0;                         	//file size (mb)
	int startoffset_blocksize_128 = 0;
	int endoffset_blocksize_128 = 1;
	
	char *buffer = NULL ;						//file write in buffer
	char *data = NULL;							//file split file name 
	char *temp = NULL;						

	void *p_void;

	struct status pp = {0};
	struct status *header;					//init struct
	header = &pp;								//首地址赋值指针变量
	p_void = (char *)malloc(sizeof(char)*4096);
	memset(p_void, 0x0, 4096);
	if(p_void == NULL)
	{
		printf("malloc error\n");
		return 1;
	}
	strncpy(header->factory_name, "GOSUNCNWELINK TECHNOLOGY.,LTD.", 32);
	printf("enter vension:");
	scanf(" %s", header->version);
	printf("enter image number:");
	scanf("%d", &header->img_count);
	printf(" \n ");
	printf(" \n ");
	printf("BUILD BY  %s\n ", header->factory_name);
	printf(" \n ");
	printf("VERSION: %s\n ", header->version);
	printf(" \n");
	
	for(count=0; count<6; count++)
	{
		//len = strlen(f_name[count]);
		strncpy(header->tag[count].name, f_name[count], MAXNAME);
		//strncat(head_buffer, header.tag.name, MAXNAME);
		//len = strlen(f_path[count]);
		//strncpy(header->tag[count].path, f_path[count], MAXPATH);
		//strncat(head_buffer, header.tag.path, MAXPATH);
		header->tag[count].length = file_length(f_path[count]);
		if((((file_length(f_path[count]) + (1024-1))/1024)%128 != 0))
		{
			header->tag[count].block_num = (((file_length(f_path[count]) + (1024-1))/1024)/128)+1;
		}
		else
		{
			header->tag[count].block_num = ((file_length(f_path[count]) + (1024-1))/1024)/128;
		}
		header->tag[count].file_crc = caculate_file_crc(f_path[count], crc_init);						//文件crc计算
		startoffset_blocksize_128 = 1+endoffset_blocksize_128;
		endoffset_blocksize_128 = startoffset_blocksize_128+header->tag[count].block_num-1;
		header->tag[count].start_block_8 = startoffset_blocksize_128/64 + 1;
		header->tag[count].end_block_8 = endoffset_blocksize_128/64 + 1;
		header->tag[count].start_offset_128 = startoffset_blocksize_128%64;
		header->tag[count].end_offset_128 = endoffset_blocksize_128%64;

		printf(" %s\n ", header->tag[count].name);
		printf("CRC :%02X\n ", header->tag[count].file_crc);
        printf("file length %d\n ", header->tag[count].length);
        printf("file 128k block %d\n ", header->tag[count].block_num);
        printf("file start_block_8M %d\n ", header->tag[count].start_block_8);
        printf("file start_offset_128K %d\n ", header->tag[count].start_offset_128);
        printf("file end_block_8M %d\n ", header->tag[count].end_block_8);    
        printf("file end_offset_128K %d\n ", header->tag[count].end_offset_128);   
		printf("file struct complete :%s\n", header->tag[count].name);
		printf("\n");
	}
	fp = fopen("sum_data", "wb+");
	if(fp ==NULL)
	{
		printf("can't create target file\n");
		return 1;
	}
	p_void = header;															//强制类型转换写入header
	header->header_crc = dsyslib_crc32_calc(p_void, 4096, crc_init);			//header数据crc校验
	header->header_crc_comp = ~(header->header_crc);							//header crc数据取反
	fwrite(p_void, 4096, 1, fp);												//写入header
	buffer = (char *)malloc(sizeof(char)*1);									//补足header剩余124k字节
	if(buffer == NULL)
	{
		printf("malloc error in buffer:\n");
		return 1;
	}
	memset(buffer, 0xff, 1);
	for(fill_code=0; fill_code<(124*1024); fill_code++)							
	{
		fwrite(buffer, 1, 1, fp);
	}

	for(i=0; i<6; i++)
	{
		fseek(fp, offset, SEEK_SET);
		tg = fopen(f_path[i], "rb");
		if(tg == NULL)
		{
			printf("can\'t open %s\n ", f_path[i]);
			return 1;
		}
		printf("openning %s\n",f_path[i]);
		printf("file length:%d\n", file_length(f_path[i]));
		if(((((file_length(f_path[i]) + (1024-1))/1024)%128) != 0))                   //冗余块计算问题
		{
			block_size = (((file_length(f_path[i]) + (1024-1))/1024)/128)+1;           
		}
		else
		{
			block_size = ((file_length(f_path[i]) + (1024-1))/1024)/128;
		}
		full_bit = block_size*1024*128;                                                 //128K块字节
		n = file_length(f_path[i]);
		printf("file start bit point %ld\n", ftell(fp));
		for(j=0; j<n; j++)																		//image写入
		{
			//printf("before entering malloc print test\n");
			buffer = (char *)malloc(sizeof(char)*1);
			//printf("after malloc test print\n");
			if(buffer != NULL)
			{
				//printf("before file read test\n");
				fread(buffer, 1, 1, tg);                      					  
				//printf("file read successful\n");

				fwrite(buffer, 1, 1, fp);
				free(buffer);
				//printf("mem free test print\n");
			}
			else 
			{
				printf("malloc error\n");
				return 1;
			}
		}
		temp_offset = full_bit - file_length(f_path[i]);										//ff补齐剩余字节
		buffer = (char *)malloc(sizeof(char)*1);
		if(buffer == NULL)
		{
			printf("malloc error in buffer:\n");
			return 1;
		}
		memset(buffer, 0xff, 1);
		for(fill_code=0; fill_code<temp_offset; fill_code++)
		{
			fwrite(buffer, 1, 1, fp);
			
		}
		free(buffer);
		offset = full_bit + offset;
		fclose(tg);
		tg = NULL;
		printf("%s caculate length is %ld \n", f_path[i], full_bit);
		printf("\n");
	}
	printf("file sum %ld \n", ftell(fp));

	fseek(fp, 0L, SEEK_END);
	f_size = (ftell(fp))/1024/1024;
	printf("The file sum all is %d mb \n", f_size);
	printf("File split initialization\n");

	if( f_size%8 != 0 )																//拆分8M块
	{
		temp_block = (f_size/8)+1;
	}
	else
	{
		temp_block = f_size/8;
	}

	fseek(fp, 0, SEEK_SET);
	for(j=0; j<temp_block; j++)
	{
		data = (char *)malloc(sizeof(char)*25);
		strncpy(data, "data_block", 11);
		temp = (char *)malloc(sizeof(char)*3);
		snprintf(temp, 3, "%d", j);
		strncat(data, temp, 3);
		tg = fopen(data, "wb+");
		if(tg == NULL)
		{
			printf("cant find this file %s\n", f_name[i]);
			return 1;
		}
		if(j<temp_block-1)
		{
			for(count=0; count<(8*1024); count++)
			{
				buffer = (char *)malloc(sizeof(char)*1024);
				if(buffer == NULL)
				{
					printf("malloc error\n");
					return 1;
				}
				fread(buffer, 1024, 1, fp);
				fwrite(buffer, 1, 1024, tg);
				free(buffer);
			}
		}
		else
		{
			for(count=0; count<((offset-(temp_block-1)*1024*1024*8)/1024); count++)
			{
				buffer = (char *)malloc(sizeof(char)*1024);
				if(buffer == NULL)
				{
					printf("malloc error\n");
					return 1;
				}
				fread(buffer, 1024, 1, fp);
				fwrite(buffer, 1, 1024, tg);
				free(buffer);
			}
		}
		f_size = ftell(tg);
		printf("file %s has already been packaged, with %d size\n", data, f_size);
		if(j == 0)																		//包含header的block进行crc校验
		{
			crc_prev = crc_init;
			fseek(tg, 128*1024+1, SEEK_SET);
			for(count=0; count<63;count++)
			{
				buffer = (char *)malloc(sizeof(char)*128*1024);	
				if(buffer == NULL)
				{
					printf("block_crc buffer malloc error\n");
					return 1;
				}		
				fread(buffer, 128*1024, 1, tg);
				crc_prev = dsyslib_crc32_calc(buffer, 128*1024, crc_prev);
				free(buffer);
				buffer = NULL;
			}
			header->block_crc[j] = crc_prev;
		}
		
		else if(j == temp_block-1)																			//其余block进行crc校验
		{
			crc_prev = crc_init;
			fseek(tg, 0, SEEK_SET);
			for(count=0; count<((offset-(temp_block-1)*1024*1024*8)/1024); count++)
			{
				buffer = (char *)malloc(sizeof(char)*1024);	
				if(buffer == NULL)
				{
					printf("block_crc buffer malloc error\n");
					return 1;
				}
				fread(buffer, 1024, 1, tg);
				crc_prev = dsyslib_crc32_calc(buffer, 1024, crc_prev);
				free(buffer);
				buffer = NULL;
			}
			header->block_crc[j] = crc_prev;
		}
		else
		{
			crc_prev = crc_init;
			fseek(tg, 0, SEEK_SET);
			for(count=0; count<64;count++)
			{
				buffer = (char *)malloc(sizeof(char)*128*1024);	
				if(buffer == NULL)
				{
					printf("block_crc buffer malloc error\n");
					return 1;
				}
				fread(buffer, 128*1024, 1, tg);
				crc_prev = dsyslib_crc32_calc(buffer, 128*1024, crc_prev);
				free(buffer);
				buffer = NULL;
			}
			header->block_crc[j] = crc_prev;
		}
		printf("block crc: %02X\n", header->block_crc[j]);
		fclose(tg);
		tg = NULL;
		free(data);
		free(temp);
	}

	fclose(fp);	
	tg = fopen("data_block0","rb+");
	fwrite(p_void, 4096, 1, tg);										//更新header数据
	tp = fopen("header_temp", "wb+");
	fseek(tg, 0, SEEK_SET);
	buffer = (char *)malloc(sizeof(char)*128*1024);
	if(buffer == NULL)
	{
		printf("header_temp buffer malloc error\n ");
		return 1;
	}
	fread(buffer, 1024*128, 1, tg);
	fwrite(buffer, 1024*128, 1, tp);
	buffer = NULL;
	fclose(tg);
	fclose(tp);
	return 0;
}

