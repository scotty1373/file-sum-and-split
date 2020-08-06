#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXNAME 25
#define MAXPATH 100
#define MAXVERSION 20
#define MAXLENGTH 20
#define MAXBLOCK 10

int i;

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
	char path[MAXPATH];
	int file_crc;
	int length;
	int block_num;
	int start_block_8;
	int end_block_8;
	int start_offset_128;
	int end_offset_128;	
};

struct status
{
	char version[MAXVERSION];
	struct file_stat tag[6];
};


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

	long int block_size = 0;				//128K divided number 
	long int full_bit = 0;					//file full bite 
	long int offset = 128*1024 + 1;				//certain offset point to locate the file access point  
	long int temp_offset = 0;				//offset temp variate

	int f_size = 0;                         //file size (mb)
	int startoffset_blocksize_128 = 0;
	int endoffset_blocksize_128 = 1;
	
	char *buffer = NULL ;					//file write in buffer
	char *data = NULL;						//file split file name 
	char *temp = NULL;						

	void *p_void;

	struct status pp, *header;				//init struct
	header = &pp;							//首地址赋值指针变量
	p_void = (char *)malloc(sizeof(char)*2048);
	if(p_void == NULL)
	{
		printf("malloc error\n");
		return 1;
	}
	scanf(" version: %s", header->version);
	for(count=0; count<6; count++)
	{
		//len = strlen(f_name[count]);
		strncpy(header->tag[count].name, f_name[count], MAXNAME);
		//strncat(head_buffer, header.tag.name, MAXNAME);
		//len = strlen(f_path[count]);
		strncpy(header->tag[count].path, f_path[count], MAXPATH);
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
			

		startoffset_blocksize_128 = 1+endoffset_blocksize_128;
		endoffset_blocksize_128 = startoffset_blocksize_128+header->tag[count].block_num-1;
		header->tag[count].start_block_8 = startoffset_blocksize_128/64 + 1;
		header->tag[count].end_block_8 = endoffset_blocksize_128/64 + 1;
		header->tag[count].start_offset_128 = startoffset_blocksize_128%64;
		header->tag[count].end_offset_128 = endoffset_blocksize_128%64;

		printf("%s\n ", header->tag[count].name);
        printf("%s\n ", header->tag[count].path);
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
	p_void = header;
	fwrite(p_void, 2048, 1, fp);
	buffer = (char *)malloc(sizeof(char)*1);
	if(buffer == NULL)
	{
		printf("malloc error in buffer:\n");
		return 1;
	}
	memset(buffer, 0xff, 1);
	for(fill_code=0; fill_code<(126*1024); fill_code++)							//补足header剩余126k字节
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
		tg = fopen(data, "wb");
		if(tg == NULL)
		{
			printf("cant find this file %s\n", f_name[i]);
			return 1;
		}
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
		
		f_size = ftell(tg);
		printf("file %s has already been packaged, with %d size\n", data, f_size);
		fclose(tg);
		tg = NULL;
		free(data);
		free(temp);
	}
	fclose(fp);	
	return 0;
}

