#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

	printf("Use only: Hour[0-24], Minute[0-60], Second[0-60]");
	printf("\nExample 1: 05 04 03");
	printf("\nExample 2: 15 14 13");

	/*Input*/
	printf("\nPlease give time: \n");

	char time[9]; /*HH MM SS'0'*/
	fgets(time, 9, stdin);

	scanf("%[^\n]%*c", time);
	printf("Time: %s", time);

	/*Input Process*/
	int hour, minute, second;
	hour = (((time[0] - '0')*10) + (time[1] - '0')); 
	if (hour > 11) hour = hour - 12; /*Easy to calculate with*/ 
	printf("\nHour: %d", hour);

	minute = (((time[3] - '0') * 10) + (time[4] - '0'));
	printf("\nMinute: %d", minute);

	second = (((time[6] - '0') * 10) + (time[7] - '0'));
	printf("\nSecond: %d", second);

	/*Editing ora.svg*/

	FILE* fp;
	fp = fopen("ora.svg", "w");
	if(fp != NULL) printf("\nFile opened for writing!");
	else perror("ERROR: File could not be opened!");

	int x1, x2, y1, y2;
	int degree = 0;

	fprintf(fp, "<svg width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"90\" stroke=\"black\" fill=\"transparent\"  stroke-width=\"5\" />\n");
	fprintf(fp, "<circle cx=\"100\" cy=\"100\" r=\"70\" stroke=\"black\" fill=\"transparent\"  stroke-width=\"3\" />\n");
	fprintf(fp, "<text x=\"57\" y=\"75\">Frozen Rolex</text>\n"); /*Logo :)*/

	
	for (int i = 0; i < 60; i++) {

		y1 = 100 + (70*sin(degree*3.1416 / 180)); /*+100 pushes to the center*/
		y2 = 100 + (90*sin(degree*3.1416 / 180));
		x1 = 100 + (70*cos(degree*3.1416 / 180));
		x2 = 100 + (90*cos(degree*3.1416 / 180));

		if (i % 5 == 0) /*For lines with bigger width*/
		{
			fprintf(fp, "<line x1 = \"%d\" y1 = \"%d\" x2 = \"%d\" y2 = \"%d\" stroke = \"black\" stroke-width=\"5\" />\n", x1, y1, x2, y2);
		}
		else fprintf(fp, "<line x1 = \"%d\" y1 = \"%d\" x2 = \"%d\" y2 = \"%d\" stroke = \"black\"  />\n", x1, y1, x2, y2);

		degree = degree + 6;
	}


	/*Handle Part*/

	int H_x1, H_x2, H_y1, H_y2; /*H = Hour Handle*/
	int M_x1, M_x2, M_y1, M_y2; /*M = Minute Handle*/
	int S_x1, S_x2, S_y1, S_y2; /*S = Second Handle*/
	int H_degree, M_degree, S_degree; 

	/*S_Degree*/	/*1 second = 6 degree*/

	S_degree = ((second * 6)-90); /*-90 degree, because of vectorgraphics*/
	S_y1 = 100; 
	S_y2 = 100 + (50 * sin(S_degree*3.1416 / 180));
	S_x1 = 100; 
	S_x2 = 100 + (50 * cos(S_degree*3.1416 / 180));
	fprintf(fp, "<line x1 = \"%d\" y1 = \"%d\" x2 = \"%d\" y2 = \"%d\" stroke = \"black\"  />\n", S_x1, S_y1, S_x2, S_y2);

	/*M_Degree*/	/*1 minute = 6 degree*/

	M_degree = (((minute * 6) + (S_degree / 60))-90); /*-90 degree, because of vectorgraphics*/
	M_y1 = 100; 
	M_y2 = 100 + (60 * sin(M_degree*3.1416 / 180));
	M_x1 = 100;
	M_x2 = 100 + (60 * cos(M_degree*3.1416 / 180));
	fprintf(fp, "<line x1 = \"%d\" y1 = \"%d\" x2 = \"%d\" y2 = \"%d\" stroke = \"black\"  />\n", M_x1, M_y1, M_x2, M_y2);

	/*H_Degree*/	/*1 hour =  30 degree*/
	
	H_degree = (((hour * 30) + (M_degree / 60))-90); /*-90 degree, because of vectorgraphics*/
	H_y1 = 100; 
	H_y2 = 100 + (70 * sin(H_degree*3.1416 / 180));
	H_x1 = 100;
	H_x2 = 100 + (70 * cos(H_degree*3.1416 / 180));
	fprintf(fp, "<line x1 = \"%d\" y1 = \"%d\" x2 = \"%d\" y2 = \"%d\" stroke = \"black\" stroke-width=\"5\" />\n", H_x1, H_y1, H_x2, H_y2);

	fprintf(fp, "</svg>");
	fclose(fp);
	printf("\nWriting finished, file closed!");
	
	printf("\nDone");
	getchar();
	getchar();
	return 0;
}