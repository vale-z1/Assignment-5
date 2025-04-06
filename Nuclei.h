// This header file defines a set of C++ classes to model the properties and behaviors of atomic nuclei,
// with a focus on stable and radioactive nuclei where they're created as inherited subclasses.

class Nucleus_Object  // Base class for any nuclei object
{
protected:// Cannot be accessed outside the class, global Nucleus objects variables defined here.

  std::string nucleus_type;
  double atomic_mass;
  double atomic_number;


public:  //
  Nucleus_Object() = default;  // Constructor
  Nucleus_Object(std::string nucleus_type_in, const double atomic_mass_in, const double atomic_number_in) :
      nucleus_type{std::move(nucleus_type_in)}, atomic_mass{atomic_mass_in}, atomic_number{atomic_number_in} {}  // Constructor, initializes object attributes

  void set_nucleus_type(const std::string nucleus_type_in) {nucleus_type = nucleus_type_in;}  // Function to set the nucleus type, can be accessed outside the class
  void set_atomic_mass(const float atomic_mass_in) {atomic_mass = atomic_mass_in;}// Function to set the atomic mass, can be accessed outside the class
  void set_atomic_number(const float atomic_number_in) {atomic_number = atomic_number_in;}// Function to set the atomic number, can be accessed outside the class

  std::string get_nucleus_type() const {return nucleus_type;} // Function to access nucleus type, can be accessed outside the class
  double get_atomic_mass() const {return atomic_mass;}// Function access the atomic mass, can be accessed outside the class
  double get_atomic_number() const {return atomic_number;}// Function to access the atomic number, can be accessed outside the class

  virtual void print_nucleus() const  // Unused but allows the same function to be used for inherited classes
  {
    std::cout << "Base Nucleus: " << get_nucleus_type() << std::endl;
  }

  virtual ~Nucleus_Object() {};  // Destructor
};

class Radioactive_Nucleus : public Nucleus_Object  // Inherited class, additional properties and functions for radioactive nuclei only
{
private:
  int decay_status;
  double half_life;
  std::vector<std::shared_ptr<Photons>> photons;
  std::vector<std::shared_ptr<Electrons>> electrons;

public:
  Radioactive_Nucleus(const std::string& nucleus_type_in, const double atomic_mass_in, const double atomic_number_in,
                      const double half_life_in, const int decay_status_in) :
      Nucleus_Object{nucleus_type_in, atomic_mass_in, atomic_number_in},
      decay_status{decay_status_in}, half_life{half_life_in} {}  // Constructor


  void set_decay_status(const int decay_status_in) {decay_status = decay_status_in;}  // Allows to change the decay
  // status of a nuclei from outside the class (0 -> not decayed, 1 -> decayed)

  // int get_decay_status() const {return decay_status;} // unused

  void add_photon(double energy_in) {
    photons.push_back(std::make_shared<Photons>(energy_in));
  }  //Creates a shared pointer to a Photons class object. Adds an extra photon to a photons vector.

  void add_electron(double energy_in, double rest_mass_in) {
    electrons.push_back(std::make_shared<Electrons>(energy_in, rest_mass_in));
  } //Creates a shared pointer to a Electron class object. Adds an extra electron to an electron vector.

  // const std::vector<std::shared_ptr<Photons>>& get_photons() const { return photons; }  // Unused
  // const std::vector<std::shared_ptr<Electrons>>& get_electrons() const { return electrons; }


  friend void photoelectric_effect(Radioactive_Nucleus& nucleus);  // Makes the photoelectric effect function a friend of this class.
  // Now possible to access the elements of the radioactive nuclei class directly from the function outside the class.
  friend double compton_scattering(Radioactive_Nucleus& nucleus, double theta); // Same use as above
  friend void pair_production(Radioactive_Nucleus& nucleus);
  friend void electron_radiation(Radioactive_Nucleus& nucleus, int n_photons);

  // Prints a full list of the properties of the nuclei
  void print_nucleus() const
  {
    std::cout << "Nucleus Type: " << get_nucleus_type() << std::endl;
    std::cout << "Atomic Mass: " << get_atomic_mass() << " u" << std::endl;
    std::cout << "Atomic Number: " << get_atomic_number() << std::endl;
    std::cout << "Half-Life: " << half_life << " years" << std::endl;
    std::cout << "Decay Status: " << (decay_status == 0 ? "Not decayed" : "Decayed") << std::endl;

    print_electrons();  // Print emitted electrons
    print_photons();  // Print emitted photons

    std::cout << "==================================================================" << std::endl;
  }

  // Prints a full list of the photons emitted by the nuclei
  void print_photons() const
  {
    if (photons.empty())
    {
      std::cout << "No photons emitted." << std::endl;
    }
    else
    {
      for (const auto &photon: photons) {
        std::cout << "Photon energy: " << photon->get_energy() << " MeV" << std::endl;
      }
    }

  };

  // Prints a full list of the electrons emitted by the nuclei
  void print_electrons() const {
    if (electrons.empty()) {
      std::cout << "No electrons emitted." << std::endl;
    } else {
      for (const auto &electron: electrons) {
        std::cout << "Electron energy: " << electron->get_energy() << " MeV, Rest mass: " << 0.511 << " MeV"
                  << std::endl;
      }
    }
  }

  ~Radioactive_Nucleus() {};
};

class Stable_Nucleus : public Nucleus_Object  // Inherited subclass for stable nuclei. Different properties compare to radioactive nuclei
{
public:
  // Constructor
  Stable_Nucleus(const std::string& nucleus_type_in, const double atomic_mass_in, const double atomic_number_in)
      : Nucleus_Object{nucleus_type_in, atomic_mass_in, atomic_number_in} {}

  // Prints a full list of the properties of a stable nuclei
  void print_nucleus() const
  {
    std::cout << "Nucleus Type: " << get_nucleus_type() << std::endl;
    std::cout << "Atomic Mass: " << get_atomic_mass() << " u" << std::endl;
    std::cout << "Atomic Number: " << get_atomic_number() << std::endl;
    std::cout << "Half-Life: " << "Stable nucleus" << std::endl;


    std::cout << "==================================================================" << std::endl;
  }

  ~Stable_Nucleus() {};
};

#ifndef ASSIGNMENT_5_VALE_Z1_NUCLEI_H
#define ASSIGNMENT_5_VALE_Z1_NUCLEI_H

#endif //ASSIGNMENT_5_VALE_Z1_NUCLEI_H
