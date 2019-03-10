#include<stdio.h>
float faq(float x);
int islow(float x);

int main()
{
	float x=1.0;
	float sum=1.0;
	int i,sign;
	i=1;
	sign=-1;
	while(!islow(x))
	{	
		printf("%f  ",4.0*sum);
		x=sign/(2.0*i+1);
		sign=(-1)*sign;
		i++;
		sum+=x;
	}
	
	return 0;
}

float faq(float x)  //绝对值函数
{
	if(x>0)
		return x;
	else
		return (-x);
}

int islow(float x)	//判断绝对值是否小于1e-6
{
	if(faq(x) < 1e-6)
		return 1;
	else 
		return 0;
}
