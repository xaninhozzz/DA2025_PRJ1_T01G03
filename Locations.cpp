//
// Created by anacastanheiros on 3/24/25.
//

#include "Locations.h"
#include <string>

Locations::Locations(int id, std::string code, bool parking) {
  this->id = id;
  this->code = code;
  this->parking = parking;
}

int Locations::getId() {
  return id;
}

std::string Locations::getCode() {
  return code;
}

bool Locations::getParking() {
  return parking;
}

void Locations::setId(int id) {
  this->id = id;
}

void Locations::setCode(std::string code) {
  this->code = code;
}

void Locations::setParking(bool parking) {
  this->parking = parking;
}
