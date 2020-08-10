#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<time.h>
int main(){
  int fd[2];
        pipe(fd);
       dup2(0,fd[0]);
       dup2(1,fd[1]);
    
while(1){
    char string[255]="";
    char cmds[255]="";
    char*m="yugrawal's terminal>";
    int status;
    write(fd[1],m,strlen(m));
    read(fd[0],string,255);
    
    int l = strlen (string);
    if (l > 0 && string [l - 1] == '\n') string [l - 1] = '\0';
    if((strcmp(string,"exit")==0)||(strcmp(string,"")==0)){
        
        write(fd[1],"exiting\n",8);
        break;
    }
    int k=0,temp=0;
    for(k=0;k<strlen(string);k++){
        if(string[k]==';'){
            temp=1;
        }
    }
    
    if(temp==0){
         char *st_result, *st_help;
        char * ps = strtok_r(string, " ", &st_help);
       
                   
                    int i=0;
                    int j=0;
        char *argv[255]={""};
       
                  
                     while (ps) {
                         // printf("ps is %s\n",ps);
                         argv[j]=ps;++j;
                         ps = strtok_r(NULL, " ", &st_help);
                     }
     //   printf("argv is %s\n",argv[0]);
        if(j==0){argv[0]=ps;argv[1]=NULL;}
                    else{ argv[j]=NULL;}
                     int pid=fork();
  
                         if(pid==0)
                         {  execvp(argv[0],argv);}
                         else{wait(&status);
                             if(WIFEXITED(status)){
                             char processid[10],exitcode[10];
                            snprintf( processid, 10, "%d", pid );
                                   snprintf( exitcode, 10, "%d", WEXITSTATUS(status));
                             char*message="child with pid: ";
                             char *message2=" ended with status code: ";
                             write(fd[1],message,strlen(message));
                              write(fd[1],processid,strlen(processid));
                              write(fd[1],message2,strlen(message2));
                                  write(fd[1],exitcode,strlen(exitcode));
                                   write(fd[1],"\n\n",2);
                             }
                         }
                }
        
    
    else{
        char *st_result, *st_help;
        char * p = strtok_r(string, ";", &st_result);

         while (p) {
             char * ps = strtok_r(p, " ", &st_help);
            
             int i=0;
             int j=1;
             char *argv[255];
             argv[0]=".";
              while (ps) {
                  if(i==0){ strcpy(cmds,ps);++i;}
                  else{
                      argv[j]=ps;++j;
                  }
                  ps = strtok_r(NULL, " ", &st_help);
              }
            if(j==0){argv[0]=ps;argv[1]=NULL;}
            else{ argv[j]=NULL;}
              int pid=fork();
                  if(pid==0)
                  {  execvp(cmds,argv);}
                  else{
                      wait(&status);
                     if(WIFEXITED(status)){
                      char processid[10],exitcode[10];
                     snprintf( processid, 10, "%d", pid );
                            snprintf( exitcode, 10, "%d", WEXITSTATUS(status));
                      char*message="child with pid: ";
                      char *message2=" ended with status code: ";
                      write(fd[1],message,strlen(message));
                       write(fd[1],processid,strlen(processid));
                       write(fd[1],message2,strlen(message2));
                           write(fd[1],exitcode,strlen(exitcode));
                            write(fd[1],"\n\n",2);
                      }
                      
                      
                  }
              p = strtok_r(NULL, ";", &st_result);
         }}

    }
    
    
    return 0;
}
