#include "reg52.h"
#include "ray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{

	int flag = 0, cnt = 0,a = 0;  //cntΪ������aΪѭ������
	TimeInit();
	led0 = 1;
	led1 = 1;
	led2 = 1;
	while (1)  // loop
	{   
		if(cnt > 10){
			led1 = 0;
		}
		if(!flag){
			if(!ray){   	//�����⴫���������ĵ͵�ƽ   
				flag = 1;
				led0 = ~(led0);
				cnt++;  //������һ
			}
		}
		else{
			if(ray){
				flag = 0;
				led0 = ~(led0);
			}
		}

	 if (TF0 == 1){     	//�ж�T0�Ƿ����                 
		 TF0 = 0;           //�����жϱ�־
		 TH0 = TimeTH0;     //���¸���ֵ             
		 TL0 = TimeTL0;             
		 a++;              //ѭ��������һ            
		 if (a >= 1000)   //�ж�T0����Ƿ�ﵽ1000��
			{
				//Countoutput();  //������������ǰʱ��
				led2=0;
				cnt=0;
			  a=0;
			}
	  }
	}
}
