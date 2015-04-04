#include <cstdio>
#include <cstdlib>

FILE* File(const char *filename, const char *mode){
	FILE *fp = fopen(filename, mode);
	if(fp == NULL){
		fprintf(stderr, "File open error: %s\n",filename);
		exit(-1);
	}
	return fp;
}

int main(int argc, char *argv[]){
	FILE *fin = File(argv[1], "r");
	FILE *fout = File(argv[2],"wb");
	
	int word;
	unsigned char byte[4];
	while(fscanf(fin, "%x",&word) == 1){
		byte[3] = (word & 0x000000FF);
		byte[2] = (word & 0x0000FF00) >> 8;
		byte[1] = (word & 0x00FF0000) >> 16;
		byte[0] = (word & 0xFF000000) >> 24;
		printf("0x%02X 0x%02X 0x%02X 0x%02X\n",
			byte[0],byte[1],byte[2],byte[3]);
		fwrite(byte, sizeof(unsigned char), sizeof(byte), fout);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}