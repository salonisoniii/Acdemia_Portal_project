#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/select.h>

int main()
{
    // struct faculty{
    //     char id[20];
    //     char password[20];
    // };
    // struct faculty f1,f2,f3;
    // int fd = open("student.txt",O_RDWR);
    // strncpy(f1.id, "MT2023001", sizeof(f1.id));
    // strncpy(f1.password, "Tanvi", sizeof(f1.password));
    // strncpy(f2.id, "MT2023002", sizeof(f2.id));
    // strncpy(f2.password, "Nikita", sizeof(f2.password));
    // strncpy(f3.id, "MT2023003", sizeof(f3.id));
    // strncpy(f3.password, "Subhra", sizeof(f3.password));
    // write(fd,&f1,sizeof(struct faculty));
    // lseek(fd,0,SEEK_CUR);
    // write(fd,&f2,sizeof(struct faculty));
    // lseek(fd,0,SEEK_CUR);
    // write(fd,&f3,sizeof(struct faculty));
    // lseek(fd,0,SEEK_CUR);
//     int fd = open("StudentDetail.txt",O_RDWR);
//     int pos = lseek(fd,0,SEEK_SET);
//     struct Student s;
//     read(fd,&s,sizeof(struct Student));
//     write(1,s.s_id,sizeof(s.s_id));
// }
// fd_set rfds;
// FD_ZERO(&rfds);
// FD_SET(0,&rfds);
// struct timeval tv;
// tv.tv_sec = 5;
// tv.tv_usec = 0;
//     int val = select(2,&rfds,NULL,NULL,&tv);
//     if(val==0)
//     {
//         printf("No input\n");
//     }
//     else{
//         printf("Input\n");
//     }
char msg[1024];
printf("%ld\n",(msg,"Logged Out Successfully\n",strlen(msg)));

}