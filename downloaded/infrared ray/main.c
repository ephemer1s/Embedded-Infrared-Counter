#include "reg52.h"
#include "ray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{

	int flag = 0, cnt = 0,a = 0;  //cnt为人数，a为循环次数
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
			if(!ray){   	//检测红外传感器发出的低电平   
				flag = 1;
				led0 = ~(led0);
				cnt++;  //人数加一
			}
		}
		else{
			if(ray){
				flag = 0;
				led0 = ~(led0);
			}
		}

	 if (TF0 == 1){     	//判断T0是否溢出                 
		 TF0 = 0;           //清零中断标志
		 TH0 = TimeTH0;     //重新赋初值             
		 TL0 = TimeTL0;             
		 a++;              //循环次数加一            
		 if (a >= 1000)   //判断T0溢出是否达到1000次
			{
				//Countoutput();  //保存人数，当前时间
				led2=0;
				cnt=0;
			  a=0;
			}
	  }
	}
}
