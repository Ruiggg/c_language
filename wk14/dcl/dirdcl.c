#include "dcl.h"
void dircdl(void)
{
	int type;
	if(tokentype=='(')//表示只有1个(，而不是一对（）
	{
		dcl();
		if(tokentype!=')')
			printf("error: missing )\n");
	}
	else if(tokentype==NAME)
		strcpy(name,token);
	else
		printf("error:expected name or (dcl)\n");
		
	while((type=gettoken())==PARENS || type ==BRACKETS)
		if(type==PARENS)
		{
			strcat(out," function returning");
		}
		else
		{
			strcat(out," array");
			strcat(out,token);
			strcat(out," of");
		}
}
