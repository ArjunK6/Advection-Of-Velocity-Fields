import os
import glob
import matplotlib.pyplot as plt
import numpy as np
import sys

def output_filename(input_path, output_dir):
    out_path = output_dir + '/' + os.path.basename(input_path)
    out_path = out_path.replace("txt", "png")
    # print(f'in = {input_path}, of = {output_dir}, o = {out_path}')
    return out_path

def create_images(input_dir, output_dir):
    if not (os.path.exists(output_dir)):
        os.mkdir(output_dir)

    files = glob.glob(input_dir + "\\*.txt")
    for file in files:
        out_path = output_filename(file, output_dir)
        arr = np.loadtxt(file)

        plt.imshow(arr, cmap="gray")
        plt.savefig(out_path)
      
if __name__ == "__main__":
    input_dir = sys.argv[1]
    output_dir = sys.argv[2]
    create_images(input_dir, output_dir)
    