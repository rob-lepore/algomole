#pragma once
#include "../am.h"
#include <fstream>
#include <iostream>
#include "../gfx/mesh.h"

/**
 * @brief The Validator class provides functionality for validating mesh properties
 *        against analytical calculations.
 * 
 * The Validator class provides functionality for validating mesh properties
 * against analytical calculations. The correct analytical values are calculated by calling
 * the UCSF Chimera software. In the project directory will be created a validation folder containing
 * scripts and log files.
 */
class am::utils::Validator
{
public:
	/**
	 * @brief Constructor for the Validator class.
	 *
	 * @param chimeraPath The path to the Chimera software executable.
	 */
	Validator(std::string chimeraPath);

	/**
	 * @brief Computes the relative error in the mesh's surface area.
	 *
	 * @param pdb Content of the PDB (Protein Data Bank) file.
	 * @param m A pointer to the Mesh object representing the mesh.
	 * @return The relative error in surface area.
	 */
	double areaRelativeError(std::string pdb, am::gfx::Mesh* m);

	/**
	 * @brief Computes the analytical surface area of a molecular structure from a PDB file.
	 *
	 * @param pdb Content of the PDB (Protein Data Bank) file.
	 * @return The analytical surface area.
	 */
	double analyticalSurfaceArea(std::string pdb);

	/**
	 * @brief Computes the relative error in the mesh's volume.
	 *
	 * @param pdb Content of the PDB (Protein Data Bank) file.
	 * @param m A pointer to the Mesh object representing the mesh.
	 * @return The relative error in volume.
	 */
	double volumeRelativeError(std::string pdb, am::gfx::Mesh* m);

	/**
	 * @brief Computes the analytical volume of a molecular structure from a PDB file.
	 *
	 * @param pdb Content of the PDB (Protein Data Bank) file.
	 * @return The analytical volume.
	 */
	double analyticalVolume(std::string pdb);

private:
	std::string m_chimera;

	double getValue(int what);
};