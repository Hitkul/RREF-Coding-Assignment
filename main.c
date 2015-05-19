#include<stdio.h>


void print(int o,int p,float a[100][100]);
void swap(int p,int i,int flag, float m[100][100]);
int biggest(int i,int j, int tempz, float m[100][100]);

main()
{
	float a[100][100],b[100],m[100][100],temp,big=-999999999.999999999;
     int o,p,i,j,count=0,s,flag,h,f,k,tempz,check=1;

	printf("\nEnter the number of linear equations==>");
	scanf("%d",&o);
	printf("\nEnter the number of variables==>");
	scanf("%d",&p);

printf("\n\n\nEnter the elements of cofficent matrix==>");

  for(i=0;i<o;i++)                                                     //cofficent matrix input
    for (j = 0; j < p; j++)
    {
      scanf("%f",&a[i][j]);
    }

  printf("\n\n\nEnter the elements of Right Hand Side matrix==>");           //b matrix input

  for(i=0;i<o;i++)
    {
      scanf("%f",&b[i]);
    }

    for(i=0;i<o;i++)                                                     //declaring augrmented matrix to zero
    for (j = 0; j < p+1; j++)
    {
      m[i][j]=0;
    }

  for ( i = 0; i < o; ++i)                                        //inserting elements of a and b to m
         for(j=0;j<p+1;j++)
         {   if(j<p)
             m[i][j]=a[i][j];
            else
            {
               m[i][j]=b[count];
               count++;
            }
         }

       printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");// just to clear the screen
for(i=0;i<o;i++)                     //marking rows having evrything zero...
{check=1;
    for(j=0;(j<p)&&(check);j++)
    {
        if(m[i][j]!=0)
            {check=0;m[i][p+1]=1;}
    }
    if(check==1)
        m[i][p+1]=0;
}

printf("\n\n So given matrix are:-");                   //just printing the three matrix:-)
printf("\n\t\nA=");
    print(o,p,a);


        printf("\n\nB=");

    for ( i = 0; i < o; ++i)
         {

         	printf("\n   %f",b[i]);
         }

    printf("\n\nM=");
    print(o,p+1,m);



printf("\n\n\nConversion to Echelon form");

//geting all zero row at the bottom
for(i=o-1;i>=0;i--)
{
    if(m[i][p+1]!=0)
       {
         tempz=i;
           break;
       }
}

for(i=0;i<tempz;i++)                                  //swaping all zero rows
{    if(m[i][p+1]==0)
    {   printf("\n R%d <--> R%d",i+1,tempz+1);
            swap(p,i,tempz,m);

            tempz--;
   }
}

print(o,p+1,m);


for(i=o-1;i>=0;i--)
{
    if(m[i][p+1]!=0)
       {
         tempz=i;
           break;
       }
}

for(i=0;i<=tempz;i++)
{
         if(i==0)                                //finding pivot element
            j=0;
        else
        {
            for(f=0;f<p+1;f++)
            {
                if(m[i][f]!=0)
                  {
                    j=f;
                    break;
                  }
            }
        }


   //starting of partial pivoting
    biggest( i,j, tempz, m);


    if(m[i][j]<big)
    {
        printf("\n\tR%d <--> R%d",i+1,flag+1);           //swaping of rows
           swap( p,i,flag,m);


        printf("\n\t");
        print(o,p+1,m);


    }
    //end of partial pivoting

    //making pivot column elements zero

    for(s=i+1;s<=tempz;s++)
    {   temp=m[s][j];
        printf("\n\t R%d ---> R%d-(%f/%f)*R%d",s+1,s+1,temp,m[i][j],i+1);
           for(h=0;h<p+1;h++)
            m[s][h]=m[s][h]-(temp/m[i][j])*m[i][h];
        printf("\n\t");
        print(o,p+1,m);

    }


}

printf("\n\n\t\t ECHELON Form is:- \n");
  print(o,p+1,m);

//solving linear equations now

//check for no soln
for(i=0;i<o;i++)
{check=1;
    for(j=0;(j<p)&&(check);j++)
    {   if(m[i][j]!=0)
          check=0;
    }
    if(check==1&&m[i][p+1]==1)
        {printf("\n\t\t NO SOLUTION");
          break;}
}

//inf soln
//checking for free variables
h=0;f=0;count=0;flag=0;
int freevar[100],pivotloc[100];

for(i=0;i<o;i++)
{
	for(j=0;j<p;j++)
	{
		if(m[i][j]!=0)
		{
			pivotloc[h]=j;
			h++;count++;break;
		}
	}
}
for(i=0;i<=100;i++)
	freevar[i]=-1;

for(i=0;i<p;i++)
{check=1;
	for(h=0;(h<count)&&(check);h++)
	{
		if(pivotloc[h]==i)
		{
			check=0;
		}
	}
	if(check==1)
	{
		freevar[f]=i;
		if(freevar[f]!=0){flag=1;};f++;
	}
}
for(i=0;i<100;i++)       //to remove x0 from free var array...
{
	if(freevar[i]==0)
		freevar[i]=-1;
}

if(flag==1)
	{
		printf("\n\n\t\tINFINTELY MANY SOLUTIONS\n\n");


       for(i=o-1;i>=0;i--)
       {
       	printf("\n");check=1;
       	for (j = 0; j < p+1; j++)
        {
       	 	if(m[i][j]!=0)
       	 	{    if (check==1)
                   {printf("%fX%d=",m[i][j],j);check=0;}
                 else
                 {
                       if(j==p)
                       {
                       	printf("(%f)",m[i][j]);
                       }
                       else
                       	printf("(%fX%d)+",-1*m[i][j],j);
                 }
       	 	}
     	}
       }
       printf("\n\n");
       for(h=0;h<p;h++)
       {
       	   if(h>0)
       	   {
       	   	printf("X%d,",freevar[h] );
       	   }
       }printf(" \b can take any arbitrary values");
    }

//unique soln
    float sol[100];
    for(h=0;h<100;h++) sol[h]=0;
    	h=p-1;
printf("\n\n\t\t UNIQUE SOLUTION \n\n");
for(i=o-1;i>=0;i--)
       {
       	check=1;
       	for (j = 0; j < p; j++)
        {
       	 	if(m[i][j]!=0)
       	 	{    if (check==1)
                   {check=0;temp=m[i][j];}
                 else
                 {
                 	sol[h]+= (-1*m[i][j]*sol[j]);
                 }
       	 	}
     	}
     	sol[h]+=m[i][p];
     	sol[h]/=temp;h--;
       }

    for(h=0;h<p;h++)
    {
    	printf("\nX%d=%f",h,sol[h]);
    }
printf("\n\n");
}



void print(int o,int p,float a[100][100])
{
//This function should print the matrix.
}

void swap(int p,int i,int flag, float m[100][100])
{//this function should swap two rows of the matrix m
}

int biggest(int i,int j, int tempz, float m[100][100])
{
  /*This function should find the biggest element in colum of the pivot*/
}