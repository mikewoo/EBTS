Input: 
  [IOINPUT1.BIN 11Bytes] 6(Key)+4(Sensor)+1(Uart)
    main()                       //TMAIN.c 
      UI_KeyGet() Char 6 Bytes   //UI.c 
    
      IN_Sensor() Char 4 Bytes   //Input.c
    
      IN_Comm()                  //Input.c
         UART2_ReadByte()  Char 1 Byte     //SYS_STC_12AXX.c

Output: 
  [IOOUTM.BIN 1Byte]
     main()                       //TMAIN.c 
       Event_Keyboard()           //Process.c
         Mot_OnOff()  Char 1 Byte //Output.c
       Event_Comm()              //Process.c
         Mot_OnOff()  Char 1 Byte //Output.c
       Event_Auto()  
         Mot_OnOff()  Char 1 Byte //Output.c
         
       Mot_RunProtect() Char 1 Byte //Output.c         
  [IOOUTLED.BIN 1Byte]
     main()                       //TMAIN.c 
       Led_OnOff()   Char 1 Byte    //UI.c
  [IOUARTO.BIN 1Byte]
     main()                       //TMAIN.c 
       UART1_SendByte()  Char 1 Byte     //SYS_STC_12AXX.c
     
   