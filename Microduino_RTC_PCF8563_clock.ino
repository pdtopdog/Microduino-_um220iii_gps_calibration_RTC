#include "U8glib.h"
#include <Wire.h>
#include <Rtc_Pcf8563.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

Rtc_Pcf8563 rtc;

void setup() { 
  Serial.begin(115200);
  Serial1.begin(115200);
  while(!Serial1){;}   
  }

void loop()
{                                     
         u8g.firstPage();            
         do {  
         u8g.setFont(u8g_font_9x18B);
         u8g.setPrintPos(5,15); 
         u8g.print("BEIJING TIME:");        
         u8g.setPrintPos(0,35);    
         u8g.print(rtc.formatDate(RTCC_DATE_ASIA));

          u8g.setPrintPos(95,35);    
          switch(rtc.getWeekday()){
          case 0: u8g.print( "MON");  break;
          case 1: u8g.print( "TUE");  break;
          case 2: u8g.print( "WED");  break;
          case 3: u8g.print( "THUR"); break;
          case 4: u8g.print( "FRI");  break;
          case 5: u8g.print( "SAT");  break;
          case 6: u8g.print( "SUN");  break;
          default: break;
         }                        
                  
         u8g.setFont(u8g_font_fub20);
         u8g.setPrintPos(8,60);                
         u8g.print(rtc.formatTime(RTCC_TIME_HMS));                  
         }  
         while( u8g.nextPage() );                                                                                    
 } 
