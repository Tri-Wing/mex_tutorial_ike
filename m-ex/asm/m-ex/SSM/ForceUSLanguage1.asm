#To be inserted at 8000aea0
.include "../Globals.s"
.include "Header.s"

# this is done because selecting japanese would load the JPN ssm files
# and m-ex does not contain sizes for them, so the audio buffer will 
# inevitably overflow.

li r0,1

Exit:
