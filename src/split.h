#pragma once
#ifndef SPLIT_H 
#define SPLIT_H
#include "student.h"
#include <vector>
#include <string>

void SkirstytiStudentus(const std::vector<Student>& visi, std::vector<Student>& vargsiukai, std::vector<Student>& kietiakai);

void IsvestiIFaila(const std::string& pav, const std::vector<Student>& grupe);

#endif