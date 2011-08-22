/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMinErrorThresholdImageFilterTest.cxx,v $
  Language:  C++
  Date:      $Date: 2008/10/21 3:21:12 $
  Version:   $Revision: 1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkMinErrorThresholdImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
//#include <limits>


int main(int argc, char* argv[] )
{
  if( argc < 5 )
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImageFile outputImageFile";  
    std::cerr << " numberOfHistogramBins"; 
	std::cerr << "mixtureType <1=Gaussian, 2=Poisson>";
    std::cerr << std::endl;  
    return EXIT_FAILURE;
    }
	
  //Input and Output pixel types
  typedef  short  InputPixelType;
  typedef  unsigned char  OutputPixelType;

  //Input and output images
  typedef itk::Image< InputPixelType,  3 >   InputImageType;
  typedef itk::Image< OutputPixelType, 3 >   OutputImageType;

  //The binarization filter
  typedef itk::MinErrorThresholdImageFilter<
               InputImageType, OutputImageType >  FilterType;
  
  //Image reader/writer
  typedef itk::ImageFileReader< InputImageType >  ReaderType;  
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  //creat the filter, the reader and the writer
  ReaderType::Pointer reader = ReaderType::New();
  FilterType::Pointer filter = FilterType::New();
  WriterType::Pointer writer = WriterType::New();

  //Set inputs and other parameters
  //Here, the output of the reader is passed to the binarization filter, 
  //and the output of that filter is passed to the writer
  reader->SetFileName( argv[1] );
  filter->SetInput( reader->GetOutput() );
  filter->SetNumberOfHistogramBins ( atoi(argv[3]) );
  filter->SetOutsideValue( 255 );
  filter->SetInsideValue(  0  );
  filter->SetMixtureType( atoi(argv[4]) );
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[2] );

  //calling the update on the writer, will automatically triger the update
  //on the previous filters in the pipeline
  writer->Update();
  
  

  //Print the resulting threshold and the estimated mixture parameters
  std::cout << "Computed Threshold is: " << filter->GetThreshold() << std::endl;  
  std::cout << "Estimated Mixture Parameters are: " << std::endl;
  std::cout << "Background Mean = " << filter->GetAlphaLeft() << std::endl;
  std::cout << "Foreground Mean = " << filter->GetAlphaRight() << std::endl;
  std::cout << "Background Prior = " << filter->GetPriorLeft() << std::endl;
  std::cout << "Foreground Prior = " << filter->GetPriorRight() << std::endl;

  return EXIT_SUCCESS;
}
