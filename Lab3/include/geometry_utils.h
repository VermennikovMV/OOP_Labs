#pragma once
#include <vector>
#include <utility>

double PolygonArea(const std::vector<std::pair<double,double>> &vertices);
std::pair<double,double> PolygonCenter(const std::vector<std::pair<double,double>> &vertices);
