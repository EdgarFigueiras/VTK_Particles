#include "ParticleCalculator.h"

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif


int main(int, char *[])
{
    //Number of particles
    int N = 1.0e6;
    
    //Shape of the array
    //{X,Y,Z,psi}
    static float pointArray[1000000][4];
    
    //Filling the array with random data
    for (int i=0; i < N; i++)
    {
        pointArray[i][0] = vtkMath::Random(-10.0,10.0);
        pointArray[i][1] = vtkMath::Random(-10.0,10.0);
        pointArray[i][2] = vtkMath::Random(-10.0,10.0);
        pointArray[i][3] = vtkMath::Random(0.0, 1.0);
    }
    
    
    //visualization config
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    
    //Window size
    renderWindow->SetSize(800,600);
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    
    //Call function to set particles and calculate colors
    renderer->AddActor(getDataSetAsActor(pointArray,N));
    //Background color
    renderer->SetBackground(0,0,0);
    
    renderWindow->Render();
    renderWindowInteractor->Start();
    
    return EXIT_SUCCESS;
}
