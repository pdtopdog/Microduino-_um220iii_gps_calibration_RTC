#include <Wire.h>
#include <Rtc_Pcf8563.h>
#include <MemoryFree.h>;   //https://github.com/sudar/MemoryFree.git


String inputString = ""; 
boolean stringComplete = false;
const int LOCAL_AREA = 8;

struct GNZDA{
  String UTC_Time;
  String localTime;
  String hour;                         
  String minute;         
  String second;
  String year;
  String month;
  String day; 
  String yr;
  int Hour; 
  int Minute;         
  int Second;   
  int YR;  
  int Year;
  int Month;
  int Day;   
}gps;

Rtc_Pcf8563 rtc;
     
void setup() { 
  Serial.begin(115200);
  while(!Serial){           
    ;
  }
  Serial1.begin(115200);  
  rtc.initClock();
  }

     
void loop() {
        serialEvent();
        if(stringComplete){
        //Serial.println(inputString);            
        if (inputString.startsWith("$GNZDA")){                
         String UTC_Time = inputString.substring(7,17);                                                                        
         String hour=inputString.substring(7,9);                         
         String minute = inputString.substring(9,11);         
         String second = inputString.substring(11,13);
                 
         gps.Hour = hour.toInt(); 
         gps.Minute = minute.toInt(); 
         gps.Second = second.toInt();                       
         
         int localHour = (gps.Hour + LOCAL_AREA) % 24 ; // 转化成区域时间，北京为东八时区，utc小时+8即为区域时间。和24取余数                 
         

         String day = inputString.substring(18,20);                                 
         String month = inputString.substring(21,23);         
         String year=inputString.substring(24,28);
         String yr=inputString.substring(26,28);    
         gps.Day = day.toInt(); 
         gps.Month = month.toInt();         
         gps.Year = year.toInt(); 
         gps.YR = yr.toInt(); 
         
        boolean LEAP_YEAR = gps.Year % 400 == 0 || gps.Year % 100 != 0 && gps.Year % 4 == 0; //闰年标志位
         
         int GPS_Hour_Tmp = gps.Hour + LOCAL_AREA;
         
         switch(gps.Month)
         {
            case 1:
                if(GPS_Hour_Tmp >= 24)
              {                   
                   gps.Day += 1;
                   if(gps.Day > 31)
                {
                   gps.Day -= 31;
                   gps.Month += 1;
                 }
              }
            break;
            case 2:
                if(GPS_Hour_Tmp >= 24)
             {                  
                   gps.Day += 1;
                   if( LEAP_YEAR = 1)
                 { 
                   if(gps.Day > 29)
                 {
                   gps.Day -= 29;
                   gps.Month += 1;  
                  }
               }
               else
              {
                 
                 if(gps.Day > 28)
                 {
                    gps.Day -= 28;
                    gps.Month += 1;
                  }
            
               }
             }
             break;      
             case 3:
                   if(GPS_Hour_Tmp >= 24)
                 {                     
                      gps.Day += 1;
                      if(gps.Day > 31)
                    {
                       gps.Day -= 31;
                       gps.Month += 1;
                     }
                  }
               break;
               case 4:
               if(GPS_Hour_Tmp >= 24)
              {                   
                    gps.Day += 1;
               if(gps.Day > 30)
                {
                      gps.Day -= 30;
                      gps.Month += 1;
                 }
               }
               break;

               case 5:
                if(GPS_Hour_Tmp >= 24)
              {                
                  gps.Day += 1;
                  if(gps.Day > 31)
                     {
                         gps.Day -= 31;
                         gps.Month += 1;
                      }
                }
                break;

               case 6:
                 if(GPS_Hour_Tmp >= 24)
               {                 
                  gps.Day += 1;
                  if(gps.Day > 30)
                  {
                   gps.Day -= 30;
                   gps.Month += 1;
                  }
                }
                break;

                case 7:
                if(GPS_Hour_Tmp >= 24)
               {               
                 gps.Day += 1;
                 if(gps.Day > 31)
                  {
                    gps.Day -= 31;
                    gps.Month += 1;
                   }
                 }
                 break;

                case 8:
                if(GPS_Hour_Tmp >= 24)
               {                   
                   gps.Day += 1;
                 if(gps.Day > 31)
                 {
                    gps.Day -= 31;
                    gps.Month += 1;
                  }
                 }
                break;

                case 9:
                if(GPS_Hour_Tmp >= 24)
                {                  
                   gps.Day += 1;
                   if(gps.Day > 30)
                   {
                      gps.Day -= 30;
                      gps.Month += 1;
                    }
                   }
                  break;

                  case 10:
                  if(GPS_Hour_Tmp >= 24)
                  {                     
                     gps.Day += 1;
                   if(gps.Day > 31)
                   {
                      gps.Day -= 31;
                      gps.Month += 1;
                    }
                   }
                   break;
      
                   case 11:
                  if(GPS_Hour_Tmp >= 24)
                  {                    
                     gps.Day += 1;
                   if(gps.Day > 30)
                   {
                     gps.Day -= 30;
                     gps.Month += 1;
                    }
                   }
                   break;

                   case 12:
                   if(GPS_Hour_Tmp >= 24)
                   {                     
                      gps.Day += 1;
                    if(gps.Day > 31)
                    {
                       gps.Day -= 31;
                       gps.Month = 1;
                       gps.Year += 1;
                     }
                    }
                    break;
            default:
            break;
            }
         
          
            /* 
            * 基姆拉尔森计算公式
            */
            if(gps.Month ==1||gps.Month ==2) {
             gps.Month=(gps.Month==1?13:14);;
             gps.Year--;
             }
             int Weekday=(gps.Day+2*gps.Month +3*(gps.Month +1)/5+gps.Year+gps.Year/4-gps.Year/100+gps.Year/400)%7;                     
             Serial.println(Weekday);     

         //set a time to start with.
         //day, weekday, month, century(1=1900, 0=2000), year(0-99)
         rtc.setDate(gps.Day, Weekday, gps.Month, 0, gps.YR);
         //hr, min, sec
         rtc.setTime(localHour, gps.Minute, gps.Second ); 

         Serial.println("CODE_1:");
         Serial.print(rtc.formatTime());
         Serial.print("     ");
         Serial.print(rtc.formatDate());
         Serial.print("\r\n");

         Serial.println("CODE_2:");
         Serial.print("20");
         Serial.print(rtc.getYear());
         Serial.print("/");
         Serial.print(rtc.getMonth());
         Serial.print("/");
         Serial.print(rtc.getDay());
         Serial.print("     ");
         Serial.print(rtc.getHour());
         Serial.print(":");
         Serial.print(rtc.getMinute());
         Serial.print(":");
         Serial.print(rtc.getSecond());
         Serial.print("\r\n");

         delay(100);
         Serial.print("\r\n");      
                                                                                             
     } 
                  
     inputString = "";
     stringComplete = false;
     boolean LEAP_YEAR = false;
     int GPS_Hour_Tmp = 0;
     memoryCheck();
     //Serial.println(getFreeMemory());        
  }
}

void serialEvent() {
   while (Serial1.available()>0){     
     char inChar =(char) Serial1.read();               
               inputString +=inChar;                                       
          if (inChar == '\n') {            
      stringComplete = true;      
     }      
   }       
 }
 




