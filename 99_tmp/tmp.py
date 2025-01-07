# 给定的十六进制字符串
hex_string = "71 61 78 a8 b2 3f a1 ec"

# 将十六进制字符串转换为字节
byte_data = bytes.fromhex(hex_string)

# 尝试使用不同的中文编码格式进行解码
encodings = ['gb2312', 'gbk', 'gb18030', 'utf-8']

for encoding in encodings:
    try:
        decoded_string = byte_data.decode(encoding)
        print(f"Decoded with {encoding}: {decoded_string}")
    except UnicodeDecodeError:
        print(f"Failed to decode with {encoding}")