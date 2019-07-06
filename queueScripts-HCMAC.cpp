#include "queueScripts-HCMAC.h"


// g++ -std=c++11 -o queueScripts-HCMAC.o queueScripts-HCMAC.cpp queueScripts-HCMAC.h


using namespace std;

int
main(int argc, char const *argv[])
{
	// write files
	// char dir_name[] = "/home/chrisomnet/usr/veins_SCMAC/examples/veins/";
	char dir_name[] = "/home/chris/usr/SuperComputerSubQueueScripts/test/";
	// string dir_name_string = dir_name;

	DIR *dp;
	// struct dirent *entry;
	// struct stat statbuf;

	char *dir;

	dir = dir_name;

	if ( (dp = opendir(dir)) == NULL ){
		cout << "cannot open directory!" << endl;
		return 1;
	}

	chdir(dir);

	string title1 = "#!/bin/bash";
	string title2 = "#$ -cwd";
	string title3 = "#$ -j y";
	string title4 = "#$ -S /bin/bash";

	// string prefix = "/home/chris/usr/HCMAC/veins_HCMAC/run -u Cmdenv -f ./omnetpp_express_SCMAC.ini -r";
	string prefix = "/home/chris/usr/HCMAC/veins-veins-4.6-EDCA/run -u Cmdenv -f omnetpp_express.ini -r";
	// string prefix = "/home/chris/usr/HCMAC/veins_DMMAC/run -u Cmdenv -f omnetpp_express.ini -r";

	string middle1 = "-c";
	string middle2 = "Density";

	std::fstream data;
	string fileName = "HCMAC.sh";

	string project= "s1Persis-"; // pPersis-, EDCA-, s1Persis-, DMMAC-

	// vehicle count from 50 to 300
	/*
	vary j to change vehicle count
	*/
	// for ( int j=50; j<=300; j=j+50){
	// 	for ( int k=0; k<10; ++k){
	// 		string newFileNameEDCAn = "HCMAC-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
	// 		cout << "write, seed: " << k << ", n: " << j << endl;
	// 		data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// 		if ( data.is_open() ){
	// 			data << title1 << "\n";
	// 			data << title2 << "\n";
	// 			data << title3 << "\n";
	// 			data << title4 << "\n";

	// 			data << prefix << " " << k << " " << middle << j;
	// 			data.close();

	// 			cout << "--->File closed." << endl;

	// 			// rename file
	// 			int renameError = rename(fileName.c_str(), newFileNameEDCAn.c_str());
	// 			if ( renameError ){
	// 				cout << "Error: failed to rename a file";
	// 				return 1;
	// 			}

	// 			cout << "--->Successfully rename the file as: " << newFileNameEDCAn << endl;
	// 		}
	// 		else std::cout <<"Error: Unable to write file! \n";
	// 	}
	// }

	// vehicle density 0.05 to 0.95
	/******************************************
	    vary i to change vehicle density
	*******************************************/
	middle2 = "Density";
	for ( double i=0.5; i<=6; i=i+0.5 ){
		// std::cout << "DEBUG======== i:" << i << endl;
		for ( int k=0; k<10; ++k ){
			int denIndex = i*10;
			// std::cout << "DEBUG======== denIndex:" << denIndex << endl;
			string newFileNameEDCAd = "HCMAC-"+middle2+"-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
			cout << "write, seed: " << k << ", " << middle2 << ":"<< denIndex << endl;
			data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
			if ( data.is_open() ){
				data << title1 << "\n";
				data << title2 << "\n";
				data << title3 << "\n";
				data << title4 << "\n";

				if (i<=0.5){
					data << prefix << " " << k << " " << middle1 << " " << middle2 << "_" << "0" << denIndex;
					newFileNameEDCAd = "HCMAC-"+ project +middle2+"-"+"0"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
				}
				else {
					data << prefix << " " << k << " " << middle1 << " " << middle2 << "_" << denIndex;
					newFileNameEDCAd = "HCMAC-"+ project +middle2+"-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
				}

				data.close();

				cout << "--->File closed." << endl;

				// rename file
				int renameError = rename(fileName.c_str(), newFileNameEDCAd.c_str());
				if ( renameError ){
					cout << "Error: failed to rename a file";
					return 1;
				}

				cout << "--->Successfully rename the file as: " << newFileNameEDCAd << endl;
			}
			else std::cout <<"Error: Unable to write file! \n";

		}
	}

	// Packet Generation Interval: 0.02-0.2
	/******************************************
	   vary i to change PGI
	*******************************************/
	// middle2 = "PktInterval";
	// for ( double i=0.02; i<=0.14; i=i+0.02 ){
	// 	// std::cout << "DEBUG======== i:" << i << endl;
	// 	for ( int k=0; k<10; ++k ){
	// 		int denIndex = i*100;
	// 		// std::cout << "DEBUG======== denIndex:" << denIndex << endl;
	// 		string newFileNameEDCAd = "HCMAC-"+middle2+"-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 		cout << "write, seed: " << k << ", " << middle2 << ":"<< denIndex << endl;
	// 		data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// 		if ( data.is_open() ){
	// 			data << title1 << "\n";
	// 			data << title2 << "\n";
	// 			data << title3 << "\n";
	// 			data << title4 << "\n";

	// 			if (i<0.1){
	// 				data << prefix << " " << k << " " << middle1 << " " << middle2 << "_" << "00" << denIndex;
	// 				newFileNameEDCAd = "HCMAC-"+ project +middle2+"-"+"00"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 			}
	// 			else if ( i<=0.2){
	// 				data << prefix << " " << k << " " << middle1 << " " << middle2 << "_" << "0" << denIndex;
	// 				newFileNameEDCAd = "HCMAC-"+ project +middle2+"-"+"0"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 			}

	// 			data.close();

	// 			cout << "--->File closed." << endl;

	// 			// rename file
	// 			int renameError = rename(fileName.c_str(), newFileNameEDCAd.c_str());
	// 			if ( renameError ){
	// 				cout << "Error: failed to rename a file";
	// 				return 1;
	// 			}

	// 			cout << "--->Successfully rename the file as: " << newFileNameEDCAd << endl;
	// 		}
	// 		else std::cout <<"Error: Unable to write file! \n";

	// 	}
	// }






/******************************************

		MPI run scripts:

******************************************/

	// prefix = "mpirun -n 2 /home/chris/usr/HCMAC/veins_HCMAC/run -u Cmdenv -f ./omnetpp_express_SCMAC.ini -r";

	// middle = "-c Density_";
	// vehicle count from 50 to 300
	/*****************************************
		vary j to change vehicle count
	******************************************/
	// for ( int j=50; j<=300; j=j+50){
	// 	for ( int k=0; k<10; ++k){
	// 		string newFileNameEDCAn = "HCMAC-MPI-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
	// 		cout << "write, seed: " << k << ", n: " << j << endl;
	// 		data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// 		if ( data.is_open() ){
	// 			data << title1 << "\n";
	// 			data << title2 << "\n";
	// 			data << title3 << "\n";
	// 			data << title4 << "\n";

	// 			data << prefix << " " << k << " " << middle << j;
	// 			data.close();

	// 			cout << "--->File closed." << endl;

	// 			// rename file
	// 			int renameError = rename(fileName.c_str(), newFileNameEDCAn.c_str());
	// 			if ( renameError ){
	// 				cout << "Error: failed to rename a file";
	// 				return 1;
	// 			}

	// 			cout << "--->Successfully rename the file as: " << newFileNameEDCAn << endl;
	// 		}
	// 		else std::cout <<"Error: Unable to write file! \n";
	// 	}
	// }

	// vehicle density 0.1 to 1
	/*************************************
		vary i to change vehicle density
	**************************************/
	// middle = "-c Density_";
	// for ( float i=0.05; i<0.95; i=i+0.05 ){
	// 	for ( int k=0; k<10; ++k ){
	// 		int denIndex = i*100;
	// 		string newFileNameEDCAd = "HCMAC-MPI-d-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 		cout << "write, seed: " << k << ", d: " << denIndex << endl;
	// 		data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// 		if ( data.is_open() ){
	// 			data << title1 << "\n";
	// 			data << title2 << "\n";
	// 			data << title3 << "\n";
	// 			data << title4 << "\n";

	// 			if (i<0.05)
	// 				data << prefix << " " << k << " " << middle << "0" << denIndex;
	// 			else
	// 				data << prefix << " " << k << " " << middle << denIndex;
	// 			data.close();

	// 			cout << "--->File closed." << endl;

	// 			// rename file
	// 			int renameError = rename(fileName.c_str(), newFileNameEDCAd.c_str());
	// 			if ( renameError ){
	// 				cout << "Error: failed to rename a file";
	// 				return 1;
	// 			}

	// 			cout << "--->Successfully rename the file as: " << newFileNameEDCAd << endl;
	// 		}
	// 		else std::cout <<"Error: Unable to write file! \n";

	// 	}
	// }



	/******************************
	
	  write queue submission shells
	
	*******************************/

	string newFileNameEDCAQsub = "qSubScripts_VehN.sh";
	// data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// if ( data.is_open() ){
	// 	for ( int j=50; j<=300; j=j+50){
	// 		for ( int k=0; k<10; ++k){
	// 			string newFileNameEDCAn = "STMAC-EDCA-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
	// 			data << "qsub " << newFileNameEDCAn << endl;
	// 		}
	// 	}
	// 	data.close();
	// 	cout << "--->File closed." << endl;
	// }
	// else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;

	/******************************
	
	  vary density
	
	*******************************/
	newFileNameEDCAQsub = "qSubScripts_Density.sh";
	data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	if ( data.is_open() ){
		for ( double i=0.5; i<=6; i=i+0.5 ){
			for ( int k=0; k<10; ++k ){
				int denIndex = i*10;
				string newFileNameEDCAd;
				if (i<=0.5){
					newFileNameEDCAd = "HCMAC-" +project+middle2+"-"+"0"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
				}
				else {
					newFileNameEDCAd = "HCMAC-" +project+middle2+"-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
				}
				data << "qsub " << newFileNameEDCAd << endl;
			}
		}
		data.close();
		cout << "--->File closed." << endl;
	}
	else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;


	/*****************************

	write packet interval queue submission shells

	*****************************/
	// newFileNameEDCAQsub = "qSubScripts_PktInterval.sh";
	// data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// if ( data.is_open() ){
	// 	for ( double i=0.02; i<=0.14; i=i+0.02 ){
	// 		for ( int k=0; k<10; ++k ){
	// 			int denIndex = i*100;
	// 			string newFileNameEDCAd;
	// 			if (i<0.1){
	// 				newFileNameEDCAd = "HCMAC-"+project+middle2+"-"+"00"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 			}
	// 			else if ( i<=0.2){
	// 				newFileNameEDCAd = "HCMAC-"+project+middle2+"-"+"0"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 			}
	// 			data << "qsub " << newFileNameEDCAd << endl;
	// 		}
	// 	}
	// 	data.close();
	// 	cout << "--->File closed." << endl;
	// }
	// else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;
	


	//
	// write MPI queue submission shells
	//
	
	// newFileNameEDCAQsub = "qSubMPIScripts_VehN.sh";
	// data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// if ( data.is_open() ){
	// 	for ( int j=50; j<=300; j=j+50){
	// 		for ( int k=0; k<10; ++k){
	// 			string newFileNameEDCAn = "STMAC-EDCA-MPI-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
	// 			data << "qsub " << newFileNameEDCAn << endl;
	// 		}
	// 	}
	// 	data.close();
	// 	cout << "--->File closed." << endl;
	// }
	// else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;

	// newFileNameEDCAQsub = "qSubMPIScripts_Density.sh";
	// data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	// if ( data.is_open() ){
	// 	for ( float i=0.05; i<0.95; i=i+0.05 ){
	// 		for ( int k=0; k<10; ++k ){
	// 			int denIndex = i*100;
	// 			string newFileNameEDCAd = "HCMAC-MPI-d-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
	// 			data << "qsub " << newFileNameEDCAd << endl;
	// 		}
	// 	}
	// 	data.close();
	// 	cout << "--->File closed." << endl;
	// }
	// else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;




	return 0;
}