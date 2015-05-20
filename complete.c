#include<stdio.h>

void print(int o,int p,float a[100][100]);
void swap(int p,int i,int flag, float m[100][100]);
int pivot(int i,int p,float m[100][100]);
int nonzero(int o,int p, float m[100][100]);
int infsoln(int o,int p, float m[100][100]);
void uniquesoln(int o,int p,float m[100][100]);

void main()
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
tempz=nonzero(o,p,m);

for(i=0;i<tempz;i++)
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
         j=pivot(i,p,m);     //finding pivot element


   //starting of partial pivoting
    big=-999999999.999999999;
    for(s=i+1;s<=tempz;s++)                           //to find biggest element in row
    {
       if(m[s][j]>big)
           {
            big=m[s][j];
              flag=s;
           }
    }

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
flag=0;
//inf soln
//checking for free variables
flag=infsoln(o,p,m);

//unique soln
   if(flag!=1)
   {
     uniquesoln(o,p,m);

   }

printf("\n\n");
}
//--------------------------------------------------end of main-------------------------------------------------
void print(int o,int p,float a[100][100])
//print the matrix
{ int i,j;
  for ( i = 0; i < o; ++i)
        {  printf("\n");
          for(j=0;j<p;j++)
         {
          printf("   %f",a[i][j]);
         }
        }
}

void swap(int p,int i,int flag, float m[100][100])
{ // This function swaps two rows of the matrix.
  int h; float temp;
   for(h=0;h<p+2;h++)
            {

                temp=m[i][h];
                m[i][h]=m[flag][h];
                m[flag][h]=temp;
            }
}
int pivot(int i,int p,float m[100][100])
{   //finds j value of pivot elemt in given row
   int j,f;
   if(i==0)
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
        return j;
}

int nonzero(int o,int p, float m[100][100])
{ //find out the first non zero from bottom of matrix
    int i;int tempz;
    for(i=o-1;i>=0;i--)
      {
        if(m[i][p+1]!=0)
          {
            tempz=i;
            break;
          }
      }
    return tempz;
}

int infsoln(int o,int p, float m[100][100])
{  // checks for free variables and find soln when inf soln case occurs

   int check,i,j, h=0,f=0,count=0,flag=0;
int freevar[100],pivotloc[100];
//finding out locations of pivot elements
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
//finding j values of free variables in matrix
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

      //printing values of basic variables in form of free variables
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
     flag=1;return flag;

    }
}

void uniquesoln(int o,int p,float m[100][100])
{      //find out values of each variable in case of unique soln

     int h,i,j,check;
     float sol[100],temp;
    for(h=0;h<100;h++) sol[h]=0;
      h=p-1;
printf("\n\n\t\t UNIQUE SOLUTION \n\n");
//finding value of each basic variable using gauss-elmination algorithm and storing it in sol array
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
}