#include <math.h>

int f1 = 1; // motor 1 forward
int b1 = 2; // motor 1 backward

int f2 = 11;
int b2 = 12;

float a = 3, b = 3, c = 1.0;

float A = acos((b * b + c * c - a * a) / (2.0 * b * c)) * 180.0 / PI;
float B = acos((a * a + c * c - b * b) / (2.0 * a * c)) * 180.0 / PI;
float C = 180.0 - A - B;

float car_length = 20;

float dist_measured = 30;
float dist_measured_time = 2000;

float angle_measured = 900;
float angle_measured_time = 4000;

float a_time = (dist_measured_time / dist_measured) * a + car_length;
float b_time = (dist_measured_time / dist_measured) * b + car_length;
float c_time = (dist_measured_time / dist_measured) * c + car_length;

float A_time = (angle_measured_time / angle_measured) * (180 - A);
float B_time = (angle_measured_time / angle_measured) * (180 - B);
float C_time = (angle_measured_time / angle_measured) * (180 - C);

void setup()
{
  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(b2, OUTPUT);
}

void forward(float time)
{
  digitalWrite(f1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(b2, LOW);
  delay(time);
}

void rotate(float time)
{
  digitalWrite(f1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(b2, LOW);
  delay(time);
}

void move_triangle()
{
  forward(a_time);
  rotate(C_time);

  forward(b_time);
  rotate(A_time);

  forward(c_time);
  rotate(B_time);
}

void move_triangle_clockwise()
{
  forward(a_time);
  rotate_cw(B_time);

  forward(c_time);
  rotate_cw(A_time);

  forward(b_time);
  rotate_cw(C_time);
}

void loop()
{
  digitalWrite(f1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b2, LOW);
  delay(500);

  move_triangle();
}
