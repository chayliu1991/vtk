/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkThreads.h.in

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkThreads_h
#define vtkThreads_h

/* Threading system.  */
/* #undef VTK_USE_PTHREADS */
#define VTK_USE_WIN32_THREADS
#define VTK_MAX_THREADS 64

// If VTK_USE_PTHREADS is defined, then the multithreaded
// function is of type void *, and returns nullptr
// Otherwise the type is void which is correct for WIN32
#ifdef VTK_USE_PTHREADS
#define VTK_THREAD_RETURN_VALUE nullptr
#define VTK_THREAD_RETURN_TYPE void*
#endif

#ifdef VTK_USE_WIN32_THREADS
#define VTK_THREAD_RETURN_VALUE 0
#define VTK_THREAD_RETURN_TYPE vtkWindowsDWORD __stdcall
#endif

#if !defined(VTK_USE_PTHREADS) && !defined(VTK_USE_WIN32_THREADS)
#define VTK_THREAD_RETURN_VALUE
#define VTK_THREAD_RETURN_TYPE void
#endif

#endif
