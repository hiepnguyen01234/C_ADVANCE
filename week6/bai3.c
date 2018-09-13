#include"graphtuan8.h"

typedef struct
{
  char key[31];
  char value[31];
}nhaga;


void searchword(JRB g)
{
  FILE *fptr1;
  char filename1[]="dulieu.txt";
  nhaga ng[10];
  nhaga dd[10];
  char s[31];
  int i=0;
  int j=0;
  if((fptr1=fopen(filename1,"r"))==NULL)
    {
      printf("error.\n");
      return ;
    }
  while(!feof(fptr1))
    {
      if(fscanf(fptr1,"%s",s)==1)
	{ 
      
	  if(strcmp(s,"stations")==0)
	    fscanf(fptr1,"%s",s);

	  if(strcmp(s,"lines")==0)
	    j=1;
	  if(j==0) {
	    sscanf(s,"%[^=]%*c%s", ng[i].key, ng[i].value);//doctuxau '%[^=]'doctruocdau= '%*c'bomotkytu
            addvertex(g,ng[i].key,ng[i].value);
	    i++;
	  }
	  //  if(j==1)
	  //for(i=0;;i++)
	  //  strcpy(dd[i].key,s);
	}
    }
  // printf("%s",dd[0].key);
  while(i--)
    printf("[%s| %s]\n",ng[i].key, ng[i].value);
  fclose(fptr1);
}
void creategraph2(JRB g)
{
  FILE *fptr1;
  char filename1[]="dulieu.txt";
  nhaga ng[10];
  nhaga dd[10];
  char s1[31],s2[31],s[31];
  char buff[9],c;
  int i=0,a=0,landau;
  int j=0;
  if((fptr1=fopen(filename1,"r"))==NULL)
    {
      printf("error.\n");
      return ;
    }
  while(!feof(fptr1))
    {
      if(fscanf(fptr1,"%s",s)==1)
	{ 
      
	  if(strcmp(s,"stations")==0)
	    j=1;

	  if(strcmp(s,"lines")==0)
            j=0;
            

	  if(j==0) {
	    while(1){
	      do{c = fgetc(fptr1);}
	      while((c!='=')&&(c!=EOF));
	      //puts("leteo");
	      a=1;
	      landau=1;
              while(1)
		{
		  if(a==1)
		    {
		      a=2;
		      fscanf(fptr1,"%s",s1);
		    }
		  else if(a==2)
		    {
		      a=1;
		      fscanf(fptr1,"%s",s2);
		    }
		  if(landau==0) {
		    //printf("%s %s\n",s1,s2);
		    addEdges(g,s1,s2);
		    addEdges(g,s2,s1);
		    i++;
		  }
		  landau=0;
		  c=fgetc(fptr1);
		  //printf("(%d,%c)",c,c);
		  if(c=='\n') break;
		  if(feof(fptr1)) return;
		  if(c==EOF) return;
		}
	    }
	  }
	}
    }
  fclose(fptr1);
}


void switch_case(int *n)
{
  printf("------menu-----\n");
  printf("1.mang luoi nha ga.\n");
  printf("2.tim kiem ga lien ke.\n");
  printf("3.thoat.\n");
  JRB g1,g2;
  char tenga[31];
  g1=make_jrb();
  g2=make_jrb();

  FILE *fptr1;
  char filename1[]="dulieu.txt";
  if ((fptr1=fopen(filename1,"r"))==NULL)
    {
      printf("error.\n");
      return ;
    }
  scanf("%d",&*n);
  switch(*n)
    {
    case 1:
      {
	searchword(g1);
	break;
      }
    case 2:
      {
	searchword(g1);
        printf("\n\nnhap ten ga:\n");
        scanf("%s",tenga);
        creategraph2(g2);
        getadj(g2,g1,tenga);
	break;
      }
    case 3:
      {
	fclose(fptr1);
        jrb_free_tree(g1);
        jrb_free_tree(g2);
	break;
      }
    }
}

int main()
{
  int n=1;
  while(n!=3)
    {
      if((n<1)||(n>3))
	{
	  printf("nhap lai.\n");
	  switch_case(&n);
	}
      else switch_case(&n);
    }
  return 0;
}


