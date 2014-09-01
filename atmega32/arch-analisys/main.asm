0000: 940C      JMP     0x00002A
0002: 940C      JMP     0x000045
0004: 940C      JMP     0x000045
0006: 940C      JMP     0x000045
0008: 940C      JMP     0x000045
000A: 940C      JMP     0x000045
000C: 940C      JMP     0x000045
000E: 940C      JMP     0x000045
0010: 940C      JMP     0x000045
0012: 940C      JMP     0x000045
0014: 940C      JMP     0x000045
0016: 940C      JMP     0x000045
0018: 940C      JMP     0x000045
001A: 940C      JMP     0x000045
001C: 940C      JMP     0x000045
001E: 940C      JMP     0x000045
0020: 940C      JMP     0x000045
0022: 940C      JMP     0x000045
0024: 940C      JMP     0x000045
0026: 940C      JMP     0x000045
0028: 940C      JMP     0x000045
002A: 2411      EOR     R1,R1
002B: BE1F      OUT     0x3F,R1
002C: E5CF      LDI     R28,0x5F
002D: E0D8      LDI     R29,0x08
002E: BFDE      OUT     0x3E,R29
002F: BFCD      OUT     0x3D,R28
0030: E010      LDI     R17,0x00
0031: E6A0      LDI     R26,0x60
0032: E0B0      LDI     R27,0x00
0033: E9EA      LDI     R30,0x9A
0034: E0F0      LDI     R31,0x00
0035: C002      RJMP    +0x0002           ; Destination: 0x000038
0036: 9005      ????
0037: 920D      ST      X+,R0
0038: 36A0      CPI     R26,0x60
0039: 07B1      CPC     R27,R17
003A: F7D9      BRNE    -0x05             ; Destination: 0x000036
003B: E010      LDI     R17,0x00
003C: E6A0      LDI     R26,0x60
003D: E0B0      LDI     R27,0x00
003E: C001      RJMP    +0x0001           ; Destination: 0x000040
003F: 921D      ST      X+,R1
0040: 36A0      CPI     R26,0x60
0041: 07B1      CPC     R27,R17
0042: F7E1      BRNE    -0x04             ; Destination: 0x00003F
0043: 940C      JMP     0x000048
0045: 940C      JMP     0x000000
0047: 9508      RET
0048: E5CF      LDI     R28,0x5F
0049: E0D8      LDI     R29,0x08
004A: BFDE      OUT     0x3E,R29
004B: BFCD      OUT     0x3D,R28
004C: CFFF      RJMP    -0x0001           ; Destination: 0x00004C
