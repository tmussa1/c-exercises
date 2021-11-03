#### [3a] Explain why this use of scanf allows buffer overflow.

More characters than intended may be read into the array resulting in
unintended behavior of accessing memory that is out of bounds of the array.
That approach also has issues with wasting too much space when not needed
