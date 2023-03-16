#include <stdio.h>
#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>

typedef struct AdptArray_{
	PElement* pE;
	DEL_FUNC f_del;
	COPY_FUNC f_copy;
    PRINT_FUNC f_print;
    int arrSize;
}AdptArray,*PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC  f_copy, DEL_FUNC f_del,PRINT_FUNC f_print){
  
    PAdptArray pNewArr = (PAdptArray)malloc(sizeof(AdptArray));
  
    if(pNewArr==NULL) return NULL;
   
    pNewArr->pE=NULL;
   
    pNewArr->f_copy=f_copy;
   
    pNewArr->f_del=f_del;
   
    pNewArr->f_print=f_print;
   
    pNewArr->arrSize=0;
   
    return pNewArr;
}


void DeleteAdptArray(PAdptArray pArr){
  
    if(pArr!=NULL){
  
        for(int i=0; i<(pArr->arrSize); i++){
  
            if((pArr->pE)[i] != NULL){
  
                pArr->f_del((pArr->pE)[i]);
  
            }
  
        }
  
        free(pArr->pE);
  
        free(pArr);
  
    }
}


Result SetAdptArrayAt(PAdptArray pArr, int i, PElement pe){
    
    if(pArr==NULL) return FAIL;
    
    PElement newPArr;

    //לבדוק שהאינדקס זה בגודל המערך
    if(i < 0 || pArr->arrSize<=i){

        newPArr = (PElement*)calloc((i + 1), sizeof(PElement));

        if(newPArr == NULL) return FAIL;
        
		memcpy(newPArr, pArr->pE, (pArr->arrSize) * sizeof(PElement));

        free(pArr->pE);
		
        pArr->pE = newPArr;
        
        pArr->arrSize=i+1;
    }
   
    //לשחרר אם יש שם משהו כבר 
    if((pArr->pE)[i]!=NULL){
    
        pArr->f_del((pArr->pE)[i]);
    
    }
   
    (pArr->pE)[i]=pArr->f_copy(pe);
   
    return SUCCESS;
}


PElement GetAdptArrayAt(PAdptArray pArr, int i){
    
    if(pArr== NULL || pArr->arrSize < i || (pArr->pE)[i]==NULL) return NULL;  
    
    return pArr->f_copy((pArr->pE)[i]);

}


int GetAdptArraySize(PAdptArray pArr){

    if(pArr==NULL){

        return -1;

    }

    return pArr->arrSize;

}


void PrintDB(PAdptArray pArr){

    if(pArr!=NULL){

        for(int i=0;i<pArr->arrSize;i++){

            if((pArr->pE)[i]!=NULL) pArr->f_print((pArr->pE)[i]);

        }

    }

}