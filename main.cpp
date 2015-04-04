#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "core.h"
#define MAXBUFF 4096

using namespace std;

char dir[MAXBUFF];
char iimagePath[MAXBUFF];
char dimagePath[MAXBUFF];
char dumpPath[MAXBUFF];
char dumpPath_dbg[MAXBUFF];
char errordumpPath[MAXBUFF];

int main(int argc, char *argv[]){
	
	strncpy(dir, argv[1], strlen(argv[1]));
	snprintf(iimagePath,  strlen(dir) + strlen("iimage.bin") + 2, "%s/iimage.bin", dir);
	snprintf(dimagePath,  strlen(dir) + strlen("iimage.bin") + 2, "%s/dimage.bin", dir);
	snprintf(dumpPath,  strlen(dir) + strlen("my_snapshot.rpt") + 2, "%s/my_snapshot.rpt", dir);
	snprintf(dumpPath_dbg,  strlen(dir) + strlen("my_snapshot_dbg.rpt") + 2, "%s/my_snapshot_dbg.rpt", dir);
    snprintf(errordumpPath,  strlen(dir) + strlen("my_error_dump.rpt") + 2, "%s/my_error_dump.rpt", dir);

#ifdef DEBUG
	printf("Dump: %s\niimage: %s\ndimage: %s\n",dumpPath, iimagePath, dimagePath);
#endif

#ifdef DEBUG
    freopen(dumpPath_dbg,"w", stdout);
#endif

#ifndef DEBUG
    freopen(dumpPath,"w", stdout);
    freopen(errordumpPath, "w", stderr);
#endif
    
    
    Core core;
    core.load(iimagePath, dimagePath);

    while(core.isEnable()){
    	core.print();
    	core.cycle();
        core.dumpError();
#ifdef DEBUG
    	//getchar();
#endif
    }

    return 0;
}
