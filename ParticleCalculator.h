#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkProperty.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

void calculateColorByAmplitude(unsigned char color[3], double amplitude)
{
    color[0]=(unsigned char) vtkMath::Random(0, 255);
    color[1]=(unsigned char) vtkMath::Random(0, 255);
    color[2]=(unsigned char) vtkMath::Random(0, 255);
}


vtkSmartPointer<vtkActor> getDataSetAsActor(float pointArray[][4], int numPoints)
{
    //Points group declaration
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    
    //points->InsertNextPoint (0.0, 0.0, 0.0);
    //points->InsertNextPoint (1.0, 0.0, 0.0);
    //points->InsertNextPoint (0.0, 1.0, 0.0);
    //points->InsertNextPoint (0.0, -1.0, 0.0);
    
    //Colors setup
    vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");
    
    //Variable to set colors
    unsigned char color[3] = {0, 0, 0};
    
    //points->SetNumberOfPoints(numberOfPoints);
    
    for(unsigned int i = 0; i < numPoints; i++)
    {
        points->InsertNextPoint(pointArray[i][0], pointArray[i][1], pointArray[i][2]);
        calculateColorByAmplitude(color, pointArray[i][3]);
        colors->InsertNextTupleValue(color);
        //With ID
        //points->InsertPoint(i, vtkMath::Random(0.0,1.0), vtkMath::Random(0.0,1.0), vtkMath::Random(0.0,1.0));
    }
    
    
    vtkSmartPointer<vtkPolyData> pointsPolydata = vtkSmartPointer<vtkPolyData>::New();
    
    pointsPolydata->SetPoints(points);
    
    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
    vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
#else
    vertexFilter->SetInputData(pointsPolydata);
#endif
    vertexFilter->Update();
    
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->ShallowCopy(vertexFilter->GetOutput());
    
    //Add data configuration
    polydata->GetPointData()->SetScalars(colors);
    
    // Visualization
    vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInputConnection(polydata->GetProducerPort());
#else
    mapper->SetInputData(polydata);
#endif
    
    vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(1);
    
    return actor;
}


vtkSmartPointer<vtkActor> getDataSetAsActor()
{
    //Points group declaration
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    
    //points->InsertNextPoint (0.0, 0.0, 0.0);
    //points->InsertNextPoint (1.0, 0.0, 0.0);
    //points->InsertNextPoint (0.0, 1.0, 0.0);
    //points->InsertNextPoint (0.0, -1.0, 0.0);
    
    int numberOfPoints = 1.0e7;
    
    //Colors setup
    vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");
    
    //Variable to set colors
    unsigned char color[3] = {0, 0, 0};
    
    //points->SetNumberOfPoints(numberOfPoints);
    
    for(unsigned int i = 0; i < numberOfPoints; i++)
    {
        points->InsertNextPoint(vtkMath::Random(-10.0,10.0), vtkMath::Random(-10.0,10.0), vtkMath::Random(-10.0,10.0));
        color[0]=(unsigned char) vtkMath::Random(0,255);
        color[1]=(unsigned char) vtkMath::Random(0,255);
        color[2]=(unsigned char) vtkMath::Random(0,255);
        colors->InsertNextTupleValue(color);
        //With ID
        //points->InsertPoint(i, vtkMath::Random(0.0,1.0), vtkMath::Random(0.0,1.0), vtkMath::Random(0.0,1.0));
    }
    
    
    vtkSmartPointer<vtkPolyData> pointsPolydata = vtkSmartPointer<vtkPolyData>::New();
    
    pointsPolydata->SetPoints(points);
    
    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
    vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
#else
    vertexFilter->SetInputData(pointsPolydata);
#endif
    vertexFilter->Update();
    
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->ShallowCopy(vertexFilter->GetOutput());
    
    //Add data configuration
    polydata->GetPointData()->SetScalars(colors);
    
    // Visualization
    vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInputConnection(polydata->GetProducerPort());
#else
    mapper->SetInputData(polydata);
#endif
    
    vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(1);
    
    return actor;
}