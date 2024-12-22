import os

directory = '/home/marco/0_gitRepo/BaiduImageSpider/国家地理摄影'

counter = 10

for filename in os.listdir(directory):
    new_filename = f'post-{counter}{os.path.splitext(filename)[1]}'
    os.rename(os.path.join(directory, filename), os.path.join(directory, new_filename))
    counter += 1