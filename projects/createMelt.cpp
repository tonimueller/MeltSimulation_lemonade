

#include <cstring>

#include <LeMonADE/utility/RandomNumberGenerators.h>
#include <LeMonADE/core/ConfigureSystem.h>
#include <LeMonADE/core/Ingredients.h>
#include <LeMonADE/feature/FeatureMoleculesIO.h>
#include <LeMonADE/feature/FeatureAttributes.h>
#include <LeMonADE/feature/FeatureExcludedVolumeSc.h>

#include <LeMonADE/utility/TaskManager.h>
#include <LeMonADE/updater/UpdaterReadBfmFile.h>
#include <LeMonADE/updater/UpdaterAddLinearChains.h>


#include <LeMonADE/Version.h>

#include "utility/CommandlineParser.h"

int main(int argc, char* argv[])
{
  try{
	
	std::string outfile;
    uint32_t nSegments;
    uint32_t nChains;
    uint32_t boxSize;
    bool periodic(false);


    CommandLineParser cmd;
		
    //add possible options for command line

    cmd.addOption("-o",1,"output prefix for data "                          );
    cmd.addOption("-N",1,"number of segments");
    cmd.addOption("-M",1,"number of chains");
    cmd.addOption("-b",1,"box size");
    cmd.addOption("-p",0,"periodic if used");

    cmd.addOption("-h",0,"display help"                                     );
    
    //parse command line options
    cmd.parse(argv+1,argc-1);
    
    if(argc==1 || cmd.getOption("-h")){
        std::cout<<"****** CreateMelt  *************\n\n"
        <<"Usage: CreateMelt [options]\n";
        cmd.displayHelp();
        exit(0);
    }

    cmd.getOption("-o", outfile);
    cmd.getOption("-N", nSegments);
    cmd.getOption("-M", nChains);
    cmd.getOption("-b", boxSize);
    periodic = cmd.getOption("-p");

    std::cout <<  "Filename = " << outfile<< std::endl;
    std::cout <<  "nSegments = " << nSegments<< std::endl;
    std::cout <<  "nChains = " << nChains<< std::endl;
    std::cout <<  "boxSize = " << boxSize<< std::endl;
    std::cout <<  "periodic = " << periodic<< std::endl;

	//seed the globally available random number generators
	RandomNumberGenerators rng;
	rng.seedAll();

	// // FeatureExcludedVolume<> is equivalent to FeatureExcludedVolume<FeatureLattice<bool> >
	typedef LOKI_TYPELIST_3(FeatureMoleculesIO, FeatureExcludedVolumeSc<>,FeatureAttributes<>) Features;
	typedef ConfigureSystem<VectorInt3,Features, 6> Config;
	typedef Ingredients<Config> Ing;
	Ing myIngredients;

    myIngredients.setBoxX(boxSize);
    myIngredients.setBoxY(boxSize);
    myIngredients.setBoxZ(boxSize);
    myIngredients.setPeriodicX(periodic);
    myIngredients.setPeriodicY(periodic);
    myIngredients.setPeriodicZ(periodic);
    myIngredients.modifyBondset().addBFMclassicBondset();
    myIngredients.modifyMolecules().setAge(0);
    myIngredients.synchronize(myIngredients);

	TaskManager taskmanager;
    taskmanager.addUpdater( new UpdaterAddLinearChains<Ing>(myIngredients, nChains,nSegments),0 );
	// taskmanager.addUpdater(new UpdaterReadBfmFile<Ing>(infile,myIngredients,UpdaterReadBfmFile<Ing>::READ_LAST_CONFIG_SAVE),0);
	// //here you can choose to use MoveLocalBcc instead. Careful though: no real tests made yet
	// //(other than for latticeOccupation, valid bonds, frozen monomers...)
	// taskmanager.addUpdater(new UpdaterSimpleSimulator<Ing,MoveLocalSc>(myIngredients,save_interval));

	taskmanager.addAnalyzer(new AnalyzerWriteBfmFile<Ing>(outfile,myIngredients));

	taskmanager.initialize();
	taskmanager.run(1);
	taskmanager.cleanup();

	}
	catch(std::exception& err){std::cerr<<err.what();}
	return 0;

}

