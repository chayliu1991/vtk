// This file is autogenerated by vtkCreateArrayDispatchArrayList.cmake.
// Do not edit this file. Your changes will not be saved.

#ifndef vtkArrayDispatchArrayList_h
#define vtkArrayDispatchArrayList_h

#include "vtkTypeList.h"
#include "vtkAOSDataArrayTemplate.h"

namespace vtkArrayDispatch {

typedef vtkTypeList::Unique<
  vtkTypeList::Create<
    vtkAOSDataArrayTemplate<char>,
    vtkAOSDataArrayTemplate<double>,
    vtkAOSDataArrayTemplate<float>,
    vtkAOSDataArrayTemplate<int>,
    vtkAOSDataArrayTemplate<long>,
    vtkAOSDataArrayTemplate<long long>,
    vtkAOSDataArrayTemplate<short>,
    vtkAOSDataArrayTemplate<signed char>,
    vtkAOSDataArrayTemplate<unsigned char>,
    vtkAOSDataArrayTemplate<unsigned int>,
    vtkAOSDataArrayTemplate<unsigned long>,
    vtkAOSDataArrayTemplate<unsigned long long>,
    vtkAOSDataArrayTemplate<unsigned short>,
    vtkAOSDataArrayTemplate<vtkIdType>
  >
>::Result Arrays;

} // end namespace vtkArrayDispatch

#endif // vtkArrayDispatchArrayList_h

