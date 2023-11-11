import re

pattern = r'(?<=<Text>)(.*?)(<\/Text>)'
text = '<Text>Hello World.</Text>'
result = re.sub(pattern, lambda x: x.group(1).capitalize(), text, flags=re.IGNORECASE)
print(result)