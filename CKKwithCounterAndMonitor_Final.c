#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<math.h>

struct tree
{
	int data[1000];
	struct tree* left;
	struct tree* right;
};
struct tree* start;
int a[1000],diff[2000],n,index=0,sub,opt=100,counter=0;
struct tree* ltree(struct tree* node);
struct tree* rtree(struct tree* node);
int noe(struct tree* node);
void display(struct tree* node);
void sort(int* a);
void root()
{
	int i;
	struct tree* nnode=(struct tree*)malloc(sizeof(struct tree));
	counter++;
	for(i=0;i<n;i++)
	{
		nnode->data[i]=a[i];
	}
    nnode->data[i]=-60000;
    start=nnode;
	nnode->left=ltree(nnode);
	nnode->right=rtree(nnode);
	//display(nnode->left->left->left->left);
}
struct tree* ltree(struct tree* node)
{
	int t,i,e1,e2,k;
	while(noe(node)>=3)
	{
		t=0,k=0;
		struct tree* left=(struct tree*)malloc(sizeof(struct tree));
		counter++;
		e1=node->data[0];
		e2=node->data[1];
		t=e1-e2;
		for(i=2;node->data[i]!=-60000;i++)
		{
			left->data[k++]=node->data[i];
		}
	    left->data[k++]=t;
		left->data[k]=-60000;
		sort(left->data);	
		left->left=ltree(left);
		left->right=rtree(left);
		return left;
	}
	
	if(noe(node)==2)
	{
		t=0,k=0;
		struct tree* left=(struct tree*)malloc(sizeof(struct tree));
		counter++;
		e1=node->data[0];
		e2=node->data[1];
		t=e1-e2;
		for(i=2;node->data[i]!=-60000;i++)
		{
			left->data[k++]=node->data[i];
		}
	    left->data[k++]=t;
		left->data[k]=-60000;
		sort(left->data);	
		left->left='\0';
		left->right='\0';
		return left;
	}
}
struct tree* rtree(struct tree* node)
{
	int t=0,i,e1,e2,k=0;
	while(noe(node)>=3)
	{
		t=0,k=0;
		struct tree* right=(struct tree*)malloc(sizeof(struct tree));
		counter++;
		e1=node->data[0];
		e2=node->data[1];
		t=e1+e2;
		for(i=2;node->data[i]!=-60000;i++)
		{
			right->data[k++]=node->data[i];
		}
	    right->data[k++]=t;
		right->data[k]=-60000;
		sort(right->data);
		right->left=ltree(right);
		right->right=rtree(right);
		return right;
	}
	if(noe(node)==2)
	{
		t=0,k=0;
		struct tree* right=(struct tree*)malloc(sizeof(struct tree));
		counter++;
		e1=node->data[0];
		e2=node->data[1];
		t=e1+e2;
		for(i=2;node->data[i]!=-60000;i++)
		{
			right->data[k++]=node->data[i];
		}
	    right->data[k++]=t;
		right->data[k]=-60000;
		sort(right->data);
		right->left='\0';
		right->right='\0';
		return right;
	}
}
int noe(struct tree* node)
{
	int k;
	for(k=0;node->data[k]!=-60000;k++);
	return k;
}
void display(struct tree* node)
{
	struct tree* temp;
	int i;
	temp=node;
	printf("\n");
	for(i=0;temp->data[i]!=-60000;i++)
	{
		printf("%d\t",temp->data[i]);
	}
}
void sort(int* a)
{
	int i,k,j,t;
	for(k=0;a[k]!=-60000;k++);
	for(i=0;i<k;i++)
	{
		for(j=0;j<k-i-1;j++)
		{
			if(a[j]<a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
		}
	}
}
void traversal(struct tree* node)
{
	int tstar;
	struct tree* temp;
	temp=node;
      if(temp=='\0')       
        return;
       if(temp->left =='\0' && temp->right=='\0')      
        {
        	counter=index;
		   	diff[index++]=temp->data[0];
		   	subopt(diff);
		   	tstar=monitor(index-1,counter);
		   	checkFunction(tstar,index-1);
		}
	    traversal(temp->left); 
	    traversal(temp->right);      
}
int monitor(int index1,int time)
{
	float tstar;
	int suboptimal;
	suboptimal=finalCheck(index1);
	if(suboptimal==0)
	{
		printf("Solution is: %d",suboptimal);
		exit(0);
	}
	else
	{
		tstar=3*abs(suboptimal)-log(time+1)/5;
	}
	return tstar;
}
void checkFunction(int tstar,int index1)
{
	int i,sub;
	if(tstar<=0)
	{
		opt=finalCheck(index1);
		printf("The solution is: %d",opt);
		exit(0);
	}
}
void subopt(int* diff)
{
	int i;
	int choice;
	sub=diff[0];
	printf("\nDo you want to continue?(Y=1/N=0): ");
	scanf("%d",&choice);
	if(choice==0)
	{
		for(i=1;i<index;i++)
		{
			if(abs(diff[i])<sub)
			 	opt=diff[i];
		}
		if(opt>sub)
		{
		   opt=sub;
		}
		printf("\nSolution is: %d",opt);
		exit(0);
	}
}
int finalCheck(int index1)
{
	int sub,i;
	sub=diff[0];
	for(i=1;i<index1;i++)
	{
		if(abs(diff[i])<sub)
		 	opt=diff[i];
	}
	if(opt>sub)
	{
	   opt=sub;
	}	
	return opt;
}
main()
{
	
	int i;
	printf("\nEnter the number of elements in the set: ");
	scanf("%d",&n);
	printf("\nEnter the elements: ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	a[n]=-60000;
	sort(a);
	root();
	traversal(start);
	opt=finalCheck(n);
	printf("\nSolution is: %d",opt);	
}
