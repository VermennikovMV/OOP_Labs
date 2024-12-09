#include "../include/Bear.h"
#include "../include/Visitors.h"
Bear::Bear(const std::string& n,int xx,int yy):name(n),x(xx),y(yy),alive(true){}
std::string Bear::GetName()const{return name;}
int Bear::GetX()const{return x;}
int Bear::GetY()const{return y;}
std::string Bear::GetType()const{return "Bear";}
bool Bear::IsAlive()const{return alive;}
void Bear::Kill(){alive=false;}
void Bear::Move(int dx,int dy){if(alive){x+=dx;y+=dy;if(x<0)x=0;if(y<0)y=0;if(x>99)x=99;if(y>99)y=99;}}