#include <IRremote.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();


const int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;
int data_in[20] = {33480735,33444015,33478695,33486855,33435855,33468495,33452175,33423615,33484815,33462375,33448095,33464415,33460335,33427695,33431775,33456255};
String input[20] = {"0","1","2","3","4","5","6","7","8","9","+","-","*","/","=","<"};
String curs;
String value;
int pos=0;
int temp;
int number1;
int number2;
int result;
int operation;
bool num=0;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  Serial.println("Start..");
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}

void loop(){
  if (irrecv.decode(&results))
  {
        //Serial.println(results.value, HEX);
        delay(100);
        temp = results.value;
        Serial.println(temp);
        for (int i=0;i<16;i++)
        {
            if(temp == data_in[i])
            {
              Serial.println("Match found");
              curs = input[i];
              Serial.println(curs);
            }
        }
        if(curs == "+" | curs == "-" | curs == "*" | curs == "/" | curs == "=" )
        {
          if(num == 0)
          {
            Serial.println("First number is : ");
            Serial.println(value);
            //tft.print("Number 1:");
            //tft.print(value);
            number1 = value.toInt();
            num = 1;
            pos = 0;
            value = "";
            tft.setCursor(0,50);
            //tft.print("Operation Selected :");
            if(curs== "+")
            {
              operation = 1;
              Serial.println("Selected add");
              tft.print("+");
              tft.setCursor(0,100);
            }
            else if(curs == "-")
            {
              operation = 2;
              Serial.println("Selected sub");
              tft.print("-");
              tft.setCursor(0,100);
            }
            else if(curs == "*")
            {
              operation = 3;
              Serial.println("Selected mult");
              tft.print("*");
              tft.setCursor(0,100);
            }
            else if(curs == "/")
            {
              operation  = 4;
              Serial.println("Selected div");
              tft.print("/");
              tft.setCursor(0,100);
            }
            
          }
          else
          {
            Serial.println("Second number is : ");
            Serial.println(value);
            tft.setCursor(0,100);
            //tft.print("Number 2:");
            //tft.print(value);
            number2 = value.toInt();
            if(curs == "=")
            {
              Serial.println("Selected equals");
              result = calculate();
              Serial.print("Result is : ");
              Serial.println(result);
              tft.setCursor(0,150);
              //tft.print("Result:");
              tft.print("=");
              tft.setCursor(0,200);
              tft.print(result);
            }
          }
          
        }
        else
        {
          if(curs =="<")
          {
            value.remove(pos-1);
            pos--;
            tft.setCursor(0,num*100);
            tft.print("                 "); //to erase the characrter , may vary according to the font size
            tft.setCursor(0,num*100);
            Serial.print("Values removed");
            tft.print(value);
          }
          else
          {
            value = value+curs; 
            tft.print(value[pos]);
            pos++;
          } 
        }
        irrecv.resume();
  }
}

int calculate()
{
  if(operation == 1)
  {
    //add
    return(number1 + number2);  
  }
  else if(operation == 2)
  {
    //sub
    return(number1 - number2);
  }
  else if(operation == 3)
  {
    //multiply
    return(number1 * number2);
  }
  else if(operation == 4)
  {
    //divide
    return(number1 / number2);
  }
  
}
