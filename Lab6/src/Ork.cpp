#include "../include/Ork.h"
#include "../include/Visitors.h"
Ork::Ork(const std::string& n,int xx,int yy):name(n),x(xx),y(yy),alive(true){}
void Ork::Accept(Visitor& v){v.Visit(*this);}
std::string Ork::GetName() const{return name;}
int Ork::GetX() const{return x;}
int Ork::GetY() const{return y;}
std::string Ork::GetType() const{return "Ork";}
bool Ork::IsAlive() const{return alive;}
void Ork::Kill(){alive=false;}