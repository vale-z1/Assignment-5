// This header file defines a set of C++ classes for modeling elementary particles, specifically electrons and photons;
// for which inherited subclasses have been created.


class Elementary_Particle_Object  // Base class for photons and electron classes

{
protected:  // Cannot be accessed outside the class, particles variables are defined here.
  double energy;

public:

  Elementary_Particle_Object(double energy_in) : energy{energy_in} {}  // Constructor, Initializes the particle energy

  void set_energy(const float energy_in) {energy = energy_in;}  // Function to set the energy
  double get_energy() const {return energy;}  // Function to get the access the energy value outside the class

  ~Elementary_Particle_Object() {}; // Destructor

};

class Electrons : public Elementary_Particle_Object  // Inherited subclass for electrons. They have an additional property; the rest mass.
{
private:
  double rest_mass;

public:
  // Constructor
  Electrons(double energy_in, double rest_mass_in) : Elementary_Particle_Object(energy_in), rest_mass{rest_mass_in} {}

  ~Electrons() {};

};

class Photons : public Elementary_Particle_Object  // Inherited subclass for photons. No extra variable or function
{
public:

  Photons(double energy_in) : Elementary_Particle_Object(energy_in) {}

  ~Photons(){};
};

#ifndef ASSIGNMENT_5_VALE_Z1_PARTICLE_OBJECT_H
#define ASSIGNMENT_5_VALE_Z1_PARTICLE_OBJECT_H

#endif //ASSIGNMENT_5_VALE_Z1_PARTICLE_OBJECT_H
