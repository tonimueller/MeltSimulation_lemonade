

#include <cstring>

#include <LeMonADE/utility/RandomNumberGenerators.h>
#include <LeMonADE/core/ConfigureSystem.h>
#include <LeMonADE/core/Ingredients.h>
#include <LeMonADE/feature/FeatureMoleculesIO.h>
#include <LeMonADE/feature/FeatureAttributes.h>
#include <LeMonADE/feature/FeatureExcludedVolumeSc.h>

#include <LeMonADE/utility/TaskManager.h>
#include <LeMonADE/updater/UpdaterReadBfmFile.h>
#include <LeMonADE/analyzer/AnalyzerRadiusOfGyration.h>


#include <LeMonADE/Version.h>

#include "utility/CommandlineParser.h"

int main(int argc, char* argv[])
{
  try{
	
	std::string outfile;
    std::string infile;
    uint32_t interval;
    uint32_t maxMCS;

    CommandLineParser cmd;
		
    //add possible options for command line

    cmd.addOption("-o",1,"output prefix for data "                          );
    cmd.addOption("-i",1,"input prefix for data "                          );
    cmd.addOption("-w",1,"interval");
    cmd.addOption("-m",1,"max mcs");

    cmd.addOption("-h",0,"display help"                                     );
    
    //parse command line options
    cmd.parse(argv+1,argc-1);
    
    if(argc==1 || cmd.getOption("-h")){
        std::cout<<"****** SimulateMelt  *************\n\n"
        <<"Usage: SimulateMelt [options]\n";
        cmd.displayHelp();
        exit(0);
    }

    cmd.getOption("-o", outfile);
    cmd.getOption("-i", infile);
    cmd.getOption("-w", interval);
    cmd.getOption("-m", maxMCS);
    
	//seed the globally available random number generators
	RandomNumberGenerators rng;
	rng.seedAll();

	// // FeatureExcludedVolume<> is equivalent to FeatureExcludedVolume<FeatureLattice<bool> >
	typedef LOKI_TYPELIST_3(FeatureMoleculesIO, FeatureExcludedVolumeSc<>,FeatureAttributes<>) Features;
	typedef ConfigureSystem<VectorInt3,Features, 6> Config;
	typedef Ingredients<Config> Ing;
	Ing myIngredients;

	TaskManager taskmanager;
	taskmanager.addUpdater(new UpdaterReadBfmFile<Ing>(infile,myIngredients,UpdaterReadBfmFile<Ing>::READ_STEPWISE) );
    taskmanager.addAnalyzer(new AnalyzerRadiusOfGyration<Ing>(myIngredients) ) ;

	taskmanager.initialize();
	taskmanager.run();
	taskmanager.cleanup();

	}
	catch(std::exception& err){std::cerr<<err.what();}
	return 0;

}

