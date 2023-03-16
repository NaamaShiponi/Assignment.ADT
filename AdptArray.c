#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AdptArray.h"


typedef struct AdptArray_{
	PElement* pE;
	DEL_FUNC f_del;
	COPY_FUNC f_copy;
    PRINT_FUNC f_print;
    int arrSize;
}AdptArray,*PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC  f_copy, DEL_FUNC f_del,PRINT_FUNC f_print){
    
    //Finding space for the new AdptArray_ struct
    PAdptArray pNewArr = (PAdptArray)malloc(sizeof(AdptArray));
    
    //Check that malloc worked
    if(pNewArr==NULL) return NULL;
    
    //Insert parameters to struct AdptArray_
    pNewArr->pE=NULL;
    pNewArr->f_copy=f_copy;
    pNewArr->f_del=f_del;
    pNewArr->f_print=f_print;
    pNewArr->arrSize=0;
   
    return pNewArr;
}


void DeleteAdptArray(PAdptArray pArr){
    
    if(pArr!=NULL){ //Check that pArr exists
  
        for(int i=0; i<(pArr->arrSize); i++){
  
            if((pArr->pE)[i] != NULL){ //Check that there is an element in the "i" position in the array
  
                //Delete the element with the delete function we received
                pArr->f_del((pArr->pE)[i]); 
  
            }
  
        }
        //Free the arr space
        free(pArr->pE);
        
        //Free struct AdptArray_
        free(pArr);
  
    }
}



Result SetAdptArrayAt(PAdptArray pArr, int i, PElement pe){
    
    //Check that pArr exists
    if(pArr==NULL) return FAIL;
    
    //Create a new pointer to AdptArray_
    PElement newPArr;

    //If the index we received is greater than the size of the array
    if(i < 0 || pArr->arrSize<=i){

        //Finding space for the new array
        newPArr = (PElement*)calloc((i + 1), sizeof(PElement));

        //Check that calloc worked
        if(newPArr == NULL) return FAIL;
        
        //Copy all the elements from the old array to the new one
		memcpy(newPArr, pArr->pE, (pArr->arrSize) * sizeof(PElement));

        //Free the old array
        free(pArr->pE);
		
        //Update the array in struct AdptArray_
        pArr->pE = newPArr;
        
        //Update the size of the array in struct AdptArray_
        pArr->arrSize=i+1;
    }
   
    if((pArr->pE)[i]!=NULL){ //Check if there is an element in the "i" place
    
        //Free the memory in place "i"
        pArr->f_del((pArr->pE)[i]);
    
    }
    
    //Create a copy of the element and place it in the array
    (pArr->pE)[i]=pArr->f_copy(pe);
   
    return SUCCESS;
}



PElement GetAdptArrayAt(PAdptArray pArr, int i){
    
    //Check that pArr exists and the element in place "i" exists
    if(pArr== NULL || pArr->arrSize < i || (pArr->pE)[i]==NULL) return NULL;  
    
    //Return the element
    return pArr->f_copy((pArr->pE)[i]);

}


int GetAdptArraySize(PAdptArray pArr){
    
    //Check that pArr exists
    if(pArr==NULL) return -1;

    //Return the array size
    return pArr->arrSize;

}


void PrintDB(PAdptArray pArr){

    if(pArr!=NULL){ //Check that pArr exists

        //Go through all the elements in the array
        for(int i=0;i<pArr->arrSize;i++){

            //If the element exists we will print it
            if((pArr->pE)[i]!=NULL) pArr->f_print((pArr->pE)[i]);

        }

    }

}