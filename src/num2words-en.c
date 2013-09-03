#include "num2words-en.h"
#include "string.h"
//#include <stdio.h>

static const char* const ONES[] = {
  "zero",
  "una",
  "dos",
  "tres",
  "quatre",
  "cinc",
  "sis",
  "set",
  "vuit",
  "nou"
};

static const char* const TEENS[] ={
  "",
  "onze",
  "dotze",
  "tretze",
  "catorze",
  "quinze",
  "setze",
  "disset",
  "divuit",
  "dinou"
};

static const char* const TENS[] = {
  "",
  "deu",
  "vint",
  "trenta",
  "quaranta",
  "cinquanta",
  "seixanta",
  "setanta",
  "vuitanta",
  "noranta"
};

#define ENPUNT "en punt"
#define QUART "un quart"
#define QUARTS "quarts"
#define MITJA "i mitja"

#define PAST "passades"
#define TO "per a"

#define SINGULAR "La"
#define PLURAL "Les"
#define MENYS "menys"
#define MAX_LEN 7


static size_t append_number(char* words, int num) {
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 0) {
    if (tens_val == 1 && num != 10) {
      strcat(words, TEENS[ones_val]);
      return strlen(TEENS[ones_val]);
    }
    strcat(words, TENS[tens_val]);
    len += strlen(TENS[tens_val]);
  }

  if (ones_val > 0 || num == 0) {
    strcat(words, ONES[ones_val]);
    len += strlen(ONES[ones_val]);
  }

  if (len > MAX_LEN)
  {
    int fullSize = strlen(words);
    words[fullSize - (len - MAX_LEN)] = 0;
    len = MAX_LEN;
  }

  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}


void time_to_words(int hours, int minutes, char* words, size_t length) {

  size_t remaining = length;
  memset(words, 0, length);

  // Fuzzy time
  minutes = (minutes + 3) / 5 * 5;

  // Handle minute wrapping
  if (minutes > 55)
  {
    minutes -= 60;
    hours++;
  }

  
  switch (minutes)
  {
    case 0:
      break;
    case 20:
      remaining -= append_number(words, minutes);
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, PAST);
      remaining -= append_string(words, remaining, " ");
      break;
    case 15:
      //remaining -= append_string(words, remaining, QUART);
      //remaining -= append_string(words, remaining, " ");
      //remaining -= append_string(words, remaining, PAST);
      //remaining -= append_string(words, remaining, " ");
		remaining -= append_string(words, remaining, QUART);
		remaining -= append_string(words, remaining, " de ");
		hours++;
      break;
    case 25:
		remaining -= append_number(words, 2);
		remaining -= append_string(words, remaining, " ");
		remaining -= append_string(words, remaining, QUARTS);
		remaining -= append_string(words, remaining, " ");    
		remaining -= append_string(words, remaining, MENYS);
		remaining -= append_string(words, remaining, " ");   
		remaining -= append_number(words, 5);
		remaining -= append_string(words, remaining, " de ");	  
		hours++;		
		break;
    case 30:
		remaining -= append_number(words, 2);
		remaining -= append_string(words, remaining, " ");
		remaining -= append_string(words, remaining, QUARTS);
		remaining -= append_string(words, remaining, " de ");
		hours++;
		break;
    case 35:
      remaining -= append_number(words, 20);
      remaining -= append_string(words, remaining, " ");
      remaining -= append_number(words, 5);
      remaining -= append_string(words, remaining, " ");    
      remaining -= append_string(words, remaining, TO);
      remaining -= append_string(words, remaining, " ");    
      hours++;
      break;
    case 40:
		remaining -= append_number(words, 3);
		remaining -= append_string(words, remaining, " ");
		remaining -= append_string(words, remaining, QUARTS);
		remaining -= append_string(words, remaining, " ");    
		remaining -= append_string(words, remaining, MENYS);
		remaining -= append_string(words, remaining, " ");   
		remaining -= append_number(words, 5);
		remaining -= append_string(words, remaining, " de ");	
		hours++;
		break;
    case 50:
		remaining -= append_number(words, 3);
		remaining -= append_string(words, remaining, " ");
		remaining -= append_string(words, remaining, QUARTS);
		remaining -= append_string(words, remaining, " i ");    
		remaining -= append_number(words, 5);
		remaining -= append_string(words, remaining, " de ");	
		hours++;
		break;	
    case 55:
      remaining -= append_number(words, 60 - minutes);
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, TO);
      remaining -= append_string(words, remaining, " ");
      hours++;
      break;
    case 45:
		remaining -= append_number(words, 3);
		remaining -= append_string(words, remaining, " ");
		remaining -= append_string(words, remaining, QUARTS);
		remaining -= append_string(words, remaining, " de ");
		hours++;
		break;	
  }

  // Handle hour wrapping
  hours += 12; // If hours == 0
  while (hours > 12)
  {
    hours -= 12;
  }

  
  // Singular o Plural depenent de la hora
  if (hours == 13 || hours == 1)
  {
	remaining -= append_string(words, remaining, SINGULAR);
	remaining -= append_string(words, remaining, " ");	
  }  
  else
  {
	//remaining -= append_string(words, remaining, PLURAL);
	//remaining -= append_string(words, remaining, " ");	
  }

  remaining -= append_string(words, remaining, "*"); // Make hours bold
  
  remaining -= append_number(words, hours);
  remaining -= append_string(words, remaining, " ");

  
  switch(minutes)
  {
  case 0:
	// Add o'clock to whole hours
	remaining -= append_string(words, remaining, ENPUNT);
	remaining -= append_string(words, remaining, " ");
    
	case 5:
	case 10:
		remaining -= append_number(words, minutes);
		break;
  }

  
}

