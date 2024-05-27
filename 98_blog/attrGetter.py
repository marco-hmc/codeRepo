import os
import datetime
import json
import re

class FileAttrHandler:
    def __init__(self, filePath, confPath='/home/marco/codeRepo/98_blog/blogConf.json'):
        with open(confPath, 'r') as f:
            config = json.load(f)
            self.project = config['projectName']
            self.target_img_dir = config['target_img_dir']
            self.blogDir = config['blogDir']
        self.debugMode = config['debugMode']
        self.filePath = filePath
        self.confPath = confPath
        self.getAttr()

    def getNumberFromFileName(self):
        file_name = os.path.basename(self.filePath)
        self.number = re.search(r'\d+(?=_)', file_name).group()
        pass
            
    def getAttr(self):
        self.getNumberFromFileName()
        self.getNameLabels()
        self.getTitle()
        self.getCreateDate()
        self.getSubTitle()
        self.getTags()
        self.getPicture()
        pass

    def getCreateDate(self):
        create_time = os.path.getctime(self.filePath)
        time_zone = "+0800"
        self.formatted_time = datetime.datetime.fromtimestamp(create_time).strftime('%Y-%m-%d %H:%M:%S %z') + time_zone
        pass    

    def getNameLabels(self):
        self.tags = []
        with open(self.filePath, 'r') as file:
            for line in file:
                if line.startswith('_label:'):
                    self.nameLabels = line.strip()[7:].split(',')[0].replace(' ', '')
                    return
        self.nameLabels = ""
        pass
  
    def getTitle(self):
        with open(self.filePath, 'r') as file:
            for line in file:
                if line.startswith('##'):
                    self.title = line.strip()[3:]
                    return
        self.title = ""  
   
    def getSubTitle(self):
        file_name = os.path.basename(self.filePath)
        self.subTitle = file_name.split(".")[0].split("_")[-1]
        self.subTitle = self.subTitle.replace('_', ' ')
        self.subTitle = ''.join([c if not c.isupper() else ' ' + c.lower() for c in self.subTitle]).strip()
   
        
    def getTags(self):
        self.tags = []
        with open(self.filePath, 'r') as file:
            for line in file:
                if line.startswith('_tags:'):
                    self.tags = line.strip()[6:].split(',')
                    self.tags = [tag.strip() for tag in self.tags]
                    return
        self.tags = []


    def getPicture(self):      
        def getSuffix():
            image_files = []
            for root, dirs, files in os.walk(self.target_img_dir):
                for file in files:
                    if f"post-{image_index}" in file:
                        suffix = file.split(".")[-1]
                        image_files.append(suffix)
            if not image_files:
                raise ValueError("No image file found with the specified image index.")
            suffix = image_files[0]
            return suffix

        with open(self.confPath, 'r') as conf_file:
            conf_data = json.load(conf_file)
        image_index = conf_data['image_index']
        suffix = getSuffix()
        self.image = f"/images/post/post-{image_index}.{suffix}"
        image_index += 1
        conf_data['image_index'] = image_index
        if (self.debugMode == False):
            with open(self.confPath, 'w') as conf_file:
                json.dump(conf_data, conf_file)
    
    def writeAttr(self, targetDir):
        attr = f"---\ntitle: {self.title}\ndate: {self.formatted_time}\nimage: {self.image}\nproject: {self.project}\ntags: {', '.join(self.tags)}\n\n---\n\n"
        targetPath = os.path.join(targetDir, f"{self.formatted_time[:10]}-{self.number}-{self.title}.md")
        with open(self.filePath, 'r') as file:
            content = file.read()
        filtered_lines = [line for line in content if not line.strip().startswith(('_tags', '_labels'))]
        content = ''.join(filtered_lines)
        with open(targetPath, 'w') as file:
            file.write(attr)
            file.write(content)
        pass

if __name__ == '__main__':
    filePath = '/home/marco/codeRepo/1_notes/0_cpp/0_notes/0_cppQuiz.md'
    handler = FileAttrHandler(filePath)
    handler.writeAttr("/home/marco/codeRepo/98_blog/test")
    pass