#include <stdio.h>
#include <time.h>

char *logfile = "/storage/emulated/0/log.txt";

void plog( const char* info,int code,void* pin ){
   time_t nowtime=time(NULL); 
   char tmp[64];
   strftime(tmp,sizeof(tmp),"%Y-%m-%d %H:%M:%S",localtime(&nowtime));

   FILE * fp;
   fp = fopen ( logfile, "a+" );
   fprintf( fp, "%s <c> %s %d [ %p ]\n", tmp, info, code, pin );
   fclose( fp ); 
}

void clog(){
   FILE * fp;
   fp = fopen ( logfile, "w" );
   fclose( fp ); 
}
