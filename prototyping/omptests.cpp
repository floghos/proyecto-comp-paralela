#include <iostream>
using namespace std;

#include <omp.h>
// since kate doesn't recognize omp.h it messes up some stuff beyond it.
// only on the IDE's side tho, it compiles and works correctly, it has been tested.
//

int main() {
// OpenMP test. Seems to work correctly despite Kate not recognizing the <omp.h> lib
    int nthreads = omp_get_num_threads();
    cout << "number of threads outside paralel region is: " << nthreads << endl;
    int random = 10;
#pragma omp parallel
{
    int tid = omp_get_thread_num();
    random = tid;
    printf("my id is %d\n", tid);
    if (tid == 0) {
        nthreads = omp_get_num_threads();
        printf("number of threads inside paralel region is %d\n", nthreads);
    }
}
    cout << "nthreads after the parallel region: " << nthreads << endl;
    cout << "random = " << random << endl;

}
