#To be inserted @ 80085680
.include "../../Globals.s"
.include "../Header.s"

lwz  r27,OFST_MnSlChrCostumeFileSymbols(rtoc)
add	r27, r27, r26
