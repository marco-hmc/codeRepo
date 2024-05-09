# 遍历一个文件夹下的所有文件
# 按照日期重命名，然后加上属性

# ---
# title:  It is never too late to be what you might have been
# date:   2018-04-24 15:01:35 +0300
# image:  '/images/post-9.jpg'
# tags:   [travel, notes]
# ---
import os
import shutil
import datetime

class ToBlogHandler:
    def __init__(self, noteDir, blogDir):
        self.noteDir = noteDir
        self.blogDir = blogDir
        
        self.Attr = {}
    
    def initAttr():
        # 'title': '', 'date': '', 'image': '', 'tags': []
        self.Attr['title'] = '' # 标题

    def getFiles(self):
        for root, dirs, files in os.walk(self.noteDir):
            for file in files:
                print(os.path.join(root, file))
                current_time = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
                new_name = f"{current_time}_{file}"
                shutil.copy2(os.path.join(root, file), os.path.join(self.blogDir, new_name))
                pass

    def renameFiles(self):
        import os
        import time
        for root, dirs, files in os.walk(self.noteDir):
            for file in files:
                print(os.path.join(root, file))
                print(time.ctime(os.path.getctime(os.path.join(root, file))))
                print(time.ctime(os.path.getmtime(os.path.join(root, file))))

if __name__ == '__main__':
    noteDir = '/home/marco/codeRepo/98_blog/notes'
    blogDir = '/home/marco/codeRepo/98_blog/blog'
    handler = ToBlogHandler(noteDir, blogDir)
    pass
    handler.getFiles()
    pass
