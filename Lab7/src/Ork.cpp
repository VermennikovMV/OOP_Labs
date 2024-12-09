#include "../include/Ork.h"
#include "../include/Visitors.h"
Ork::Ork(const std::string& n,int xx,int yy):name(n),x(xx),y(yy),alive(true){}
std::string Ork::GetName()const{return name;}
int Ork::GetX()const{return x;}
int Ork::GetY()const{return y;}
std::string Ork::GetType()const{return "Ork";}
bool Ork::IsAlive()const{return alive;}
void Ork::Kill(){alive=false;}
void Ork::Move(int dx,int dy){if(alive){x+=dx;y+=dy;if(x<0)x=0;if(y<0)y=0;if(x>99)x=99;if(y>99)y=99;}}