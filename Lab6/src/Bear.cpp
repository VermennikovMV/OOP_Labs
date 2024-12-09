#include "../include/Bear.h"
#include "../include/Visitors.h"
Bear::Bear(const std::string& n,int xx,int yy):name(n),x(xx),y(yy),alive(true){}
void Bear::Accept(Visitor& v){v.Visit(*this);}
std::string Bear::GetName() const{return name;}
int Bear::GetX() const{return x;}
int Bear::GetY() const{return y;}
std::string Bear::GetType() const{return "Bear";}
bool Bear::IsAlive() const{return alive;}
void Bear::Kill(){alive=false;}