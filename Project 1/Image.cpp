//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************


#include "Image.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

// Constructor and Desctructors
MyImage::MyImage() 
{
	Data = NULL;
	Width = -1;
	Height = -1;
	Y_lum = -1;
	U_chr = -1;
	V_chr = -1;
	Quant = -1;
	ImagePath[0] = 0;
}

MyImage::~MyImage()
{
	if ( Data )
		delete Data;
}


// Copy constructor
MyImage::MyImage( MyImage *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	Data   = new char[Width*Height*3];
	strcpy(otherImage->ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage->Data[i];
	}


}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	Y_lum = otherImage.Y_lum;
	U_chr = otherImage.U_chr;
	V_chr = otherImage.V_chr;
	Quant = otherImage.Quant;
	Data   = new char[Width*Height*3];
	strcpy( (char *)otherImage.ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage.Data[i];
	}
	
	return *this;

}

// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Width*Height; i ++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}
	
	// Allocate Data structure and copy
	Data = new char[Width*Height*3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
	}

	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(IN_FILE);

	return true;

}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
		
	}

	
	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}
	
	// Clean up and return
	delete Rbuf;
	delete Gbuf;
	delete Bbuf;
	fclose(OUT_FILE);

	return true;

}





// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
bool MyImage::Modify()
{
	//const int sizeData = Height * Width * 3;
	float *dataY = new float[this->Height*this->Width];
	float *dataU = new float[this->Height*this->Width];
	float *dataV = new float[this->Height*this->Width];
	float *dataR = new float[this->Height*this->Width];
	float *dataG = new float[this->Height*this->Width];
	float *dataB = new float[this->Height*this->Width];
	float *dataOri = new float[Height*Width * 3];
	int Y_val = this->Y_lum;
	int U_val = this->U_chr;
	int V_val = this->V_chr;
	int Q_val = this->Quant;
	//create a Y U and V matrices
	for (int i = 0; i < this->Height * this->Width; i++)
	{
		dataY[i] = 0;
		dataU[i] = 0;
		dataV[i] = 0;
	}
	//converting to YUV
	for (int i = 0; i < Height*Width; i++)
	{

		dataY[i] = 0.299*Data[3 * i + 2] + 0.587*Data[3 * i + 1] + 0.114*Data[3 * i]; //Y
		dataU[i] = 0.596*Data[3 * i + 2] - 0.274*Data[3 * i + 1] - 0.322*Data[3 * i]; //U
		dataV[i] = 0.211*Data[3 * i + 2] - 0.523*Data[3 * i + 1] + 0.312*Data[3 * i]; //V
		dataOri[3 * i] = Data[3 * i];
		dataOri[3 * i + 1] = Data[3 * i + 1];
		dataOri[3 * i + 2] = Data[3 * i + 2];
	}

	//subsampling
	if (Y_val != 1)
	{
		for (int i = 0; i < Height*Width; i++)
		{
			if (i%Y_val != 0)
			{
				dataY[i] = 0;
			}
		}
	}
	if (U_val != 1)
	{
		for (int i = 0; i < Height*Width; i++)
		{
			if (i%U_val != 0)
			{
				dataU[i] = 0;
			}
		}
	}
	if (V_val != 1)
	{
		for (int i = 0; i < Height*Width; i++)
		{
			if (i%V_val != 0)
			{
				dataV[i] = 0;
			}
		}
	}

	/*
	//Upsampling by averaging
	if (Y_val != 1)
	{
		int i = 1;
		while (i < Height*Width)
		{
			if (dataY[i] == 0)
			{
				for (int j = 0; j < Y_val; j++)
				{
					if (dataY[i - 1] == 0)
					{
						dataY[i + j] = dataY[i - 2];
					}
					else if (dataY[i + Y_val - 1] == 0)
					{
						dataY[i + j] = dataY[i - 1];
					}
					else
					{
						dataY[i + j] = (dataY[i - 1] + dataY[i + Y_val - 1]) / 2;
					}
				}
				i += Y_val;
			}

		}
	}

	if (U_val != 1)
	{
		int i = 1;
		while (i < Height*Width)
		{
			if (dataU[i] == 0)
			{
				for (int j = 0; j < U_val; j++)
				{
					if (dataU[i - 1] == 0)
					{
						dataU[i + j] = dataU[i - 2];
					}
					else if (dataU[i + U_val - 1] == 0)
					{
						dataU[i + j] = dataU[i - 1];
					}
					else {
						dataU[i + j] = (dataU[i - 1] + dataU[i + U_val - 1]) / 2;
					}
				}
				i += U_val;
			}

		}
	}

	if (V_val != 1)
	{
		int i = 1;
		while (i < Height*Width)
		{
			if (dataV[i] == 0)
			{
				for (int j = 0; j < V_val; j++)
				{
					if (dataV[i - 1] == 0)
					{
						dataV[i + j] = dataV[i - 2];
					}
					else if (dataV[i + V_val - 1] == 0)
					{
						dataV[i + j] = dataV[i - 1];
					}
					else {
						dataV[i + j] = (dataV[i - 1] + dataV[i + V_val - 1]) / 2;
					}
				}
				i += V_val;
			}

		}
	}
	*/

	//Upsampling by linear interpolation

	if (Y_val != 1)
	{
		float ratioY = Y_val;
		int i = 1;
		while (i < Height*Width)
		{
			if (dataY[i] == 0)
			{
				for (int j = 0; j < Y_val; j++)

				{
					dataY[i + j] = (Y_val - (j + 1))*(1 / ratioY)*dataY[i - 1] + ((j + 1)*(1 / ratioY)*dataY[i + Y_val - 1]);
				}
				i += Y_val;
			}

		}
	}

	if (U_val != 1)
	{
		float ratioU = U_val;
		int i = 1;
		while (i < Height*Width)
		{
			if (dataU[i] == 0)
			{
				for (int j = 0; j < U_val; j++)
				{
					dataU[i + j] = (U_val - (j + 1))*(1 / ratioU)*dataU[i - 1] + ((j + 1)*(1 / ratioU)*dataU[i + U_val - 1]);
				}
				i += U_val;
			}

		}
	}

	if (V_val != 1)
	{
		float ratioV = V_val;
		int i = 1;
		while (i < Height*Width)
		{
			if (dataV[i] == 0)
			{
				for (int j = 0; j < V_val; j++)
				{
					dataV[i + j] = (V_val - (j + 1))*(1 / ratioV)*dataV[i - 1] + ((j + 1)*(1 / ratioV)*dataV[i + V_val - 1]);
				}
				i += V_val;
			}

		}
	}


	//Writing it to RGB
	for (int i = 0; i < Height*Width; i++)
	{
		dataR[i] = (dataY[i] + 0.956*dataU[i] + 0.621*dataV[i]);
		dataG[i] = (dataY[i] - 0.272*dataU[i] - 0.647*dataV[i]);
		dataB[i] = (dataY[i] - 1.106*dataU[i] + 1.703*dataV[i]);
	}

	
	float *dataRGB = new float[Height*Width * 3];
	for (int i = 0; i < Height*Width; i++)
	{
		dataRGB[3 * i] = dataB[i];
		dataRGB[3 * i + 1] = dataG[i];
		dataRGB[3 * i + 2] = dataR[i];
	}
	
	
	//Quantization
	if (Q_val != 256)
	{

		for (int i = 0; i < Height*Width * 3; i++)
		{
			dataRGB[i] += 128.0;
			if (dataRGB[i] < 0)
			{
				dataRGB[i] = 0.0;
			}
			if (dataRGB[i] > 255)
			{
				dataRGB[i] = 255.0;
			}

			float N = 0;
			float oldColour = (int)dataRGB[i];
			int bound = 256 / Q_val;
			if (oldColour >= (255 - bound)) {
				dataRGB[i] = 255 - bound;
			}
			else
			{

				float Val = oldColour / bound;
				int flor = int(Val);
				int cil = int(Val + 1);

				if ((Val - flor) < (cil - Val))
				{
					N = flor;
					
				}
				else
				{
					N = cil;
					
				}
				dataRGB[i] = (N*bound) - 1;

			}
			dataRGB[i] -= 128;
		}
	}

	for (int i = 0; i < Height*Width * 3; i++) 
	{
		Data[i] = dataRGB[i];
	}
	
	return false;
}