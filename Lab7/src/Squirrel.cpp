#include "../include/Squirrel.h"
#include "../include/Visitors.h"
Squirrel::Squirrel(const std::string& n,int xx,int yy):name(n),x(xx),y(yy),alive(true){}
std::string Squirrel::GetName()const{return name;}
int Squirrel::GetX()const{return x;}
int Squirrel::GetY()const{return y;}
std::string Squirrel::GetType()const{return "Squirrel";}
bool Squirrel::IsAlive()const{return alive;}
void Squirrel::Kill(){alive=false;}
void Squirrel::Move(int dx,int dy){if(alive){x+=dx;y+=dy;if(x<0)x=0;if(y<0)y=0;if(x>99)x=99;if(y>99)y=99;}}