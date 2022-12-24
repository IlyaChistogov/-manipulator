// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>
#include <Servo.h>
#include <Stepper.h>
Servo myservo12;
Servo myservo10;
Servo myservo9;
Servo myservo8;
#define STEPS 200

#define mot1_en   53
#define mot1_dir  51
#define mot1_step 49

#define mot2_5v   47
#define mot2_en_  35
#define mot2_cw   33
#define mot2_clk  45

Stepper mot3(STEPS, 37, 39, 41, 43);


int pos = 1;
int pos1 = 1;
int pos2 = 1;
int pos3 = 1;

int i1 = 0;
int i2 = 0;
int t = 0;

int t12 = 14; //НАСТРОЙКА!!!//
int t11 = 4;  //НАСТРОЙКА!!!//
int t22 = 14; //НАСТРОЙКА!!!//
int t21 = 4;  //НАСТРОЙКА!!!//

// настройки соединения 
#define REMOTEXY_SERIAL Serial3
#define REMOTEXY_SERIAL_SPEED 9600


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 71 bytes
  { 255,6,0,0,0,64,0,16,31,2,5,32,3,30,30,30,0,70,30,30,
  2,26,31,4,0,51,26,8,34,34,52,6,47,2,26,4,0,80,26,8,
  32,45,57,7,41,2,26,4,0,91,26,8,32,54,57,7,41,2,26,4,
  128,72,16,37,7,7,36,51,7,2,26 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  int8_t joystick_1_x; // oт -100 до 100  
  int8_t joystick_1_y; // oт -100 до 100  
  int8_t slider_1; // =0..100 положение слайдера 
  int8_t slider_2; // =0..100 положение слайдера 
  int8_t slider_3; // =0..100 положение слайдера 
  int8_t slider_4; // =0..100 положение слайдера 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

void motor_stop()
{
  digitalWrite(37, 0);
  digitalWrite(39, 0);
  digitalWrite(41, 0);
  digitalWrite(43, 0);

  digitalWrite(mot1_en, 1);
  digitalWrite(mot1_dir, 0);
  digitalWrite(mot1_step, 0);

  digitalWrite(mot2_5v, 0);
  digitalWrite(mot2_en_, 0);
  digitalWrite(mot2_cw, 0);
  digitalWrite(mot2_clk, 0);

}
void mot3_right()
{
  mot3.step(10);
}
void mot3_left()
{
  mot3.step(-10);
}
void mot2_up()
{
  digitalWrite(mot2_en_, 1);
  digitalWrite(mot2_5v, 1);
  digitalWrite(mot2_cw, 0);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot2_clk, !digitalRead(mot2_clk));
    delayMicroseconds(1000);
  }
}

void mot2_down()
{
  digitalWrite(mot2_en_, 1);
  digitalWrite(mot2_5v, 1);
  digitalWrite(mot2_cw, 1);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot2_clk, !digitalRead(mot2_clk));
    delayMicroseconds(1000);
  }
}

void mot1_up()
{
  digitalWrite(mot1_en, 0);
  digitalWrite(mot1_dir, 0);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot1_step, !digitalRead(mot1_step));
    delayMicroseconds(1000);
  }
}

void mot1_down()
{
  digitalWrite(mot1_en, 0);
  digitalWrite(mot1_dir, 1);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot1_step, !digitalRead(mot1_step));
    delayMicroseconds(1000);
  }
}



void setup() 
{
  RemoteXY_Init ();
  RemoteXY_Init (); 
  myservo12.attach(12);
  myservo8.attach(8); 
  myservo10.attach(10);
  myservo9.attach(9); 


  pinMode(mot1_en,   1);
  pinMode(mot1_dir,  1);
  pinMode(mot1_step, 1);

  pinMode(mot2_5v,  1);
  pinMode(mot2_en_, 1);
  pinMode(mot2_cw,  1);
  pinMode(mot2_clk, 1);

  digitalWrite(mot1_en,  0);

  digitalWrite(mot2_en_, 1);
  digitalWrite(mot2_5v,  1);

  mot3.setSpeed(30);

  
  
  // TODO you setup code
  
}



void loop() 
{ 
  RemoteXY_Handler ();
  pos = RemoteXY.slider_4;
  myservo12.write(pos);
  pos1 = ((RemoteXY.slider_1)/2)+130;
  myservo10.write(pos1);
  pos2 = RemoteXY.slider_2;
  myservo9.write(pos2);
  pos3 = RemoteXY.slider_3+90;
  myservo8.write(pos3);

  if ((RemoteXY.joystick_1_y > 50) and (RemoteXY.joystick_1_x > -50) and (RemoteXY.joystick_1_x < 50))
        {
          mot2_up();
        }
        else if ((RemoteXY.joystick_1_y < -50) and (RemoteXY.joystick_1_x > -50) and (RemoteXY.joystick_1_x < 50))
        {
          mot2_down();
        }
        else if ((RemoteXY.joystick_1_x > 50) and (RemoteXY.joystick_1_y > -50) and (RemoteXY.joystick_1_y < 50))
        {
          mot3_right();
        }
        else if ((RemoteXY.joystick_1_x < -50) and (RemoteXY.joystick_1_y > -50) and (RemoteXY.joystick_1_y < 50))
        {
          mot3_left();
        }
        else
        {
          motor_stop();
        }
  
  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay() 


}
