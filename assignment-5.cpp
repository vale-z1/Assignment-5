// University of Manchester - 10895347
// PHYS30762 Programming in C++
// Assignment 5

// This program simulates the decay of 4 different nuclei. 3 radioactive ones and a stable one. Two main classes are used
// elementary particles (for electrons and photons subclasses) and Nuclei objects (for radioactive and stable nuclei subclasses).
// After each decay the nuclei properties and emitted electrons and photons are updated accordingly.
// Four further processes have been explored as well: photoelectric effects, compton scattering, pair production and
// further photon radiations caused by the emitted electrons.


#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include "Elementary_Particles.h"
#include "Nuclei.h"



// This function describes how the different nuclei will decay. Photons and electrons are added accordingly
// and nuclei properties changed to reflect the decay.
void decay(Radioactive_Nucleus& nucleus)
{

  std::string nucleus_type;
  nucleus_type = nucleus.get_nucleus_type();
  if (nucleus_type == "Cs-137")
  {
    std::cout << nucleus.get_nucleus_type() << std::endl;
    nucleus.add_electron(0.5120, 0.511);  // Adds 2 electrons with different energies to the electrons vector in the radioactive nuclei subclass
    nucleus.add_electron(1.174, 0.511);
    nucleus.add_photon(0.661); // Adds a photon to the photons vector in the radioactive nuclei subclass
    nucleus.set_decay_status(1);  // Decay has taken place, flag changed from 0 to 1.
    nucleus.print_photons();  // Prints the new photons created by the decay
    nucleus.set_nucleus_type("Ba-137");  // Changes nuclei type after decay
    nucleus.set_atomic_mass(137);// Changes atomic mass after decay
    nucleus.set_atomic_number(56);// Changes atomic number after decay
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  }

  if (nucleus_type == "Na-22")  // Same function as above but for different nuclei
  {
    std::cout << nucleus.get_nucleus_type() << std::endl;
    nucleus.add_photon(1.2745);
    nucleus.set_decay_status(1);
    nucleus.print_photons();
    nucleus.set_nucleus_type("Ne-22");
    nucleus.set_atomic_mass(22);
    nucleus.set_atomic_number(10);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  }

  if (nucleus_type == "Co-60")// Same function as above but for different nuclei
  {
    std::cout << nucleus.get_nucleus_type() << std::endl;
    nucleus.add_photon(1.173);
    nucleus.add_photon(1.333);
    nucleus.set_decay_status(1);
    nucleus.add_electron(0.31, 0.511);
    nucleus.add_electron(1.48, 0.511);
    nucleus.print_photons();
    nucleus.set_nucleus_type("Ni-60");
    nucleus.set_atomic_mass(60);
    nucleus.set_atomic_number(28);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  }

}

void photoelectric_effect(Radioactive_Nucleus& nucleus)  // Function to simulate the photoelectric effect caused by a photon
{
  const std::shared_ptr<Photons>& photon = nucleus.photons.front();  // Only considers the last photon emitted
  std::cout << "The photoelectric effect electrons energy is: " << photon->get_energy() << " Mev" << std::endl;
}

double compton_scattering(Radioactive_Nucleus& nucleus, double theta)  // Function to simulate compton scattering by a photon.
{
  double energy_0;
  double new_energy;
  std::shared_ptr<Photons> photon = nucleus.photons.back(); // Only considers the last photon emitted

  energy_0 = photon->get_energy();
  new_energy = energy_0 / (1 + (energy_0 / 0.511)*(1 - cos(theta)));  // Calculates the new photon energy after scattering
  photon->set_energy(new_energy);  // Changes the photon energy in the radioactive nuclei photons vector

  return new_energy;
}

void pair_production(Radioactive_Nucleus& nucleus)  // Function to simulate pair production by a photon
{

  const std::shared_ptr<Photons>& photon = nucleus.photons.back();  // Only considers the last photon emitted
  // if multiple photons are present in a decay. .back() returns a reference to the last vector element
  double photon_energy;
  photon_energy = photon->get_energy();
  double electron_energy;
  if (photon_energy > (0.511 * 2))  // Checks if photon energetic enough for pair production
  {
    electron_energy = (photon_energy - (0.511 * 2)) / 2;
    nucleus.add_electron(electron_energy, 0.511);  // Adds 2 new electrons to the electrons vector in the radioactive nuclei subclass
    nucleus.add_electron(electron_energy, 0.511);
    std::cout << "Electrons pair-production has taken place" << std::endl;  // Confirms pair-production
  }
  else {std::cout << "Photon energy is too low, electron pair-production not possible" << std::endl;}  // Warns of no pair-production
}

