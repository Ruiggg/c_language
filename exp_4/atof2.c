#include<stdio.h>
#include<ctype.h>
double pow2(int n);
int main(){
	char s[100];
	scanf("%s",s);
	double d;
	double atof(char s[]);
	d=atof(s);
	printf("s=%s\n",s);
	printf("d=%lf\n",d);
	return 0;
}

double atof(char s[]){
	double var,power;
	int i,sign,sign2,n;
	for(i=0;isspace(s[i]);i++)
		;
	sign=(s[i]=='-')?-1:1;
	if(s[i]=='-'||s[i]=='+')
		i++;
	for(var=0.0;isdigit(s[i]);i++)
		var=var*10.0+s[i]-'0';
	if(s[i]=='.')
		i++;
	for(power=1.0;isdigit(s[i]);i++)
	{
		var=var*10.0+s[i]-'0';
		power*=10.0;
	}	
	if(s[i]=='e'||s[i]=='E')
		i++;
	sign2=(s[i]=='-')?-1:1;
	
	if(s[i]=='-'||s[i]=='+')
		i++;
	for(n=0;isdigit(s[i]);i++)
		n=n*10+s[i]-'0';
		//printf("\nn=%d\n",n);
	
		//printf("\nn=%d\n",n);
		//printf("\npow2(n)=%lf\n",pow2(n));
	double bf=1.0;
	if(sign2>=0)
	{
		for(i=1;i<=n;i++)
			bf=10.0*bf;	
	}
	if(sign2<0)
	{
		for(i=1;i<=n;i++)
			bf=bf/10.0;
	}
	return (sign*var/power)*bf;
}

/*double pow2(int n)
{
	double x,y=1.0;
	int i;
	x=n;
	
	if(n>0)
	{
		for(i=1;i<=n;i++)
			y=10.0*y;
		return y;
	}
	else if(n=0)
		return 1.0;
	else
	{
		for(i=-1;i>=n;i--)
			y=y/10.0;
		return y;
	}
}*/
