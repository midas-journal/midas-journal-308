CMAKE_MINIMUM_REQUIRED(VERSION 2.0)

PROJECT ( MinimumErrorThresholding)

# This is needed for testing with ctest
ENABLE_TESTING()

FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR “Set ITK_DIR”)
ENDIF(ITK_FOUND)


SET(ProjectExe "itkMinErrorThresholdImageFilterTest")
ADD_EXECUTABLE(${ProjectExe} itkMinErrorThresholdImageFilterTest.cxx )
TARGET_LINK_LIBRARIES(${ProjectExe} ITKIO ITKBasicFilters ITKCommon)

SET(INPUTDATA ${PROJECT_SOURCE_DIR})
ADD_TEST( MinimumErrorThresholdingTest2  ${ProjectExe} ${INPUTDATA}/Test_Image_2D.tif Test_Image_2D_PoissonOutput.tif 128  1)
ADD_TEST( MinimumErrorThresholdingTest1  ${ProjectExe} ${INPUTDATA}/Test_Image_2D.tif Test_Image_2D_GaussianOutput.tif 128  2)
ADD_TEST( MinimumErrorThresholdingTest4  ${ProjectExe} ${INPUTDATA}/Test_Image_3D.pic Test_Image_3D_PoissonOutput.tif 128  1)
ADD_TEST( MinimumErrorThresholdingTest3  ${ProjectExe} ${INPUTDATA}/Test_Image_3D.pic Test_Image_3D_GaussianOutput.tif 128  2)


