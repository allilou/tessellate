#include "../tessellate.h"
#include <stdio.h>
#include <stdlib.h>

void exportPointsToGeoJSON(const double *coordinates_out, int nverts, char *filename){

    int i;
    FILE * fout = fopen(filename,"wt");

    fprintf(fout, "{ \"type\": \"FeatureCollection\", \n");
    fprintf(fout, "\"features\": [ \n");

    for (i=0; i<2 * nverts; i+=2) {
        fprintf(fout, "    {\"type\": \"Feature\", \n");
        fprintf(fout, "    \"geometry\": { \n");
        fprintf(fout, "      \"type\": \"Point\", \n");
        fprintf(fout, "      \"coordinates\": [%g, %g] \n",
                coordinates_out[i], coordinates_out[i+1]);
        fprintf(fout, "      }, \n");
        fprintf(fout, "    \"properties\": { \n");
        fprintf(fout, "      \"num\": \" %d \" \n", i/2);
        fprintf(fout, "      } \n");
        fprintf(fout, "    }, \n");
    }
    fprintf(fout, "\n {}] \n");
    fprintf(fout, "} \n");

    fclose(fout);
}
void exportTrianglesToGeoJSON(int *tris_out, int ntris, const double *coordinates_out, char *filename){
    int i, size = 2;
    FILE * fout = fopen(filename,"wt");

    fprintf(fout, "{ \"type\": \"FeatureCollection\", \n");
    fprintf(fout, "\"features\": [ \n");

    for (i=0; i<3  * ntris; i+=3) {
        fprintf(fout, "    {\"type\": \"Feature\", \n");
        fprintf(fout, "    \"geometry\": { \n");
        fprintf(fout, "      \"type\": \"Polygon\", \n");
        fprintf(fout, "      \"coordinates\": [[ ");
        fprintf(fout, "[%g, %g], [%g, %g], [%g, %g] ",
                coordinates_out[ tris_out[i] * size],
                coordinates_out[(tris_out[i] * size)+1],
                coordinates_out[ tris_out[i+1] * size],
                coordinates_out[(tris_out[i+1] * size)+1],
                coordinates_out[ tris_out[i+2] * size],
                coordinates_out[(tris_out[i+2] * size)+1]);
        fprintf(fout, " ]] \n");
        fprintf(fout, "      }, \n");
        fprintf(fout, "    \"properties\": { \n");
        fprintf(fout, "      \"num\": \" Triangle : %d-%d-%d\" \n", tris_out[i],tris_out[i+1],tris_out[i+2]);
        fprintf(fout, "      } \n");
        fprintf(fout, "    }, \n");
    }
    fprintf(fout, "\n{}] \n");
    fprintf(fout, "} \n");
    fclose(fout);
}

void run_example(const double *contours_array[],
                 int contours_size,
                 int input_size,
                 char *suffix)
{
    double *coordinates_out;
    int *tris_out;
    int nverts, ntris, i;
    char filename[100]="";

    tessellate(&coordinates_out,
               &nverts,
               &tris_out,
               &ntris,
               contours_array,
               contours_array + contours_size);

    fprintf(stdout, "\n--------- vetices ------------ \n");

    for (i=0; i<2 * nverts; ++i) {
        fprintf(stdout, "%g ", coordinates_out[i]);
    }

    fprintf(stdout, "\n--------- triangles ------------ \n");

    for (i=0; i<3 * ntris; ++i) {
        fprintf(stdout, "%d ", tris_out[i]);
    }
    fprintf(stdout, "\n**** \n");

    sprintf(filename, "input_%s.geojson", suffix);
    exportPointsToGeoJSON(contours_array[0], input_size, filename);
    sprintf(filename, "output_%s.geojson", suffix);
    exportPointsToGeoJSON(coordinates_out, nverts, filename);
    sprintf(filename, "tris_%s.geojson", suffix);
    exportTrianglesToGeoJSON(tris_out, ntris, coordinates_out, filename);

    free(coordinates_out);
    if (tris_out)
        free(tris_out);
}

int main()
{
    double a1[] = { 0, 0, 1, 5, 2, 0, -1, 3, 3, 3 };
    const double *c1[] = {a1, a1+10};
    int s1 = 2;
    run_example(c1, s1, 5, "s1");

    double a2[] = { 0, 0, 3 , 0, 3, 3, 0, 3,
                    1, 1, 2, 1, 2, 2, 1, 2 };
    const double *c2[] = {a2, a2+8, a2+16};
    int s2 = 3;
    run_example(c2, s2, 8, "s2");

    double a3[] = { 441, 0, 326, 0, 326, 889, 12, 889, 12,
                    992, 755, 992, 755, 889, 441, 889 };
    const double *c3[] = { a3, a3+16 };
    int s3 = 2;
    run_example(c3, s3, 8, "s3");

    return 0;
}
