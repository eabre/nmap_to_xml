#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#define MAX 2048
#define ROW_NUM 128
int row_saver(int i, int temp, char  texter[MAX], char row[MAX])
{
    temp = i;
    while(1)
    {
        if(texter[i] != '\n')
        {
            i++; // bir sonraki satira gecis icin karakter sayisi tutar
        }
        else break;
    }
    printf("\ntemp is: %d\n", temp);
    while(1)
    {

        if(temp <= i)
        {
            row[temp]= texter[temp];
            temp++;
        }
        else break;
    }
    printf("\n rowwa : %s\n",row);
    return i;
}

int main() {
    int m = 0;
    int temp = 0;
    int j = 0;
    char row_tot[MAX][MAX]; //total rows of text
    char row[MAX]= {"0"};
    FILE* fp;
    char texter[MAX];
    int i=0;
    int count = 0;

    fp= fopen("nmap_test.txt","r");
    if(fp == NULL)
    {
            printf("Could not find nmap_test.txt\n");
            return -1;
    }

    while (1)
    {
            texter[count]= fgetc(fp);
            count++;
            if(feof(fp))
            {
                    break;
            }
    }

    count= 0;
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
    while(1)
    {
        if(j< 500)
        {
            j= row_saver(i, temp, texter, row) + j;
            i= j;
            printf("\nj is : %d\n", j);
            strcpy(row_tot[m],row);
            m++;
            memset(row, 0 ,sizeof (row));
        }
        else break;
    }
    printf("a\n%sb\n%sc\n%sd\n%se\n%sf\n",row_tot[0], row_tot[1], row_tot[2], row_tot[3],row_tot[4]);
    return 0;
}
