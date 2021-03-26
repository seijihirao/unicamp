import os
import sys
import numpy as np

stdout = sys.stdout.fileno()
def put_byte(output):
    written_n = os.write(stdout, bytes((output,)))
    if written_n != 1:
        print('error writing to output stream', file=sys.stderr)
        sys.exit(1)

def put_string(output):
    output = output.encode('ascii') if isinstance(output, str) else output
    written_n = os.write(stdout, output)
    if written_n != len(output):
        print('error writing to output stream', file=sys.stderr)
        sys.exit(1)


def draw_line(image, x0, y0, x1, y1, color, weight):
    h, w = image.shape
    assert x0 >=0
    assert x0 < w
    assert x1 >=0
    assert x1 < w
    assert y0 >=0
    assert y0 < h
    assert y1 >=0
    assert y1 < h
    assert weight >= 1
    # Computes differences
    dx = x1-x0
    dy = y1-y0
    dc = abs(dx) # delta x in book - here we are using row, col coordinates
    dr = abs(dy) # delta y in book
    if dr <= dc:
        # Line inclination is at most 1
        # Swaps points if c1<c0 and converts x,y coordinates to row,col coordinates
        # dx>=0 => x1>=x0 => c1>=x0
        r0 = h-1-y0 if dx>=0 else h-1-y1
        r1 = h-1-y1 if dx>=0 else h-1-y0
        c0 =     x0 if dx>=0 else x1
        c1 =     x1 if dx>=0 else x0
        # Implements Bresenham's midpoint algorithm for lines
        # (Klawonn. Introduction to Computer Graphics. 2nd Edition. Section 4.2, pp. 45–53)
        # ...deltas of Bressenham's algorithm
        d_horizontal = 2*dr      # delta east in book
        d_diagonal   = 2*(dr-dc) # delta northeast in book
        # ...draws line
        pixel_r = r0
        pixel_c = c0
        step_row = 1 if r1>=r0 else -1
        d = 2*dr - dc # starting D value, D_init in book
        
        weight_cols = 10
        weight_rows = int(weight_cols*dr/dc)
        for r in range(c0, c1+1):
            if (weight > 1):
                draw_line(image, pixel_c - weight_rows, pixel_r - weight_cols, pixel_c + weight_rows, pixel_r + weight_cols, color, 1)
            else:
                image[pixel_r, pixel_c] = color
            if d<=0:
                d +=  d_horizontal
                pixel_c += 1
            else:
                d +=  d_diagonal
                pixel_r += step_row
                pixel_c += 1
    else:
        # Line inclination is greater than one -- inverts the roles of row and column
        # Swaps points if y1>y0 and converts x,y coordinates to row,col coordinates
        # dy<=0 => y1<=y0 => r1>=r0
        r0 = h-1-y0 if dy<=0 else h-1-y1
        r1 = h-1-y1 if dy<=0 else h-1-y0
        c0 =     x0 if dy<=0 else x1
        c1 =     x1 if dy<=0 else x0
        # Implements Bresenham's midpoint algorithm for lines
        # (Klawonn. Introduction to Computer Graphics. 2nd Edition. Section 4.2, pp. 45–53)
        # ...deltas of Bressenham's algorithm - same as above, but with coordinates inverted
        d_vertical = 2*dc
        d_diagonal = 2*(dc-dr)
        pixel_r = r0
        pixel_c = c0
        step_col = 1 if c1>=c0 else -1
        d = 2*dc - dr # starting D value, D_init in book

        weight_rows = 10
        weight_cols = int(weight_rows*dc/dr)
        for r in range(r0, r1+1):
            if (weight > 1):
                draw_line(image, pixel_c - weight_rows, pixel_r - weight_cols, pixel_c + weight_rows, pixel_r + weight_cols, color, 1)
            else:
                image[pixel_r, pixel_c] = color
            if (d<=0):
                d +=  d_vertical
                pixel_r += 1
            else:
                d += d_diagonal
                pixel_r += 1
                pixel_c += step_col

# Parses and checks command-line arguments
MAX_SIZE = 8192
max_val = 255

w = h = x0 = y0 = x1 = y1 = color = weight = -1
if len(sys.argv) > 8:
    w = int(sys.argv[1])
    h = int(sys.argv[2])
    x0 = int(sys.argv[3])
    y0 = int(sys.argv[4])
    x1 = int(sys.argv[5])
    y1 = int(sys.argv[6])
    color = int(sys.argv[7])
    weight = int(sys.argv[8])
    
if len(sys.argv)<=8 or w<0 or w>MAX_SIZE or h<0 or h>=MAX_SIZE or x0<0 or x0>=w or x1<0 or x1>=w or y0<0 or y0>=h or \
        y1<0 or y1>=h or color<0 or color>max_val:
    print("usage: draw_line <W> <H> <X0> <Y0> <X1> <Y1> <COLOR> <WEIGHT> > output.pgm\n"
          "creates a PGM image with a line from (X0, Y0) to (X1, Y1) drawin in it\n"
          "W => image width, from 1 to %d\n"
          "H => image height, from 1 to %d\n"
          "<X0> <Y0> <X1> <Y1> => line coordinates, with 0 <= X < W and 0 <= Y < H\n"
          "COLOR => \"color\" of the line in grayscale, from 0 to %d\n"
          "WEIGHT => distante from line to draw rectangle.\n" %
          (MAX_SIZE, MAX_SIZE, max_val), file=sys.stderr)
    sys.exit(1)

# Defines image header
magic_number_1 = 'P'
magic_number_2 = '5'
width  = w
height = h
end_of_header = '\n'

# Writes header
put_string(magic_number_1)
put_string(magic_number_2)
put_string('\n')
put_string('%d %d\n' % (width, height))
put_string('%d' % max_val)
put_string(end_of_header)

# Creates image...
background = 255
image = np.full((height, width), fill_value=background, dtype=np.uint8)

# Draws line
draw_line(image, x0, y0, x1, y1, color, weight)

# Outputs image
put_string(image.tobytes())
