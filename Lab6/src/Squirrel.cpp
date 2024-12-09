#include "../include/Squirrel.h"
#include "../include/Visitors.h"
Squirrel::Squirrel(const std::string& n,int xx,int yy):name(n),x(xx),y(yy),alive(true){}
void Squirrel::Accept(Visitor& v){v.Visit(*this);}
std::string Squirrel::GetName() const{return name;}
int Squirrel::GetX() const{return x;}
int Squirrel::GetY() const{return y;}
std::string Squirrel::GetType() const{return "Squirrel";}
bool Squirrel::IsAlive() const{return alive;}
void Squirrel::Kill(){alive=false;}