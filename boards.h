

#ifdef BOARD_SUMO_1_1712
  
  /*
    D05 - PD5 - Debug
    D06 - PD6 - MOT A1
    D07 - PD7 - EN StepUp
    D08 - PB0
    D09 - PB1 - MOT A2
    D10 - PB2 - MOT B2
    D11 - PB3 - MOT B1
    D12 - PB4 - LED 2
    D13 - PB5 - LED 1
    D14 / A0 - PC0
    D15 / A1 - PC1
    D16 / A2 - PC2
    D17 / A3 - PC3
    A7 - PC7*/
  
  #define pinLED2           12
  #define pinLED1           13
  
  // inputs
  #define pinDebug          5
  
  // outputs
  #define pinSteUpEN        7
  
  #define pinMotA1          6
  #define pinMotA2          9
  #define pinMotB1          11
  #define pinMotB2          10

#elif BOARD_SUMO_1_0
  
  /*
    D02 - PD2 - LiPo charging
    D03 - PD3 - LiPo full
    D06 - PD6 - MOT A1
    D07 - PD7 - EN StepUp
    D08 - PB0
    D09 - PB1 - MOT A2
    D10 - PB2 - MOT B2
    D11 - PB3 - MOT B1
    D12 - PB4 - LED 2
    D13 - PB5 - LED 1
    D14 / A0 - PC0
    D15 / A1 - PC1
    D16 / A2 - PC2
    D17 / A3 - PC3
    A7 - PC7*/
  
  #define pinLED2           12
  #define pinLED1           13
  
  // inputs
  #define pinLiPoCharging   2
  #define pinLiPoFull       3
  
  // outputs
  #define pinSteUpEN        7
  
  #define pinMotA1          6
  #define pinMotA2          9
  #define pinMotB1          11
  #define pinMotB2          10

#else
  #error define board in config.h
#endif


#ifdef BOARD_SUMO_OPT_1_0

  #define pinLineLeft       A0
  #define pinLineFront      A1
  #define pinLineRight      A2
  #define pinLineBack       A3
#endif


