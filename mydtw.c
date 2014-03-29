//dynamic time warping (DTW)
//Author: shuaijiang

#include<stdio.h>
#define XSIZE 5
#define YSIZE 6

int compute_distance(int x, int y);
int min_of_three(int x, int y, int z);
int x_index_of_three(int x, int y, int z);
int y_index_of_three(int x, int y, int z);

int main(int argc, char **argv){
	int x[XSIZE] = {2,3,2,4,5};
	int y[YSIZE] = {1,2,1,4,1,6};
	int distance[XSIZE][YSIZE];
	int xcount = 0, ycount = 0;
	int path_cost[XSIZE][YSIZE];
	int path_trace[XSIZE][YSIZE][2];
	int path_result[XSIZE+YSIZE][2];
	int result_num = 0;
	//compute the distance between the two sequence
	for(xcount=0;xcount<XSIZE;++xcount)
		for(ycount=0;ycount<YSIZE;++ycount)
			distance[xcount][ycount] = compute_distance(x[xcount],y[ycount]);
	
	//print the distance
	for(xcount=0;xcount<XSIZE;++xcount)
	{
		for(ycount=0;ycount<YSIZE;++ycount)
		{
			printf("%d ",distance[xcount][ycount]);
		}
		printf("\n");
	}
	//compute the path cost
	path_cost[0][0] = distance[0][0];
	path_trace[0][0][0] = 0;
	path_trace[0][0][1] = 0;
	for(xcount=1;xcount<XSIZE;++xcount)
	{
		path_cost[xcount][0] = path_cost[xcount-1][0] + distance[xcount][0];
		path_trace[xcount][0][0] = xcount - 1;
		path_trace[xcount][0][1] = 0;
	}
	for(ycount=1;ycount<YSIZE;++ycount)
	{
		path_cost[0][ycount] = path_cost[0][ycount-1] + distance[0][ycount];
		path_trace[0][ycount][0] = 0;
		path_trace[0][ycount][1] = ycount - 1;
	}

	for(xcount=1;xcount<XSIZE;++xcount)
		for(ycount=1;ycount<YSIZE;++ycount)
		{
			path_cost[xcount][ycount] = 
				min_of_three(path_cost[xcount-1][ycount-1],path_cost[xcount-1][ycount],path_cost[xcount][ycount-1]) + distance[xcount][ycount];
			path_trace[xcount][ycount][0] = xcount + x_index_of_three(path_cost[xcount-1][ycount-1],path_cost[xcount-1][ycount],path_cost[xcount][ycount-1]);
			path_trace[xcount][ycount][1] = ycount + y_index_of_three(path_cost[xcount-1][ycount-1],path_cost[xcount-1][ycount],path_cost[xcount][ycount-1]);
		}
			
	//print the path cost
	printf("The path cost:\n");
	for(xcount=0;xcount<XSIZE;++xcount)
	{
		for(ycount=0;ycount<YSIZE;++ycount)
		{
			printf("%d ",path_cost[xcount][ycount]);
		}	
		printf("\n");
	}
	//print the path 
	printf("The path is:\n");
	xcount=XSIZE - 1;
	ycount=YSIZE - 1;
	result_num = 0;
	path_result[0][0] = x[xcount];
	path_result[0][1] = y[ycount];
	while(xcount>0 || ycount > 0)
	{
		printf("%d %d\n",path_trace[xcount][ycount][0],path_trace[xcount][ycount][1]);
		xcount = path_trace[xcount][ycount][0];
		ycount = path_trace[xcount][ycount][1];
		result_num ++;
		path_result[result_num][0] = x[xcount];
		path_result[result_num][1] = y[ycount];
	}
	//print the result
	printf("The result:\n");
	for(xcount=result_num;xcount>=0;--xcount)
		printf("%d ",path_result[xcount][0]);
	printf("\n");
	for(xcount=result_num;xcount>=0;--xcount)
		printf("%d ",path_result[xcount][1]);
	printf("\n");
	
	return 0;
}

int compute_distance(int x, int y)
{
	int distance = x - y;
	if(distance < 0)
		return -distance;
	return distance;
}

int min_of_three( int x, int y, int z )
{
	if( ( x <= y ) && ( x <= z ) ) return x;
	if( ( y <= x ) && ( y <= z ) ) return y;
	if( ( z <= x ) && ( z <= y ) ) return z;
}
int x_index_of_three(int x, int y, int z)
{
	if( ( x <= y ) && ( x <= z ) ) return -1;
	if( ( y <= x ) && ( y <= z ) ) return -1;
	if( ( z <= x ) && ( z <= y ) ) return 0;
}
int y_index_of_three(int x, int y, int z)
{
	if( ( x <= y ) && ( x <= z ) ) return -1;
	if( ( y <= x ) && ( y <= z ) ) return 0;
	if( ( z <= x ) && ( z <= y ) ) return -1;
}
