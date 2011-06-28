#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char filename[30], XString[16], YString[16], ZString[16], FString[16];
int i, j, k;
float XVal, YVal, ZVal, FVal;
float XMulti, YMulti, ZMulti, FMulti;
float XMin, XMax, YMin, YMax, ZMin, ZMax, FMin, FMax;
float XMod, YMod;
int PrintX, PrintY, PrintZ, PrintF, PrintG01, PrintG00;
int settings_mm, settings_xmod, settings_ymod, settings_zmod;
int main ( int argc, char *argv[] )
{
    XMulti = YMulti = ZMulti = FMulti = 25.4;
    XMax = YMax = ZMax = FMax = -99999999999;
    XMin = YMin = ZMin = FMin =  99999999999;
    printf("nomoreinches! Version 0.1, by Tim K. \n");
    if (!argv[1])
    {
        argv[1] = "front.ngc";
    }
    printf("Processing file: %s. Output in millimetres.\n", argv[1]);
    printf("The minimum X and Y are set to zero.\n", argv[1]);
    FILE *file = fopen ( argv[1], "r" );
    if (file)
    {
        FILE *fp;
        if (fp = fopen("convert-to-mm.ngc", "w"))
        {
            char line [ 128 ];
            
while ( fgets(line, sizeof line, file))
{
    memset(XString, 0, 16);memset(YString, 0, 16);memset(ZString, 0, 16);
    PrintX = 0; PrintG01 = 0; PrintG00 = 0; PrintY = 0; PrintZ = 0; PrintF = 0;
    //run through the text file till you find a value.
    for (i = 0; line[i]; i++)
    {
        if(line[i]=='X')
        {
            PrintX = 1;
            for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
            {
                *(XString+j)=line[i+1+j];
            };
            XVal=atof(XString);
        } // end of x value processing
        if(line[i]=='Y')
        {
            PrintY = 1;
            for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
            {
                *(YString+j)=line[i+1+j];
            };
            YVal=atof(YString);
        } // end of x value processing
        if(line[i]=='Z')
        {
            PrintZ = 1;
            for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
            {
                *(ZString+j)=line[i+1+j];
            };
            ZVal=atof(ZString);
        } // end of x value processing
        if(line[i]=='F')
        {
            PrintF = 1;
            for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
            {
                *(FString+j)=line[i+1+j];
            };
            FVal=atof(FString);
        } // end of x value processing
    } // end of if x processing
    if (PrintX)
    {
        if((XVal*XMulti) > XMax)
        { XMax = XVal*XMulti; }
        if((XVal*XMulti) < XMin)
        { XMin = XVal*XMulti; }
    }
    if (PrintY)
    {
        if((YVal*YMulti) > YMax)
        { YMax = YVal*YMulti; }
        if((YVal*YMulti) < YMin)
        { YMin = YVal*YMulti; }
    }
    if (PrintZ)
    {
        if((ZVal*ZMulti) > ZMax)
        { ZMax = ZVal*ZMulti; }
        if((ZVal*ZMulti) < ZMin)
        { ZMin = ZVal*ZMulti; }
    }
    if (PrintF)
    {
        if((FVal*FMulti) > FMax)
        { FMax = FVal*FMulti; }
        if((FVal*FMulti) < FMin)
        { FMin = FVal*FMulti; }
    }
}
    printf("\n     XMin: %.5f, XMax: %.5f\n     YMin: %.5f, YMax: %.5f\n     ZMin: %.5f, ZMax: %.5f\n     Feedrate Max: %.5f\n", XMin, XMax, YMin, YMax, ZMin, ZMax,FMax);
        //fprintf(fp, "\n     XMin: %.5f, XMax: %.5f\n     YMin: %.5f, YMax: %.5f\n     ZMin: %.5f, ZMax: %.5f\n     Feedrate Max: %.5f\n\n", XMin, XMax, YMin, YMax, ZMin, ZMax,FMax);
        
        if("AutoMod" == "AutoMod") {
            XMod = (0-XMin);
            YMod = (0-YMin);
            } else {
            XMod = 0;
            YMod = 0;
            }
            printf("New Values: \n     XMin: %.5f, XMax: %.5f\n     YMin: %.5f, YMax: %.5f\n\n", XMin+XMod, XMax+XMod, YMin+YMod, YMax+YMod, ZMin, ZMax,FMax);
            rewind(file);
            while ( fgets(line, sizeof line, file))
            {
                k++;
                memset(XString, 0, 16);memset(YString, 0, 16);memset(ZString, 0, 16);
                PrintX = 0; PrintG01 = 0; PrintG00 = 0; PrintY = 0; PrintZ = 0; PrintF = 0;
                //run through the text file till you find a value.
                for (i = 0; line[i]; i++)
                {
                    if(line[i]=='G'&&line[i+1]=='0'&&line[i+2]=='1'&&line[i+3]==' ')
                    {
                        //The line has a G01 code.
                        PrintG01 = 1;
                    }
                    if(line[i]=='G'&&line[i+1]=='0'&&line[i+2]=='0'&&line[i+3]==' ')
                    {
                        //The line has a G00 code.
                        PrintG00 = 1;
                    }
                    if(line[i]=='X')
                    {
                        PrintX = 1;
                        for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
                        {
                            *(XString+j)=line[i+1+j];
                        };
                        XVal=atof(XString);
                    } // end of x value processing
                    if(line[i]=='Y')
                    {
                        PrintY = 1;
                        for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
                        {
                            *(YString+j)=line[i+1+j];
                        };
                        YVal=atof(YString);
                    } // end of x value processing
                    if(line[i]=='Z')
                    {
                        PrintZ = 1;
                        for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
                        {
                            *(ZString+j)=line[i+1+j];
                        };
                        ZVal=atof(ZString);
                    } // end of x value processing
                    if(line[i]=='F')
                    {
                        PrintF = 1;
                        for(j=0;(line[i+j]!='\n'&&line[i+j]!=' '&&line[i+j]);j++)
                        {
                            *(FString+j)=line[i+1+j];
                        };
                        FVal=atof(FString);
                    } // end of x value processing
                } // end of if x processing
                if (PrintG00)
                {
                    fprintf(fp, "G00 ");
                }
                if (PrintG01)
                {
                    fprintf(fp, "G01 ");
                }
                if (PrintX)
                {
                    fprintf(fp, "X%.5f ", (XVal*XMulti)+XMod);
                }
                if (PrintY)
                {
                    fprintf(fp, "Y%.5f ", (YVal*YMulti)+YMod);
                }
                if (PrintZ)
                {
                    fprintf(fp, "Z%.5f ", (ZVal*ZMulti));
                }
                if (PrintF)
                {
                    fprintf(fp, "F%.5f ", (FVal*FMulti));
                }
                if((PrintF+PrintX+PrintY+PrintZ))
                {
                fprintf(fp, "\n"); }
            }
        }
        fclose (fp);
        fclose (file);
        printf("Done! %d lines processed.\n", k);
    }
    else
    {
        printf("No file could be loaded. Drag or specify a file to process.\n Automatically defaults to front.ngc");
        getchar();
    }
    return 0;
}
