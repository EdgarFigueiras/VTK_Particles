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

//Changes the array with the color passed (color[3]) according to,
//Psi value (amplitude), min Psi value (min), max Psi value (max)
void calculateColorByAmplitudeInRange(unsigned char color[3], double amplitude, float min, float max)
{
    //Colors array, from dark blue (Lowest probability) to dark red (Highest probability)
    unsigned char colorArray[20][3] = {
        {0,0,130},
        {0,0,200},
        {0,0,255},
        {0,40,255},
        {0,90,255},
        {0,153,255},
        {1,212,255},
        {38,255,210},
        {96,255,150},
        {134,255,115},
        {177,255,71},
        {228,255,20},
        {255,211,0},
        {255,163,0},
        {255,100,0},
        {255,60,0},
        {245,10,0},
        {200,0,0},
        {155,0,0},
        {131,0,0}
    };
    
    //TODO Adjust step algorithm
    
    // Calculate the step to use the full range of colours between min and max psi values
    // Calculate the amplitude to adjust the new steps.
    // Amplitude_in_order_0-1 = (Amplitude - minPsi)/(maxPsi-minPsi)
    float x_ampl = (amplitude - min)/(max-min);
    
    //20 steps of colours, amplitude from 0.0 to 1.0
    int indexOfColor = floor (x_ampl / 0.05);
    
    color[0] = colorArray[indexOfColor][0];
    color[1] = colorArray[indexOfColor][1];
    color[2] = colorArray[indexOfColor][2];
    
}

//Changes the array with the color passed (color[3]) according to the Psi value (amplitude)
void calculateColorByAmplitude(unsigned char color[3], double amplitude)
{
    //Colors array, from dark blue (Lowest probability) to dark red (Highest probability)
    unsigned char colorArray[20][3] = {
        {0,0,130},
        {0,0,200},
        {0,0,255},
        {0,40,255},
        {0,90,255},
        {0,153,255},
        {1,212,255},
        {38,255,210},
        {96,255,150},
        {134,255,115},
        {177,255,71},
        {228,255,20},
        {255,211,0},
        {255,163,0},
        {255,100,0},
        {255,60,0},
        {245,10,0},
        {200,0,0},
        {155,0,0},
        {131,0,0}
    };
    
    //20 steps of colours, amplitude from 0.0 to 1.0, step size of 0.05
    int indexOfColor = floor (amplitude / 0.05);
    
    color[0] = colorArray[indexOfColor][0];
    color[1] = colorArray[indexOfColor][1];
    color[2] = colorArray[indexOfColor][2];
    
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
        //calculateColorByAmplitude(color, pointArray[i][3]);
        calculateColorByAmplitudeInRange(color, pointArray[i][3], 0.0, 1.0);
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