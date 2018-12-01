#include "helper_functions.h"

int setTimeSignatureUpper(timeSignatureEnum timeSignature)
{
        switch(timeSignature)
        {
          case timeFOUR_FOUR:
              return 4;
            break;

          case timeTHREE_FOUR:
              return 3;
            break;

          case timeTWO_FOUR:
              return 2;
            break; 
        }
}

int setTimeSignatureLower(timeSignatureEnum timeSignature)
{
        switch(timeSignature)
        {
          case timeFOUR_FOUR:
          case timeTHREE_FOUR:
          case timeTWO_FOUR:
              return 4;
            break; 
        }
}
