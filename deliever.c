#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXNAME 25
#define MAXPATH 100
#define MAXVERSION 20


struct file_stat{
	char name[MAXNAME];
	char path[MAXPATH];
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

int filestat_detect_integrate()
{
    FILE *tp = NULL;
    FILE *fp = NULL;
    
    char *data = NULL; 
    char *temp = NULL;

    int n = 0;
    int j = 0;
    int block_number = 0;

    fp = fopen("data_sum", "wb+");
    do
    {
        data = (char *)malloc(sizeof(char)*25);
		strncpy(data, "data_block", 11);
		temp = (char *)malloc(sizeof(char)*4);
		snprintf(temp, 4, "%d", n);
		strncat(data, temp, 4);
        tp = fopen(data, "rb");
        if(tp != NULL)
        {
            for(j = 0; j<(1024*1024*8); j++)
            {
                temp = (char *)malloc(sizeof(char)*1);
                if(temp == NULL)
                {
                    printf("malloc error\n");
                    return 1;
                }
                fread(temp, 1, 1, tp);
                fwrite(temp, 1, 1, fp);
                free(temp);
            }
            printf("file block %s founded\n", data);
            n++;
        }
        else
        {
            printf("finish locate file block");
            block_number = n - 1;
            printf("%d\n", block_number);
            break;
        }
        free(data);
        fclose(tp);
    }
    while(n<20);  
    fclose(fp);
    return 0;
}


int main()
{
    FILE *fp_source = NULL;
    FILE *tp_target = NULL;
    FILE *tg = NULL;

    char *buff_temp = NULL;
    char *data = NULL;
    char *buffer = NULL;

    int n = 0;
    int j = 0;
    int flag = 0;
    int offset_point = 1024*128+1;
    int fileblock_length = 0;
    int filemalloc_count = 0;

    void *p_void;

    struct status *header;
    filestat_detect_integrate();
    fp_source = fopen("data_sum", "rb");
    if(fp_source == NULL)
    {
        printf("file open error\n");
        return 1;
    }
    fseek(fp_source, 0L, SEEK_END);
    flag = ftell(fp_source);
    printf("data_sum length %d\n", flag);
    fseek(fp_source, 0, SEEK_SET);   
    buff_temp = (char *)malloc(sizeof(char)*2048);
    if(buff_temp == NULL)
    {
        printf("malloc error\n");
        return 1;
    }        
    fread(buff_temp, 2048, 1, fp_source); 
    p_void = buff_temp;
    header = p_void;        
    for(n=0; n<6; n++)
    {
        printf("%s\n ", header->tag[n].name);
        printf("%s\n ", header->tag[n].path);
        printf("file length %d\n ", header->tag[n].length);
        printf("file 128k block %d\n ", header->tag[n].block_num);
        printf("file start_block_8M %d\n ", header->tag[n].start_block_8);
        printf("file start_offset_128K %d\n ", header->tag[n].start_offset_128);
        printf("file end_block_8M %d\n ", header->tag[n].end_block_8);    
        printf("file end_offset_128K %d\n ", header->tag[n].end_offset_128);   
        printf("\n");        
    }

    for(j=0; j<6; j++)
    {
        tp_target = fopen(header->tag[j].name, "wb+");
        offset_point = fileblock_length + offset_point;
        fseek(fp_source, offset_point, SEEK_SET);
        fileblock_length = (header->tag[j].block_num)*128*1024;
		//printf("file start bit point %ld\n", ftell(fp));
        for(filemalloc_count=0; filemalloc_count < header->tag[j].length; filemalloc_count++)
        {
            buffer = (char *)malloc(sizeof(char)*1);
            if(buff_temp == NULL)
            {
                printf("malloc error\n");
                return 1;
            }
            fread(buffer, 1, 1, fp_source);
            fwrite(buffer, 1, 1, tp_target);
            free(buffer);
        } 
        flag = ftell(tp_target);
        fclose(tp_target);
        tp_target = NULL;
        printf("file %s length is %d, original file length %d \n", header->tag[j].name, flag, header->tag[j].length);
    }
    free(buff_temp);
    fclose(fp_source);
    return 0;
}



