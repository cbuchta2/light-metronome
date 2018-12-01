#include "helper_functions.h"

int setTimeSignatureUpper(int timeSignature)
{
        switch(timeSignature)
        {
          case TIME_FOUR_FOUR:
              return 4;
            break;

          case TIME_THREE_FOUR:
              return 3;
            break;

          case TIME_TWO_FOUR:
              return 2;
            break; 
        }
}

int setTimeSignatureLower(int timeSignature)
{
        switch(timeSignature)
        {
          case TIME_FOUR_FOUR:
          case TIME_THREE_FOUR:
          case TIME_TWO_FOUR:
              return 4;
            break; 
        }
}
