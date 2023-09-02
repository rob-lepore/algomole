import chimera
chimera.openModels.open("./files/pdb/molecule.pdb")
chimera.runCommand("surface")
chimera.runCommand("stop now")
