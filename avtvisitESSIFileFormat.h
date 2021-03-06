/*****************************************************************************
*
* Copyright (c) 2000 - 2013, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtvisitESSIFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_visitESSI_FILE_FORMAT_H
#define AVT_visitESSI_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>

#include <vector>

#include <hdf5.h>

#include <vtkFloatArray.h>
#include <vtkPoints.h>
#include <vtkRectilinearGrid.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>


// ****************************************************************************
//  Class: avtvisitESSIFileFormat
//
//  Purpose:
//      Reads in visitESSI files as a plugin to VisIt.
//
//  Programmer: jaabell -- generated by xml2avt
//  Creation:   Thu May 15 11:22:33 PDT 2014
//
// ****************************************************************************

class avtvisitESSIFileFormat : public avtMTMDFileFormat
{
public:
    avtvisitESSIFileFormat(const char *);
    virtual           ~avtvisitESSIFileFormat()
    {
        FreeUpResources();
        // Maybe need to destroy VTK objects????
    };

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, int timestep,
    //                                     int domain, const char *type, void *args,
    //                                     DestructorFunction &);
    //

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    // virtual void        GetCycles(std::vector<int> &);
    // virtual void        GetTimes(std::vector<double> &);
    //

    virtual int            GetNTimesteps(void);
    //     virtual void          GetTimes(std::vector<double>&) { return; };
    // virtual double        GetTime(void) { return INVALID_TIME; };
    virtual double        GetTime(int);

    virtual void        GetTime(std::vector<double> &times);

    virtual const char    *GetType(void)
    {
        return "visitESSI";
    };
    virtual void           FreeUpResources(void);

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

    //To provide initialization... later
    void ActivateTimestep();

    void PopulateTimeAndNSteps();

    void *
    GetAuxiliaryData(const char *var,
                     int domain, const char *type, void *,
                     DestructorFunction &df);

protected:
    // DATA MEMBERS
    void initialize();
    void
    openSubdomainNumber(int domain);

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
private:
    std::string filename_string;
    bool initialized;
    hid_t id_file;
    int *nnodes;
    int *ngauss;
    int *ncells;
    int nsteps;
    int number_of_processes;
    int process_number;

    int max_ele_tag;
    int max_node_tag;

    std::vector<double> t;

    std::string mainmesh, gaussmesh;

    bool returned_mainmesh_already;
    bool returned_gaussmesh_already;

    int **m_gauss_to_element_tag;
    int **m_number_of_gauss_points;
    int **m_number_of_dofs;
    int **m_tags2pointnumbers;
    int **m_pointnumbers2tags;
    int **m_tags2cellnumbers;
    int **m_cellnumbers2tags;

    vtkUnstructuredGrid **m_mainmesh_data;
    vtkUnstructuredGrid **m_gaussmesh_data;

};



//Element class tags (see ClassTags.h within RealESSI)
#define EightNodeBrickLT 8001

#endif
