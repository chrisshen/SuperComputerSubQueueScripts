#include "queueScripts.h"

using namespace std;

int
main(int argc, char const *argv[])
{
	// write files
	// char dir_name[] = "/home/chrisomnet/usr/veins_SCMAC/examples/veins/";
	char dir_name[] = "/home/chrisomnet/usr/SuperComputerSubQueueScripts/test/";
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

	string prefix = "/home/chris/usr/STMAC/veins_stableTMAC/run -u Cmdenv -f ./veins_STMAC_EDCA.ini -r";
	string middle = "-c VehN_";

	std::fstream data;
	string fileName = "STMAC-EDCA.sh";

	// vehicle count from 50 to 300
	/*
	vary j to change vehicle count
	*/
	for ( int j=50; j<=300; j=j+50){
		for ( int k=0; k<10; ++k){
			string newFileNameEDCAn = "STMAC-EDCA-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
			cout << "write, seed: " << k << ", n: " << j << endl;
			data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
			if ( data.is_open() ){
				data << title1 << "\n";
				data << title2 << "\n";
				data << title3 << "\n";
				data << title4 << "\n";

				data << prefix << " " << k << " " << middle << j;
				data.close();

				cout << "--->File closed." << endl;

				// rename file
				int renameError = rename(fileName.c_str(), newFileNameEDCAn.c_str());
				if ( renameError ){
					cout << "Error: failed to rename a file";
					return 1;
				}

				cout << "--->Successfully rename the file as: " << newFileNameEDCAn << endl;
			}
			else std::cout <<"Error: Unable to write file! \n";
		}
	}

	// vehicle density 0.1 to 1
	/*
	vary i to change vehicle density
	*/
	middle = "-c Density_";
	for ( float i=0.1; i<1.1; i=i+0.1 ){
		for ( int k=0; k<10; ++k ){
			int denIndex = i*10;
			string newFileNameEDCAd = "STMAC-EDCA-d-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
			cout << "write, seed: " << k << ", d: " << denIndex << endl;
			data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
			if ( data.is_open() ){
				data << title1 << "\n";
				data << title2 << "\n";
				data << title3 << "\n";
				data << title4 << "\n";

				if (i<1.0)
					data << prefix << " " << k << " " << middle << "0" << denIndex;
				else
					data << prefix << " " << k << " " << middle << denIndex;
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


/******************************************

		MPI run scripts:

******************************************/

	prefix = "mpirun -n 2 /home/chris/usr/STMAC/veins_stableTMAC/run -u Cmdenv -f ./veins_STMAC_EDCA.ini -r";

	middle = "-c VehN_";
	// vehicle count from 50 to 300
	/*****************************************
		vary j to change vehicle count
	******************************************/
	for ( int j=50; j<=300; j=j+50){
		for ( int k=0; k<10; ++k){
			string newFileNameEDCAn = "STMAC-EDCA-MPI-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
			cout << "write, seed: " << k << ", n: " << j << endl;
			data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
			if ( data.is_open() ){
				data << title1 << "\n";
				data << title2 << "\n";
				data << title3 << "\n";
				data << title4 << "\n";

				data << prefix << " " << k << " " << middle << j;
				data.close();

				cout << "--->File closed." << endl;

				// rename file
				int renameError = rename(fileName.c_str(), newFileNameEDCAn.c_str());
				if ( renameError ){
					cout << "Error: failed to rename a file";
					return 1;
				}

				cout << "--->Successfully rename the file as: " << newFileNameEDCAn << endl;
			}
			else std::cout <<"Error: Unable to write file! \n";
		}
	}

	// vehicle density 0.1 to 1
	/*************************************
		vary i to change vehicle density
	**************************************/
	middle = "-c Density_";
	for ( float i=0.1; i<1.1; i=i+0.1 ){
		for ( int k=0; k<10; ++k ){
			int denIndex = i*10;
			string newFileNameEDCAd = "STMAC-EDCA-MPI-d-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
			cout << "write, seed: " << k << ", d: " << denIndex << endl;
			data.open( fileName, ios::out /*| ios::in| ios::app*/ | ios::binary );
			if ( data.is_open() ){
				data << title1 << "\n";
				data << title2 << "\n";
				data << title3 << "\n";
				data << title4 << "\n";

				if (i<1.0)
					data << prefix << " " << k << " " << middle << "0" << denIndex;
				else
					data << prefix << " " << k << " " << middle << denIndex;
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

	// write queue submission shells
	string newFileNameEDCAQsub = "qSubScripts_VehN.sh";
	data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	if ( data.is_open() ){
		for ( int j=50; j<=300; j=j+50){
			for ( int k=0; k<10; ++k){
				string newFileNameEDCAn = "STMAC-EDCA-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
				data << "qsub " << newFileNameEDCAn << endl;
			}
		}
		data.close();
		cout << "--->File closed." << endl;
	}
	else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;

	newFileNameEDCAQsub = "qSubScripts_Density.sh";
	data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	if ( data.is_open() ){
		for ( float i=0.1; i<1.1; i=i+0.1 ){
			for ( int k=0; k<10; ++k ){
				int denIndex = i*10;
				string newFileNameEDCAd = "STMAC-EDCA-d-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
				data << "qsub " << newFileNameEDCAd << endl;
			}
		}
		data.close();
		cout << "--->File closed." << endl;
	}
	else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;
	
	//
	// write MPI queue submission shells
	//
	
	newFileNameEDCAQsub = "qSubMPIScripts_VehN.sh";
	data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	if ( data.is_open() ){
		for ( int j=50; j<=300; j=j+50){
			for ( int k=0; k<10; ++k){
				string newFileNameEDCAn = "STMAC-EDCA-MPI-n-"+to_string(j)+"-r-"+to_string(k)+".sh";
				data << "qsub " << newFileNameEDCAn << endl;
			}
		}
		data.close();
		cout << "--->File closed." << endl;
	}
	else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;

	newFileNameEDCAQsub = "qSubMPIScripts_Density.sh";
	data.open( newFileNameEDCAQsub, ios::out /*| ios::in| ios::app*/ | ios::binary );
	if ( data.is_open() ){
		for ( float i=0.1; i<1.1; i=i+0.1 ){
			for ( int k=0; k<10; ++k ){
				int denIndex = i*10;
				string newFileNameEDCAd = "STMAC-EDCA-MPI-d-"+to_string(denIndex)+"-r-"+to_string(k)+".sh";
				data << "qsub " << newFileNameEDCAd << endl;
			}
		}
		data.close();
		cout << "--->File closed." << endl;
	}
	else std::cout <<"Error: Unable to write file! \n" << newFileNameEDCAQsub;




	return 0;
}