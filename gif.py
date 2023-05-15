from PIL import Image
import os

def get_file_list(folder_path):
    file_list = []
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            file_list.append(file_path)
    file_list.sort() 
    return file_list

def ppm_to_gif(ppm_files, output_file):
    images = []
    for ppm_file in ppm_files:
        image = Image.open(ppm_file)
        image = image.convert('RGB')
        images.append(image)
    images[0].save(output_file, save_all=True, append_images=images[1:], loop=0, duration=500)

ppm_files = get_file_list("anime")
ppm_to_gif(ppm_files, "animation.gif")
