/*
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         Corridor acoustic lights
* @author       Jessica
* @version      V1.0
* @date         2019.8.21
* @brief        走廊声控灯
* @details
* @par History  见如下说明
*
*/
int voicepin = A1;//定义模拟接口A1
int LED_R = 10;  //LED_R接在arduino上的数字I/O口10
int LED_G = 11;  //LED_G接在arduino上的数字I/O口11
int LED_B = 9;   //LED_B接在arduino上的数字I/O口9
int val = 0;//暂存来自传感器的变量数值

/*
* Function       setup
* @author        Jessica
* @date          2019.8.21
* @brief         初始化配置
* @param[in]     void
* @retval        void
* @par History   无
*/
void setup() 
{
  pinMode(voicepin,INPUT);//定义模拟接口0 为输入
  pinMode(LED_B,OUTPUT);//定义绿灯引脚为输出模式
  Serial.begin(9600);//设置波特率为9600
}


/*
* Function       loop
* @author        Jessica
* @date          2019.8.21
* @brief         主函数
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   无
*/
void loop() 
{
  val = analogRead(voicepin);//读取声音传感器的模拟值并赋值给val
  Serial.println(val);//串口打印val变量
  if (analogRead(voicepin) >= 300) //判断收到数据值是否符合范围,个人觉得400比较合适,可根据当前环境调节
  {
    digitalWrite(LED_B, HIGH);//开灯
    for(int i=0; i<10; i++)//感应到有动静的话亮10s之后熄灭，for循环10次也就是1s*10=10s
    {
      delay(1000);//延时1s
    } 
  }
  else
  {
    digitalWrite(LED_B, LOW);//关灯
  }
  delay(1000);//延时1s
}
