#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

FILE *fp;

char command[500]; 
snprintf(command, 500, "bcftools query -f '%%INFO/AF\n[%%GP\n]' %s", argv[1]);

fp = popen(command , "r");

if (fp == NULL) {
	printf("Unable to execute bcftools command");
}

FILE *info;
char file[70];
snprintf(file, 70, "%s.infos", argv[1]);
info = fopen(file, "r");

FILE *vcf;
char final[70];
snprintf(final, 70, "dosage-%s", argv[1]);
vcf = fopen(final, "a");

int line_read = -1;
int indivs = atoi(argv[2]);
float dosage_line[indivs];
char line[50];
char info_line[847400];
char *info_l = info_line;
char* extra;
float GP[3];
float af;

while(fgets(line, 50 , fp) != NULL){

	if (line_read == -1){
		af = (float) atof(line);
		//printf("maf %f\n", af);
	}
	else{
		
		GP[0] = strtof(strtok(line, ","), &extra);
		//printf("first: %f\n", GP[0]);
		GP[1] = strtof(strtok(NULL, ","), &extra);
		//printf("second: %f\n", GP[1]);
		GP[2] = strtof(strtok(NULL, ","), &extra);
		//printf("third: %f\n", GP[2]);

		if (af >= .5){
			dosage_line[line_read] = GP[0] + GP[0] + GP[1];
		}			
		else{
			dosage_line[line_read] = GP[2] + GP[2] + GP[1];
		}

	}

	line_read ++;

	if (line_read == indivs){

		fgets(info_line, 847400, info);
		fprintf(vcf, "%s\t.\tDS", strtok(info_line, "\n"));

		for (int i=0; i<=indivs-1; i++){
			fprintf(vcf, "\t%f", dosage_line[i]);
		}

		fputs("\n", vcf);
		line_read = -1;
	}
 
}

fclose(info);
fclose(vcf);
pclose(fp);

return 0;

}
