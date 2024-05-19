# // project: project_os
# // project: project_network
# // project: project_ccpp
# // project: project_compile
# // project: project_essay
# // project: project_data

import sys

if __name__ == '__main__':
    sys.path[0]="/home/marco/codeRepo/98_blog"

import json
import os
from attrGetter import FileAttrHandler
import sys
import re
import re
import shutil

class ToBlogHandler:
    def __init__(self, confPath):
        with open(confPath, 'r') as f:
            config = json.load(f)
            self.noteDir = config['noteDir']
            self.projectName = config['projectName']
            self.targetDir = config['targetDir']
            self.target_img_dir = config['target_img_dir']
            
        self.confPath =confPath

    def processAttr(self, file_path):
        attr_getter = FileAttrHandler(file_path, self.confPath)
        if attr_getter.title != "":
            attr_getter.writeAttr(self.targetDir)
            return True
        return False
    
    def dealWithImg(self, file_path):
        img_dir = os.path.join(os.path.dirname(file_path), '_imgs')
        target_img_dir = os.path.join(self.targetDir, self.projectName, '_imgs')
        if os.path.exists(img_dir):
            if not os.path.exists(target_img_dir):
                os.makedirs(target_img_dir)
            for root, dirs, files in os.walk(img_dir):
                for file in files:
                    img_path = os.path.join(root, file)
                    shutil.copy(img_path, target_img_dir)
    
    def traverseFiles(self):
        for root, dirs, files in os.walk(self.noteDir):
            for file in files:
                # 只处理满足正则表达式的文件
                if re.match(r'\d{1,2}_', file):
                    file_path = os.path.join(root, file)
                    if(self.processAttr(file_path)):
                        self.dealWithImg(file_path)
        pass
    

if __name__ == '__main__':
    handler = ToBlogHandler("/home/marco/codeRepo/98_blog/blogConf.json")
    handler.traverseFiles()
    pass
