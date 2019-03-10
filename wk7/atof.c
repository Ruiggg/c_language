#include<stdio.h>
#include<ctype.h>

int main(){
	char s[]="      -456.1231";
	double d;
	double atof(char s[]);
	d=atof(s);
	printf("s=%s\n",s);
	printf("d=%lf\n",d);
	return 0;
}

double atof(char s[]){
	double var,power;
	int i,sign;
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
	
	return sign*var/power;
}
