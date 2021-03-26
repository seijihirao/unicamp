# draw a color image

import math
import os
import sys

stdout = sys.stdout.fileno()
def put_byte(output):
    written_n = os.write(stdout, bytes((output,)))
    if written_n != 1:
        print('error writing to output stream', file=sys.stderr)
        sys.exit(1)

def put_string(output):
    output = output.encode('ascii')
    written_n = os.write(stdout, output)
    if written_n != len(output):
        print('error writing to output stream', file=sys.stderr)
        sys.exit(1)


if len(sys.argv) > 1:
    print('usage: python create_ppm.py > output.ppm\n\n'
          '       creates a PPM image with a drawing', file=sys.stderr)
    sys.exit(1)

# Defines image header
magic_number_1 = 'P'
magic_number_2 = '6'
width  = 640
height = 480
max_val = 255
end_of_header = '\n'

# Writes output header
put_string(magic_number_1)
put_string(magic_number_2)
put_string('\n')
put_string('%d %d\n' % (width, height))
put_string('%d' % max_val)
put_string(end_of_header)

for row in range(height):
    for col in range(width):
        # ---- Change this section --->
        if row-col < -height//3:
            # White
            put_byte(0xFF); # Red
            put_byte(0xFF); # Green
            put_byte(0xFF); # Blue
        elif row-col > height//3:
            # Dark green
            put_byte(0x44);
            put_byte(0x66);
            put_byte(0x22);
        else:
            # Light cyan
            put_byte(0x66);
            put_byte(0xDD);
            put_byte(0xEE);
        # <----
