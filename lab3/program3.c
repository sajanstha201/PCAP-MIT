#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
int findVowel(char *str){
    int count=0;
    for(int i=0;i<strlen(str);i++)
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))
            if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u')
                continue;
            else
                count++;
    return count;
}
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char str[100];
    int new_len;
    char *new_str;
    int len_each_block;
    if(rank==0){
        printf("Enter a string: \n");
        scanf("%s",str);
        new_len=((int)(strlen(str)/size)+1)*size;
        len_each_block=(int)(strlen(str)/size)+1;
        new_str=(char*)malloc(sizeof(char)*new_len);
        for(int i=0;i<new_len;i++)
            if(i<strlen(str))
                new_str[i]=str[i];
            else
                new_str[i]='0';
    }
    MPI_Bcast(&len_each_block,1,MPI_INT,0,MPI_COMM_WORLD);
    char got_str[len_each_block];
    MPI_Scatter(new_str,len_each_block,MPI_CHAR,got_str,len_each_block,MPI_CHAR,0,MPI_COMM_WORLD);
    int no_vowel=findVowel(got_str);
    int result_arr[size];
    MPI_Gather(&no_vowel,1,MPI_INT,&result_arr,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        int total_non_vowel=0;
        for(int i=0;i<size;i++){
            printf("Rank: %d Found No of Non Vowel: %d\n",i,result_arr[i]);
            total_non_vowel+=result_arr[i];
        }
        printf("The total number of Non Vowel is %d\n",total_non_vowel);
    }
    MPI_Finalize();
}