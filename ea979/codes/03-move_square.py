import sys
import numpy as np

# Gets binary output underlying stdout
stdout_bin = sys.stdout.buffer

def put_string(output):
    output = output.encode('ascii') if isinstance(output, str) else output
    written_n = stdout_bin.write(output)
    if written_n != len(output):
        print('error writing to output stream', file=sys.stderr)
        sys.exit(1)


def draw_line(image, x0, y0, x1, y1, color):
    h, w = image.shape
    if x0 < 0:
        x0 = 0
    if x0 >= w:
        x0 = w-1
    if x1 < 0:
        x1 = 0
    if x1 >= w:
        x1 = w-1
    if y0 < 0:
        y0 = 0
    if y0 >= h:
        y0 = h-1
    if y1 < 0:
        y1 = 0
    if y1 >= h:
        y1 = h-1
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
        step_row = 1 if r1>=r0 else -1
        d = 2*dr - dc # starting D value, D_init in book
        for pixel_c in range(c0, c1+1):
            image[pixel_r, pixel_c] = color
            if d<=0:
                d += d_horizontal
            else:
                d += d_diagonal
                pixel_r += step_row
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
        for pixel_r in range(r0, r1+1):
            image[pixel_r, pixel_c] = color
            if (d<=0):
                d += d_vertical
            else:
                d += d_diagonal
                pixel_c += step_col

# Parses and checks command-line arguments
max_val = 255
INITIAL_POINTS = [
    np.array([10, 110, 1]),
    np.array([10, 170, 1]),
    np.array([70, 170, 1]),
    np.array([70, 110, 1])
]

def main():
    
    # Getting input matrix to apply on drawing
    matrix = []
    matrix.append([float(i) for i in input().split(' ')])
    matrix.append([float(i) for i in input().split(' ')])
    matrix.append([float(i) for i in input().split(' ')])
    matrix = np.array(matrix)

    # Defines image header
    magic_number_1 = 'P'
    magic_number_2 = '5'
    width  = 400
    height = 400
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

    # Applies linear transformation
    points = []
    for point in INITIAL_POINTS:
        points.append([int(x) for x in matrix.dot(point)])

    # Draws line
    for i in range(len(INITIAL_POINTS)):
        j = i+1 if (i != len(INITIAL_POINTS)-1) else 0
        draw_line(image, 
                points[i][0], points[i][1], 
                points[j][0], points[j][1], 
                0)

    # Outputs image
    put_string(image.tobytes())


main()
