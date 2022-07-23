#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct 
{
	double r;
	double g;
	double b;

} pixel_RGB;

void imagefilter(char *, char *, char *);

int main (int argc, char *argv[]){

	if (argc!=4){
	printf("you should pass four arguments\n");
	exit(EXIT_FAILURE);
	
	}
	

	imagefilter(argv[1], argv[2], argv[3]);
	
	return 0;
}


void imagefilter(char *path1, char *path2, char *path3){


FILE* output=NULL;
	output=fopen(path2,"wb");
	if(output==NULL){
	printf("\nerror\n");
	exit(EXIT_FAILURE);
	}
	
	FILE *fp=NULL;
	fp=fopen(path1,"r");
	if (fp==NULL){
       printf("error while opening the image");
  		 } 
    double** kernel=NULL;
    kernel=calloc(1,(3)*sizeof(double* ));
   for (int i=0; i<(3); i++){
   
   kernel[i]=calloc(1,3*sizeof(double* ));
   
   }
   kernel[1][1]=1;
   char* end=NULL;
   char* string=path3;
   
   for(int i=0; i<3; i++){
   
   for(int k=0; k<3; k++){
   
   kernel[i][k]=strtod(string,&end);
   string=end+1;
   printf("%0.2f ",kernel[i][k]);
   }
   
   }
   printf("\n");
   
   
   
   int x;
   int y;
   char p;
   unsigned int max;
   
   
   int format;
   fscanf(fp,"%c%d", &p,&format);
   fscanf(fp,"%d %d", &x,&y);
   fscanf(fp,"%u",&max);
   
   pixel_RGB** image=NULL;
   
   image=calloc(1,(y+2)*sizeof(pixel_RGB* ));
   for (int i=0; i<(y+2); i++){
   
   image[i]=calloc(1,(x+2)*sizeof(pixel_RGB));
   
   }
   
   for (int i=1; i<(y+1);i++){
   
   for (int k=1; k<(x+1); k++)
   {
   fscanf(fp,"%lf",&image[i][k].r);
   fscanf(fp,"%lf",&image[i][k].g);
   fscanf(fp,"%lf",&image[i][k].b);
   }
   
   }
   
   pixel_RGB** filterimage=NULL;
   
   filterimage=calloc(1,(y+2)*sizeof(pixel_RGB* ));
   for (int i=0; i<(y+2); i++){
   
   filterimage[i]=calloc(1,(x+2)*sizeof(pixel_RGB));
   
   }
   
   	for (int i=1; i<(y+1);i++){
   		for (int k=1; k<(x+1); k++){
   		
   
  	 for (int v=0; v<3;v++){
   		for (int c=0; c<3; c++){
   		filterimage[i][k].r+=(image[i-1+v][k-1+c].r*kernel[c][v]);
   		filterimage[i][k].g+=(image[i-1+v][k-1+c].g*kernel[c][v]);
   		filterimage[i][k].b+=(image[i-1+v][k-1+c].b*kernel[c][v]);
 			  
	}}
		if(filterimage[i][k].r>(double)max) filterimage[i][k].r=(double )max;
		if(filterimage[i][k].g>(double)max) filterimage[i][k].g=(double )max;
		if(filterimage[i][k].b>(double)max) filterimage[i][k].b=(double )max;
		
		
		if(filterimage[i][k].r<0) filterimage[i][k].r=0;
		if(filterimage[i][k].g<0) filterimage[i][k].g=0;
		if(filterimage[i][k].b<0) filterimage[i][k].b=0;
	}}
   
   
   
   
   fprintf(output,"P%d\n%d %d\n%u\n",format,x,y,max);
   int count=0;
   
   for (int i=1; i<(y+1);i++){
   
   for (int k=1; k<(x+1); k++)
   {
   fprintf(output,"%u ",(unsigned int)filterimage[i][k].r);
   fprintf(output,"%u ",(unsigned int)filterimage[i][k].g);
   fprintf(output,"%u ",(unsigned int)filterimage[i][k].b);
   count++;
   if (count%4==0)fprintf(output,"\n");
   }
   
   }
   
   
   fclose(fp);
   free(image);
   free(kernel);
   fclose(output);

}

	

  
   
   