void electron_radiation(Radioactive_Nucleus& nucleus, int n_photons)  // Function to simulate eventual photons radiated by the emitted electrons
{
  const std::shared_ptr<Electrons>& electron = nucleus.electrons.back();  // Selects last electron (I don't want to iterate over all of them T_T)
  double electron_energy = electron->get_energy();
  double photon_energy = electron_energy / n_photons;  // Assumes energy radiated to be equally distributed between n_photons
  if (n_photons == 0) // Not possible for no photon to be radiated during electrons whole lifetime
  {
    std::cout << "The electron must radiate at least one photon during it's lifetime. Please change the number of radiated photons" << std::endl;
    return;
  }
  for (int n = 0; n < n_photons;)
  {
    n++;
    nucleus.add_photon(photon_energy);  // Adds a new photon to the vector each time one is released
  }

}

int main()
{
  // Sets the initial parameters for the nuclei considered
  Radioactive_Nucleus cs_137{"Cs-137", 137, 55, 30.2, 0};
  Radioactive_Nucleus na_22{"Na-22", 22, 11, 2.6, 0};
  Radioactive_Nucleus co_60{"Co-60", 60, 27, 5.3, 0};
  Stable_Nucleus fe_56{"Fe-56", 56, 26};


  // Create a vector of shared pointers to Nucleus_Object
  std::vector<std::shared_ptr<Nucleus_Object>> nuclei_vector;

  // Add objects to the vector using shared pointers
  nuclei_vector.push_back(std::make_shared<Radioactive_Nucleus>(cs_137));
  nuclei_vector.push_back(std::make_shared<Radioactive_Nucleus>(na_22));
  nuclei_vector.push_back(std::make_shared<Radioactive_Nucleus>(co_60));
  nuclei_vector.push_back(std::make_shared<Stable_Nucleus>(fe_56));

  // Iterate over the vector and print information for each object
  for (const auto& nucleus : nuclei_vector)
  {
    nucleus->print_nucleus();  // Call the print_nucleus method on each object
  }

  std::cout << "" << std::endl;
  std::cout << "If possible, the atoms will now undergo decay" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  for (const auto& nucleus : nuclei_vector)
  {
    // Try casting the nucleus to a shared_ptr of Radioactive_Nucleus
    // Checks if the nuclei is radioactive and therefore if it can decay
    if (auto radioactive_nucleus = std::dynamic_pointer_cast<Radioactive_Nucleus>(nucleus))
    {
      decay(*radioactive_nucleus);  // Call decay only for Radioactive_Nucleus objects
    }

    else // For stable nuclei
    {
      std::cout << nucleus->get_nucleus_type() << " did not decay" << std::endl;
      std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
      std::cout << "" << std::endl;
    }
  }


  for (const auto& nucleus : nuclei_vector)
  {
    nucleus->print_nucleus();  // Call the print_nucleus method on each object after decay
  }



  std::cout << "" << std::endl;
  std::cout << "The cesium photon will now undergo photoelectric effect" << std::endl;
  std::cout << "" << std::endl;

  // Selects one of the nuclei in the vector for one of its electrons to undergo photoelectric effect
  photoelectric_effect(*std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[0]));
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;


  std::cout << "" << std::endl;
  std::cout << "The Sodium photon will now undergo compton scattering" << std::endl;
  std::cout << "" << std::endl;

  // Selects one of the nuclei in the vector for one of its photons to undergo compton scattering
  compton_scattering(*std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[1]), 0.7854);
  nuclei_vector[1]->print_nucleus();

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  std::cout << "" << std::endl;
  std::cout << "Cesium's last photon will now attempt pair-production" << std::endl;  // Should fail
  std::cout << "" << std::endl;
  // Selects one of the nuclei in the vector for one of its photons to undergo compton scattering
  pair_production(*std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[0]));

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  std::cout << "" << std::endl;
  std::cout << "Cobalt's last photon will now attempt pair-production" << std::endl;  // Should succeed
  std::cout << "" << std::endl;

  // Selects one of the nuclei in the vector for one of its photons to undergo pair production
  pair_production(*std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[2]));
  std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[2])->print_electrons();  // Prints all the electrons created in the decay

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  std::cout << "" << std::endl;
  std::cout << "One of the pair produces electrons will now radiate at least an additional photon." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Cobalt's final photons list:" << std::endl;
  std::cout << "" << std::endl;

  // Selects one of the nuclei in the vector for one of its electrons to undergo further radiation
  electron_radiation(*std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[2]), 3);
  std::dynamic_pointer_cast<Radioactive_Nucleus>(nuclei_vector[2])->print_photons();  // Prints all the photons created in the decay

  return 0;
}



















