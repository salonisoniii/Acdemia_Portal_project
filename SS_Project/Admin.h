#ifndef ADMIN_H
#define ADMIN_H
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<fcntl.h>
#include "Structures.h"

void display_menu_admin(int socket)
{
    char buff[1024];
    memset(buff,0,sizeof(buff));
    strncpy(buff,"Welcome to Admin Menu\n1.Add Student\n2.View Student Details\n3.Add Faculty\n4.View Faculty Details\n5.Activate Student\n6.Block Student\n7.Modify Student Details\n8.Modify Faculty Details\n9.Logout and Exit\n",sizeof(buff));
    write(socket,buff,strlen(buff)); 
}
void add_student(int socket)
{
    struct Student s;
    char data[20];
    char info[1024];
    strncpy(info,"Enter Student Name\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&s.name,sizeof(s.name));
    // write(1,s.name,sizeof(s.name));
    memset(info,0,sizeof(info));
    strncpy(info,"Enter Student Age\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&s.age,sizeof(s.age));
    // write(1,s.age,sizeof(s.age));
    strncpy(info,"Enter Student Department\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&s.dept,sizeof(s.dept));
    // write(1,s.dept,sizeof(s.dept));
    memset(info,0,sizeof(info));
    strncpy(info,"Enter Student Email\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&s.email,sizeof(s.email));
    // write(1,s.email,sizeof(s.email));
    memset(info,0,sizeof(info));
    int fd = open("StudentDetail.txt",O_RDWR);
    int pos = lseek(fd,0,SEEK_END);
    char temp[] = "MT2023";
    int next_id = (pos/(sizeof(s)))+1;
    char id[20];
    sprintf(id, "%d", next_id);
    strcat(temp,id);
    strncpy(s.s_id,temp,sizeof(s.s_id));
    write(fd,&s,sizeof(s));
    struct Credentials cd;
    int login_data = open("student.txt",O_RDWR);
    lseek(login_data,0,SEEK_END);
    strncpy(cd.id,s.s_id,sizeof(cd.id));
    strncpy(cd.pwd,s.s_id,sizeof(cd.pwd));
    write(login_data,&cd,sizeof(cd));
    memset(info,0,sizeof(info));
    strncpy(info,"Student added successfully!\nPress X to Continue\n",sizeof(info));
    write(socket,info,sizeof(info));
    close(fd);
}
void view_student(int socket)
{
    struct Student s;
    char info[1024];
    char data[20];
    memset(data,0,sizeof(data));
    memset(info,0,sizeof(info));
    strncpy(info,"Enter Student ID\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,data,sizeof(data));
    int fd = open("StudentDetail.txt",O_RDONLY);
    char id_offset[14];
    strncpy(id_offset,data+6,14);
    int offset = atoi(id_offset);
    lseek(fd,(offset-1)*sizeof(struct Student),SEEK_SET);
    int rcount =read(fd,&s,sizeof(s));
    char temp[100];
    memset(temp,0,sizeof(temp));
    strcat(temp,"ID: ");
    strcat(temp,s.s_id);
    strcat(temp,"\nName: ");
    strcat(temp,s.name);
    strcat(temp,"\nAge: ");
    strcat(temp,s.age);
    strcat(temp,"\nEmail: ");
    strcat(temp,s.email);
    strcat(temp,"\nDepartment: ");
    strcat(temp,s.dept);
    strcat(temp,"\n");
    strcat(temp,"Press X to Continue\n");
    // printf("%s",temp);
    write(socket,temp,strlen(temp));
    close(fd);
}
void modify_student(int socket)
{
    char info[1024];
    char data[20];
    strncpy(info,"Enter the student ID\n",sizeof(info));
    write(socket,info,sizeof(info));
    memset(info,0,sizeof(info));
    read(socket,data,sizeof(data));
    int fd = open("StudentDetail.txt",O_RDWR);
    char id_offset[14];
    strncpy(id_offset,data+6,14);
    int offset = atoi(id_offset);
    strncpy(info,"What do you want to modify\n",sizeof(info));
    write(socket,info,sizeof(info));
    memset(info,0,sizeof(info));
    memset(data,0,sizeof(data));
    read(socket,data,sizeof(data));
    if(strcmp("name",data)==0)
    {
        strncpy(info,"Enter the Student Name\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Student)+20,SEEK_SET);
    }
    if(strcmp("age",data)==0)
    {
        strncpy(info,"Enter the Student Age\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Student)+40,SEEK_SET);
    }
    if(strcmp("email",data)==0)
    {
        strncpy(info,"Enter the Student Email\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Student)+60,SEEK_SET);
    }
    if(strcmp("dept",data)==0)
    {
        strncpy(info,"Enter the Student Dept\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Student)+80,SEEK_SET);
    }
    write(fd,data,sizeof(data));
    memset(info,0,sizeof(info));
    strncpy(info,"Updated Successfully!\nPress X to Continue\n",sizeof(info));
    write(socket,info,sizeof(info));
}
void add_faculty(int socket)
{
    struct Faculty f;
    char info[100];
    strncpy(info,"Enter Faculty Name\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&f.name,sizeof(f.name));
    // write(1,f.name,sizeof(f.name));
    memset(info,0,sizeof(info));
    strncpy(info,"Enter Faculty Department\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&f.dept,sizeof(f.dept));
    //write(1,f.dept,sizeof(f.dept));
    memset(info,0,sizeof(info));
    strncpy(info,"Enter Faculty Email\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,&f.email,sizeof(f.email));
    //write(1,f.email,sizeof(f.email));
    memset(info,0,sizeof(info));
    int fd = open("FacultyDetail.txt",O_RDWR);
    int pos = lseek(fd,0,SEEK_END);
    char temp[] = "F";
    int next_id = (pos/(sizeof(f)))+1;
    char id[20];
    sprintf(id, "%d", next_id);
    strcat(temp,id);
    strncpy(f.f_id,temp,sizeof(f.f_id));
    write(fd,&f,sizeof(f));
    struct Credentials cd;
    int login_data = open("faculty.txt",O_RDWR);
    lseek(login_data,0,SEEK_END);
    strncpy(cd.id,f.f_id,sizeof(cd.id));
    strncpy(cd.pwd,f.f_id,sizeof(cd.pwd));
    write(login_data,&cd,sizeof(cd));
    memset(info,0,sizeof(info));
    strncpy(info,"Faculty added successfully!\nPress X to Continue\n",sizeof(info));
    write(socket,info,sizeof(info));
    close(fd);
}
void view_faculty(int socket)
{
    struct Faculty f;
    char info[100];
    char data[20];
    memset(data,0,sizeof(data));
    memset(info,0,sizeof(info));
    strncpy(info,"Enter Faculty ID\n",sizeof(info));
    write(socket,info,sizeof(info));
    read(socket,data,sizeof(data));
    int fd = open("FacultyDetail.txt",O_RDONLY);
    char id_offset[19];
    strncpy(id_offset,data+1,19);
    int offset = atoi(id_offset);
    lseek(fd,(offset-1)*sizeof(f),SEEK_SET);
    int rcount =read(fd,&f,sizeof(f));
    char temp[100];
    memset(temp,0,sizeof(temp));
    strcat(temp,"ID: ");
    strcat(temp,f.f_id);
    strcat(temp,"\nName: ");
    strcat(temp,f.name);
    strcat(temp,"\nEmail: ");
    strcat(temp,f.email);
    strcat(temp,"\nDepartment: ");
    strcat(temp,f.dept);
    strcat(temp,"\n");
    strcat(temp,"Press X to Continue\n");
    // printf("%s",temp);
    write(socket,temp,sizeof(temp));
    close(fd);
}
void modify_faculty(int socket)
{
    char info[100];
    char data[20];
    strncpy(info,"Enter the Faculty ID\n",sizeof(info));
    write(socket,info,sizeof(info));
    memset(info,0,sizeof(info));
    read(socket,data,sizeof(data));
    int fd = open("FacultyDetail.txt",O_RDWR);
    char id_offset[19];
    strncpy(id_offset,data+1,19);
    int offset = atoi(id_offset);
    strncpy(info,"What do you want to modify\n",sizeof(info));
    write(socket,info,sizeof(info));
    memset(info,0,sizeof(info));
    memset(data,0,sizeof(data));
    read(socket,data,sizeof(data));
    if(strcmp("name",data)==0)
    {
        strncpy(info,"Enter the Faculty Name\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Faculty)+20,SEEK_SET);
    }
    if(strcmp("email",data)==0)
    {
        strncpy(info,"Enter the Faculty Email\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Faculty)+60,SEEK_SET);
    }
    if(strcmp("dept",data)==0)
    {
        strncpy(info,"Enter the Faculty Dept\n",sizeof(info));
        write(socket,info,sizeof(info));
        memset(data,0,sizeof(data));
        read(socket,data,sizeof(data));
        lseek(fd,(offset-1)*sizeof(struct Faculty)+40,SEEK_SET);
    }
    write(fd,data,sizeof(data));
    memset(info,0,sizeof(info));
    strncpy(info,"Updated Successfully!\nPress X to Continue\n",sizeof(info));
    write(socket,info,sizeof(info));
}
#endif