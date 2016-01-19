#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include "Matrix.h"

using namespace std;

double* readTXT(char *fileName, int sizeR, int sizeC);

void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

void UnshuffleLogo();


int main()
{

	
	cout << endl;
	cout << "Press 'S' to Unshuffle the logo." << endl;
	
	char input = ' ';
	cin>> input;

	switch(input)
	{
	case 'S':
		UnshuffleLogo();
		break;

	case 's':
		UnshuffleLogo();
		break;

	default:
		cout<<"Invaild input, the program will now close."<<endl;
		system ("pause");
		break;
	}

}

void UnshuffleLogo()
{
	int R = 512; int C = 512;
	
	double* input_data = 0;

	char* inputFileName = "C:\\Users\\Ryan\\Dropbox\\Private\\ASD Assingment\\ASD Assingment\\logo_shuffled.txt"; 
	input_data = readTXT(inputFileName, R, C);

	Matrix LogoShuffled(R, C, input_data);
	
	inputFileName = "C:\\Users\\Ryan\\Dropbox\\Private\\ASD Assingment\\ASD Assingment\\logo_with_noise.txt";
	input_data = readTXT(inputFileName, R, C);

	Matrix LogoNoise(R, C, input_data);

	Matrix LogoResolved(R, C);

	double LowestSSD = 999999999999, tempSSD = 0;

	int LowestCoOrdi = 0, LowestCoOrdj = 0;

	for(int i = 0; i <= 480; i = i + 32)
	{
		for(int j = 0; j <= 480; j = j + 32)
		{
			
			Matrix SampleShuffled = LogoShuffled.getBlock(i, (i+32), j, (j+32));
			for(int k = 0; k <= 480; k = k + 32)
			{
				for(int l = 0; l <= 480; l = l + 32)
				{
					Matrix SampleNoise = LogoNoise.getBlock(k, (k+32), l, (l+32));
					Matrix Diff = SampleShuffled - SampleNoise;
					Matrix Squared = Diff * Diff;
					tempSSD = Squared.sum();
					if (tempSSD < LowestSSD)
					{
						LowestSSD = tempSSD;
						LowestCoOrdi = k;
						LowestCoOrdj = l;
					}
					
				}
			}
			LogoResolved.setBlock(LowestCoOrdi, LowestCoOrdj, SampleShuffled);
			LowestCoOrdi = 0, LowestCoOrdj = 0, LowestSSD = 999999999999;
		}
	}


	
	for(int i = 0; i < R; i ++)
	{
		for(int j = 0; j < C; j ++)
		{
			double temp = LogoResolved.get(i, j);
			input_data[i * C + j] = temp;
		}
	}

	// writes data back to .pgm file stored in outputFileName
	char* outputFileName = "C:\\Users\\Ryan\\Dropbox\\Private\\ASD Assingment\\ASD Assingment\\logo_restored.pgm";
	// Use Q = 255 for greyscale images and 1 for binary images.
	int Q = 255; 
	WritePGM(outputFileName, input_data, R, C, Q); 
	
	
	delete [] input_data;

	cout<<"Logo has been unshuffled."<<endl;

	system ("pause");

}


double* readTXT(char *fileName, int sizeR, int sizeC)
{
  double* data = new double[sizeR*sizeC];
  int i=0;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
	 
	while ( myfile.good())
    {
       if (i>sizeR*sizeC-1) break;
		 myfile >> *(data+i);
	     i++;                                                             
	}
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

 int i;
 unsigned char *image;
 ofstream myfile;

 image = (unsigned char *) new unsigned char [sizeR*sizeC];

 // convert the integer values to unsigned char
 
 for(i=0; i<sizeR*sizeC; i++)
	 image[i]=(unsigned char)data[i];

 myfile.open(filename, ios::out|ios::binary|ios::trunc);

 if (!myfile) {
   cout << "Can't open file: " << filename << endl;
   exit(1);
 }

 myfile << "P5" << endl;
 myfile << sizeC << " " << sizeR << endl;
 myfile << Q << endl;

 myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

 if (myfile.fail()) {
   cout << "Can't write image " << filename << endl;
   exit(0);
 }

 myfile.close();

 delete [] image;

}
